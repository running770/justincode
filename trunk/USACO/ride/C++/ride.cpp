/*
ID: running1
PROG: ride
LANG: C++
*/
#include <iostream>
#include <string>
#include <fstream>
	
using namespace std;

#define CHAR_VAL(ACHAR) (ACHAR - 'A' + 1)
	
int
main(int argc, char **argv)
{
	ofstream fout ("ride.out");
	ifstream fin ("ride.in");
	string cometName, groupName;
	char *p;
	int cometVal, groupVal;
	
	while (fin >> cometName >> groupName)
	{
		cometVal = 1;
		groupVal = 1;
		//cout << "comet name:" << cometName << endl;
	    //cout << "group name:" << groupName << endl;
		for (p = &cometName[0]; *p; p++)
		{
		//	cout << "char:" << *p << "val:"  << CHAR_VAL(*p) << endl;
			cometVal *= CHAR_VAL(*p);
		//	cout << "comet value:" << cometVal << endl;
		}
		for (p = &groupName[0]; *p; p++)
		{
		//	cout << "char:" << *p << "val:"  << CHAR_VAL(*p) << endl;
			groupVal *= CHAR_VAL(*p);
		//	cout << "group value:" << groupVal << endl;
		}
		if (cometVal%47 == groupVal%47)
			fout << "GO" << endl;
		else
			fout << "STAY" << endl;	
	}
	fout.close();
	fin.close();
	return 0;
}
