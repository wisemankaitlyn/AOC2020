// day 10
// kaitlyn wiseman
// 12/10/2020


#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

bool isValid(vector<int> test);
string filename = "Day10.txt";

int main() {
	vector<int> joltages;
	joltages.push_back(0);  // joltage of outlet
	ifstream in;
	in.open(filename);

	while (!in.eof())
	{
		int temp;
		in >> temp;
		joltages.push_back(temp);
	}

	sort(joltages.begin(), joltages.end());

	// add joltage of device
	joltages.push_back(joltages.at(joltages.size() - 1) + 3);

	int oneJ = 0;
	int twoJ = 0;
	int thrJ = 0;

	for (int i = 0; i < joltages.size() - 1; i++)
	{
		int diff = joltages.at(i + 1) - joltages.at(i);
		
		if (diff == 3) thrJ++;
		else if (diff == 2) twoJ++;
		else if (diff == 1) oneJ++;
	}

	cout << "part 1: the output number is " << oneJ * thrJ << endl;

	int numValid = 1;
	vector<int> weights(joltages.size(), 0);


	for (int i = 0; i < joltages.size() - 1; i++)
	{
		if (i + 2 < joltages.size() && joltages.at(i + 2) - joltages.at(i) <= 3)
			weights.at(i + 2) += 1;
		if (i + 3 < joltages.size() && joltages.at(i + 3) - joltages.at(i) <= 3)
			weights.at(i + 2) += 2;
	}

	int tempVal = 0;
	long long outVal = 1;

	for (auto v : weights)
	{
		tempVal += v;
		if (tempVal != 0 && v == 0)
		{
			if (tempVal == 1)
				outVal *= 2;
			else
				outVal *= tempVal;
			tempVal = 0;
		}
	}
	
	cout << "part 2: " << outVal << endl;

	return 0;
}

bool isValid(vector<int> test)
{
	for (int i = 0; i < test.size() - 1; i++)
	{
		if (test.at(i + 1) - test.at(i) > 3) return false;
	}
	return true;
}
