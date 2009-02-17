#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(x,y) ((x)>(y))?(x):(y);
/*
Spiral queue
21 22 23 24 25
20 07 08 09 10
19 06 01 02 11
18 05 04 03 12
17 16 15 14 13
analyse: the upper right corner of square is (n+1)*(n+1); 
         n is the length of the side 
         e.g. 
         11 (2,0)       ur: 25  (2*2+1)^2
         05 (-1,-1)     ur: 09  (2*|-1|+1)^2
 */
int
Sq_GetValue(int x, int y)
{
    int ur;
    unsigned int m  = max(abs(x),abs(y));
    unsigned int n  = 2*m; //side
    unsigned int v  = 0;  //value

    //the upper right corner
    ur = (n+1)*(n+1);

    if (y == m) // on the upper side
    {
        v = ur - m + x; 
    }
    else if (x == -m) //on the left side, but not the upper left corner
    {
        v = ur - 3*m + y;
    }
    else if (y == -m) //on the lower side, but not the lower left corner
    {
        v = ur - 5*m - x;
    }
    else //on the right side, but not the upper and lower right corner
    {
        v = ur - 7*m - y;
    }

    return v;
}

int
main(int argc, char **argv)
{
    int x, y;
    int n = 9; //side

    for (y=n/2; y>=-n/2; y--)
    {
        for (x=-n/2; x<=n/2; x++)
        {
            printf("%03d ", Sq_GetValue(x,y));
        }
        printf("\n");
    }

    return 0;
}
