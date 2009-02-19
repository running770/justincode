/*
ID: running1
PROG: friday
LANG: C++
*/
#include <iostream>
#include <fstream>
	
using namespace std;

enum WEEK_DAY
{
	Sunday = 0,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	WEEK_DAY_NUM		
};
const int monthDay[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const int BEGIN_YEAR = 1900;
const int BEGIN_DAY = Monday;
const int RANGE_MAX = 400; 
const int theDate = 13;

#define LEAP_YEAR(Y) ((0==Y%400) || ((0==year%4)&&(0!=year%100))) 

int
main(int argc, char **argv)
{
	ofstream fout ("friday.out");
	ifstream fin ("friday.in");
	
	int n;
	int dayOf13[WEEK_DAY_NUM]={0};
	int daysCount = 13; 
	int daysOfMonth;
	
	fin >> n;
	//the first month of 1900
	++dayOf13[daysCount%7];
	for (int year=BEGIN_YEAR; year<BEGIN_YEAR+n; year++)
	{
		//Feb.13 = daysCount + days Of Jan; Mar.13 = daysCount + days Of Feb ......
		for (int month=1; month<=12; month++)
		{
			if (month > 12)
				month = 1;
			if (2 == month && LEAP_YEAR(year))
				daysOfMonth = 29;
			else	
				daysOfMonth = monthDay[month];
			daysCount += daysOfMonth;
			++dayOf13[daysCount%7];
		} 	
	}
	//minus the day: Jan 13 BEGIN_YEAR+n
	--dayOf13[daysCount%7];
	
	fout << dayOf13[Saturday];
	for(int i=Sunday; i<Saturday; i++)
		fout << " " << dayOf13[i];
	fout << endl;
	fout.close();
	fin.close();
	return 0;	
}
