/*
ID: running1
PROG: milk2
LANG: C++
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
	
using namespace std;

#define MAX(X,Y) ((X>Y)?(X):(Y))
#define MIN(X,Y) ((X<Y)?(X):(Y))	

class Interval
{
public:
	Interval(){}
	Interval(int st, int et){SetVal(st, et);}
	int start;
	int end;
	int operator < (const Interval &m) const{
		return start < m.start;
	}
	void SetVal(int st, int et){
			this->start = st;
			this->end = et;
	}
	int GetVal(void){return this->end - this->start;}	
};
	
const int MAX_FARMERS = 5000;


int
main(int argc, char **argv)
{
	ofstream fout("milk2.out");
	ifstream fin("milk2.in");
	
	int n;
	vector< Interval > vect;
	
	fin >> n;
//	cout << n << endl;

	for (int i=0; i<n; i++)
	{
		Interval farmer;
		fin >> farmer.start >> farmer.end;
		vect.push_back(farmer);	
	}
//	for (int i=0; i<(int)vect.size(); i++)
//		cout << setw(2) << vect[i].start << " " << vect[i].end << endl;
//	sort(vect.begin(), vect.end());
//	for (int i=0; i<(int)vect.size(); i++)
//		cout << setw(2) << vect[i].start << " " << vect[i].end << endl;
		
	Interval milking = vect[0];
	Interval idling(0, 0);
	Interval maxMilking = milking;
	Interval maxIdling = idling;
	
	//cout << "milking: " << maxMilking.start << " " << maxMilking.end << endl;
	for(int i=1; i<n; i++)
	{
		//continuous milking 
		if (vect[i].start < milking.start)//continuous
		{
			milking.start = vect[i].start;	
			milking.end = MAX(milking.end, vect[i].end);
		}
		else if (vect[i].start > milking.end)
		{	
			milking.start = vect[i].start;
			milking.end = vect[i].end;	
			idling.start = milking.end;
			idling.end = vect[i].start;
		}
		else if(vect[i].end > milking.end)
		{
			milking.end = vect[i].end;	
		}
		
		if (milking.GetVal() > maxMilking.GetVal())
				maxMilking = milking;
		//cout << maxMilking.start << " " << maxMilking.end << endl;
	}
	
	//cout << maxMilking.GetVal() << " " << maxIdling.GetVal() << endl;
	fout << maxMilking.GetVal() << " " << maxIdling.GetVal() << endl;
	
	fout.close();
	fin.close();
	return 0;	
}
