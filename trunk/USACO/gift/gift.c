/*
ID:running3
LANG:C
TASK:gift1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX_LEN (14)
#define MONEY_MAX_VALUE (2000)

typedef struct
{
    char name[NAME_MAX_LEN+1];
    int money;

}Person_S;

Person_S* FindPerson(unsigned int np, const char* name);
void GiveMoney(Person_S* giver, Person_S* receiver, int money);

Person_S *s_group = NULL;

int
main(int argc, char** argv)
{
    FILE *fin  = fopen("gift1.in", "r");
    FILE *fout = fopen("gift1.out", "w");
    unsigned int np = 0; //2 <= NP <= 10
    unsigned int i=0, j = 0;
    Person_S *giver, *receiver;
    char name[NAME_MAX_LEN+1] = {0};
    int money = 0, nums = 0;

    //line 1 NP
    fscanf(fin, "%u\n", &np);
    /*printf("%d\n", np);//testing*/
    s_group = malloc(np*sizeof(Person_S));

    //line 2..NP+1  Each line contains the name of a group member
    for(i=0; i<np; i++)
    {
        fscanf(fin, "%s\n", s_group[i].name);
        s_group[i].money = 0;
        /*printf("%s\n", s_group[i].name);*/
    }

    //line NP+2..EOF 
    /*NP groups of lines organized like this:
    The first line in the group tells the person's name who will be giving gifts.
    The second line in the group contains two numbers: The initial amount of money (in the range 0..2000) to be divided up into gifts by the giver and then the number of people to whom the giver will give gifts, NGi (0 ≤ NGi ≤ NP-1).
    If NGi is nonzero, each of the next NGi lines lists the the name of a recipient of a gift. 
    */
    for(i=0; i<np; i++)
    {
        fscanf(fin, "%s\n", name);
        giver = FindPerson(np, (const char*)name);
        fscanf(fin, "%d %d\n", &money, &nums); 
        /*giver->money += money;*/
        for (j=0; j<nums; j++)
        {
            fscanf(fin, "%s\n", name); 
            receiver = FindPerson(np, (const char*)name);
            GiveMoney(giver, receiver, money/nums);
        }
    }

    //Output data
    for(i=0; i<np; i++)
    {
        fprintf(fout, "%s %d\n", s_group[i].name, s_group[i].money);
    }

    free(s_group);
    fclose(fin);
    fclose(fout);
    return 0;
}

Person_S* FindPerson(unsigned int np, const char* name)
{
    Person_S *person = NULL;
    unsigned int i=0;

    for (i=0; i<np; i++)
    {
        if (0 == strcmp(s_group[i].name, name))
        {
            person = &s_group[i];
            break;
        }
    }

    return person;
}
void GiveMoney(Person_S* giver, Person_S* receiver, int money)
{
    giver->money -= money;
    receiver->money += money;
}

