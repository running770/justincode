/*
ID:running3
LANG:C
TASK:beads
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

int HFAlgorithm(void);
int DBAlgorithm(void);
int Exhaustion(void);

#define MAXN (400)

char necklace[MAXN];
int length;

FILE *fin, *fout;
int
main(int argc, char** argv)
{
    fin = fopen("beads.in", "r");
    fout = fopen("beads.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d\n%s", &length, necklace);
    assert(strlen(necklace) == length);
    /*printf("%d\n%s\n", length, necklace);*/

    /*Exhaustion();*/
    /*DBAlgorithm();*/
    HFAlgorithm();

    fclose(fin);fclose(fout);
    return 0;
}

/*
 *Exhaustion Start O(n^2)
 */

/*
 * Description:Return n mod m. The C % operator is not enough because
     * its behavior is undefined on negative numbers
 * Parameter:n m
 * Return:n%m
 * Author:Justin
 * Time:2008/11/9 12:32:50
 **/
int
mod(int n, int m)
{
    while(n < 0)
        n += m;
    return n%m;
}

/*
 * Description:Calculate number of beads gotten by breaking 
 * before character p and going in direction dir, which is 1
 * for forward and -1 backward
 * Parameter:p, dir
 * Return:number of beads
 * Author:Justin
 * Time:2008/11/9 13:20:29
 **/
int
nbreak(int p, int dir)
{
    char color;
    int i, n;

    color = 'w';

    /*Start at p if going forward, bead before if going backward*/
    if (dir > 0)
        i = p;
    else
        i = mod(p-1, length);

    /*We use "n<length" to cut off loops that go around the whole necklace*/
    for(n=0; n<length; n++, i=mod(i+dir, length))
    {
        /*record which color we're going to collect*/
        if (color == 'w' && necklace[i] != 'w')
            color = necklace[i];
        /*If we've chosen a color and see a bead not 
         * white and not that color, stop*/
        if (color != 'w' && necklace[i] != 'w' && necklace[i] != color)
            break;
    }

    return n;
}
int Exhaustion(void)
{
    int i, n, m;

    m = 0;
    for(i=0; i<length; i++)
    {
        n = nbreak(i, 1) + nbreak(i, -1);
        if (n > m)
            m = n;
    }
    /*If the whole necklace can be gotten with a good
     * break, we'll sometimes count beads more that once.
     * this can only happen when the whole necklace can be
     * taken, when beads that can be grabbed from the right
     * of the break can also be grabbed frome the left*/
    if (m > length)
        m = length;
    
    printf("%d\n", m);
    fprintf(fout, "%d\n", m);
    return m;
}
/*
 *Exhaustion End
 */

/*
Daniel Bundala had an O(n) solution:
Dynamic Programming is good method for solving this problem in O(N). If we consider two copies of the string we easy transform cyclic configuration of the necklace to linear. Now we can compute for each breaking point how many beads of the same color can be collected on the left and on the right from the breaking point. I show how we can compute it only for the left side. For right side it is analogical. Let r[p] and b[p] be the number of red / blue beads that can be collected, when necklace is broken in point p. If we know this and color of next bead (c) we can compute r[p+1] and b[p+1].

 r[0] = p[0] = 0
 If c = 'r' then r[p+1] = r[p] + 1 and b[p+1] = 0
        because the length of the blue beads is 0.
 if c = 'b' then b[p+1] = b[p] + 1 and r[p+1] = 0
 if c = 'w' then both length of the red and length of blue beads
             can be longer.
so r[p+1] = r[p]+1 and b[p+1] = b[p] + 1.

The number of beads that can be collected in breaking point p is then max(left[r[p]], left[b[p]]) + max(right[r[p]], right[b[p]]). And the maximum from this value is answer for the problem. 
 */
int DBAlgorithm(void)
{
    int result = 0;
    char S[2*MAXN];
    int left[2*MAXN][2], right[2*MAXN][2];
    int i;

    strcpy(S, necklace);
    strcat(S, necklace);
    /*printf("%s\n", S);*/

    left[0][0] = left[0][1] = 0;

    for (i=1; i<=2*length; i++)
    {
        /*printf("idx %d %c ", i, S[i]);*/
        if (S[i-1] == 'r')
        {
            left[i][0] = left[i-1][0] + 1;
            left[i][1] = 0;
        }
        else if (S[i-1] == 'b')
        {
            left[i][1] = left[i-1][1] + 1;
            left[i][0] = 0;
        }
        else
        {
            left[i][0] = left[i-1][0] + 1;
            left[i][1] = left[i-1][1] + 1;
        }
        /*printf("left: red %d blue %d\n", left[i][0], left[i][1]);*/
    }

    right[2*length][0] = right[2*length][1] = 0;
    for (i=2*length-1; i>=0; i--)
    {
        if (S[i] == 'r')
        {
            right[i][0] = right[i+1][0] + 1;
            right[i][1] = 0;
        }
        else if (S[i] == 'b')
        {
            right[i][1] = right[i+1][1] + 1;
            right[i][0] = 0;
        }
        else
        {
            right[i][0] = right[i+1][0] + 1;
            right[i][1] = right[i+1][1] + 1;
        }
        /*printf("right: red %d blue %d\n", right[i][0], right[i][1]);*/
    }

    for (i=0; i<2*length; i++)
    {
        result = MAX(result, MAX(left[i][0], left[i][1])+MAX(right[i][0], right[i][1]));

        /*printf("idx %d %c, left red %d blue %d  right red %d blue %d\n", i, S[i], */
                /*left[i][0], left[i][1], right[i][0], right[i][1]);*/
        /*printf("idx %d %c, result %d, left %d, right %d\n", i, S[i], result, */
                /*MAX(left[i][0], left[i][1]), MAX(right[i][0], right[i][1]));*/
    }

    result = MIN(result, length);

    /*printf("%d\n", result);*/
    fprintf(fout, "%d\n", result);
   
    return result;
}

/*
Holland's Frank Takes has a potentially easier solution:

This solution simply changes the string s into ss, then for every starting
symbol it checks if it can make a sequence simply by repeatedly checking 
if a sequence can be found that is longer than the current maximum one.
*/
int HFAlgorithm(void)
{
    int i=0, j=0, current=0, max=0;
    char ss[2*MAXN] = {0};
    char c;
    int state = 0; //calculated r&b: 0: neither 1:either 2:both
    
    strcpy(ss, necklace);
    strcat(ss, necklace);
    /*printf("%s\n", ss);*/

    for(i=0; i<length; i++)
    {
        c = ss[i];
        if (c == 'w')
            state = 0;
        else
            state = 1;
        j = i;
        current = 0;
        while(state <= 2)
        {
            //dont go further in second string that 
            //starting position in first string
            while(j<length+i && (ss[j] == c || ss[j] == 'w'))
            {
                current++;
                j++;
            }//end while
            state++;
            c = ss[j];
        }//end while
        if (current > max)
            max = current;
    }//for

    /*printf("%d\n", max);*/
    fprintf(fout, "%d\n", max);
    return max;
}

