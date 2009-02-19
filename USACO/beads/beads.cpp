/*
ID: running1
PROG: beads
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
	
using namespace std;

//#define DEBUG


int CollectFirstLeftBeads(string s, int length, int startPos);
int CollectRightBeads(string s, int length, int startPos);
int CollectBeads(string s, int length);
int
main(int argc, char **argv)
{
	ofstream fout("beads.out");
	ifstream fin("beads.in");
	
	int n;
	string necklace;
	
#ifdef DEBUG	
	while (fin >> n >> necklace)
	{
		cout << n << endl << necklace << endl;
		cout << CollectBeads(necklace, n) << endl;
	}
#else
	fin >> n >> necklace;
	fout << CollectBeads(necklace, n) << endl;	
#endif		
	fout.close();
	fin.close();
	return 0;	
}

int 
CollectFirstLeftBeads(string s, int length, int startPos)
{
	int count = 0;
	int i = startPos;
	int color;

	while (s[i] == 'w')
	{
		++count;
		--i;
		if (i < 0)
			i = length - 1;
	}
	color = s[i];
//	cout << i << count << s[i] << endl;
	while (s[i] == color || s[i] == 'w')
	{
		++count;
		--i;
		if (i < 0)
			i = length - 1;
	}
	
//	cout << "CollectFirstLeftBeads:" << count << endl;

	return count;
}

int 
CollectRightBeads(string s, int length, int startPos)
{
	int count = 0;
	int i = startPos;
	int color;
	
	while (s[i] == 'w')
	{
	//	cout << "i:" << i << " color:" << s[i] << endl;
		++count;
		++i;
	}
	color = s[i];
	while (s[i] == color || s[i] == 'w')
	{
	//	cout << "i:" << i << " color:" << s[i] << endl;
		++count;
		++i;
		if (i >= length)
			i = 0;
	}	
	//cout << "CollectRightBeads:" << count << endl;
	return count;
}
int CollectBeads(string s, int length)
{
	int maxSeriesBeads = 0;
	int posBroken = 0;
	int pos=0;
	int left, right;
	int redBeginPos = s.find("r");
	int blueBeginPos = s.find("b");
	
	//cout << redBeginPos << " " << blueBeginPos << endl;
	if ((-1)==redBeginPos || (-1)==blueBeginPos)
	{
		return length;
	}
	
	if (redBeginPos < blueBeginPos)
		pos = blueBeginPos - 1;
	else pos = redBeginPos - 1;
	
	int firstLeft = CollectFirstLeftBeads(s, length, pos);
	left = firstLeft;
	int newEnding = length - (firstLeft-pos-1);
	//cout << "new n :" << newEnding << endl;
	int i = pos;
	
	while( i<newEnding )
	{
		if (i >= length-1)
			break;
		right = CollectRightBeads(s, length, i+1);
		//cout << "total:" << left+right << " max:" << maxSeriesBeads << endl;
		if (left+right > maxSeriesBeads)
		{
			maxSeriesBeads = left+right;
			posBroken = i;
		}
		i = i+right;
		if (i > newEnding)
			break;
		left = right;
		//reback to the beads which is not 'w'
		while (s[i] == 'w')
		{	
			--i;
			--left;
		}
			
	}
	
	return maxSeriesBeads;	
}
