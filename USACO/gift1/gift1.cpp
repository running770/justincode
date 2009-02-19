/*
ID: running1
PROG: gift1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
	
const int NAME_MAX_LEN =14;
const int NP_MAX = 10; 

class Person
{
public:
	Person(void){}
	Person(string name){this->nameStr = name;}
	
	void GiveMoney(int money){this->money -= money;}
	void ReceiveMoney(int money){this->money += money;};
	int  GetMoney(void){return this->money;};
	
	string nameStr; 
private:	
	int  money;		
};
	
Person *FindPersonByName(string name, Person *somePerson, int personNum)
{
	for (int i=0; i< personNum; i++)
		if (somePerson[i].nameStr == name)
			return &somePerson[i];	
	return NULL;
}

	
int
main(int argc, char **argv)
{
	ofstream fout ("gift1.out");
	ifstream fin  ("gift1.in");
	int np;
	Person 	*somePerson;
	Person  giver;
	Person  recipient;
	Person  *thePerson;
	
	//line 1
	fin >> np;
	somePerson = new Person[np];
	
	//line 2..np+1
	for (int i=2; i<=np+1; i++)
		fin >> somePerson[i-2].nameStr;

	
	int money, n,giveMoney;
	//line np+2 -> end
	while(fin >> giver.nameStr)
	{
		thePerson = FindPersonByName(giver.nameStr, somePerson, np); 
		
		fin >> money >> n;

		giveMoney = (0 == n)?(0):(money/n);
		thePerson->GiveMoney(n*giveMoney);
		while(n--)
		{
			fin >> recipient.nameStr;
			thePerson = FindPersonByName(recipient.nameStr, somePerson, np);	
			thePerson->ReceiveMoney(giveMoney);
		}
	}
	
	for (int i=0; i<np; i++)
	{
		fout << somePerson[i].nameStr << " " << somePerson[i].GetMoney() << endl;
	}
	
	fout.close();
	fin.close();
	return 0;
}
