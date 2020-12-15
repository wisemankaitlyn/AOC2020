// day 15
// kaitlyn wiseman
// 12/15/2020

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

struct Pair {
	int index;
	int val;
};



int main()
{
	vector<int> vals = { 6,19,0,5,7,13,1 };
	vector<int> valInd(40000000, -1);
	for(int i = 0; i < vals.size(); i++)
	{
		valInd.at(vals.at(i)) = i;
	}

	bool PART1 = false;
	int size = vals.size();
	int limit = 0;
	if (PART1) limit = 2020;
	else limit = 30000000;

	Pair nextVal;
	nextVal.index = vals.size();
	nextVal.val = 0;
	
	for (int i = size + 1; i < limit; i++)
	{
		if (valInd.at(nextVal.val) != -1)  // it's been done before
		{
			// the next number is the difference between the current index and the last time 
			// the number was spoken
			int temp = nextVal.val;
			nextVal.val = nextVal.index - valInd.at(temp);
			valInd.at(temp) = nextVal.index;
			nextVal.index = i;
		}
		else  // it's the first time
		{
			// add the new val (+ ind) to the num vector
			valInd.at(nextVal.val) = nextVal.index;

			// make nextVal val = 0, index current i
			nextVal.val = 0;
			nextVal.index = i;
		}
	}

	if (valInd.at(nextVal.val) != -1)  // it's been done before
	{
		// the next number is the difference between the current index and the last time 
		// the number was spoken
		int temp = nextVal.val;
		//nextVal.val = nextVal.index - valInd.at(temp);
		valInd.at(temp) = nextVal.index;
		//nextVal.index = i;
		cout << nextVal.val << endl;
	}
	else  // it's the first time
	{
		// add the new val (+ ind) to the num vector
		valInd.at(nextVal.val) = nextVal.index;

		// make nextVal val = 0, index current i
		//nextVal.val = 0;
		//nextVal.index = i;
		cout << nextVal.val << endl;
	}

	return 0;
}