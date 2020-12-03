// day 3
// kaitlyn wiseman
// 12/03/2020

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

int numTreesHit(int right, int down, vector<string> trail);

int main()
{
	vector<string> trail;

	ifstream in;
	in.open("Day3.txt");
	while (!in.eof())
	{
		string line;
		getline(in, line, '\n');
		trail.push_back(line);
	}
	in.close();

	int numTreesP1 = numTreesHit(3, 1, trail);

	cout << "part 1: the number of trees encountered was " << numTreesP1 << "." << endl;

	// Part 2
	int R1D1 = numTreesHit(1, 1, trail);
	int R3D1 = numTreesHit(3, 1, trail);
	int R5D1 = numTreesHit(5, 1, trail);
	int R7D1 = numTreesHit(7, 1, trail);
	int R1D2 = numTreesHit(1, 2, trail);

	cout << "Part 2:" << endl;
	cout << "Right 1 down 1: " << R1D1 << endl;
	cout << "Right 3 down 1: " << R3D1 << endl;
	cout << "Right 5 down 1: " << R5D1 << endl;
	cout << "Right 7 down 1: " << R7D1 << endl;
	cout << "Right 1 down 2: " << R1D2 << endl;
	cout << "The product of these is " 
		 << (long long)R1D1 * (long long)R3D1 * (long long)R5D1 * (long long)R7D1 * (long long)R1D2;

	return 0;
}

int numTreesHit(int right, int down, vector<string> trail)
{
	int row = 0;
	int col = 0;
	int numTrees = 0;
	if (trail.at(row).at(col) == '#')
		numTrees++;

	while (row < trail.size() - down)
	{
		row += down;
		col += right;
		if (col >= trail.at(row).length())
			col -= trail.at(row).length();

		if (trail.at(row).at(col) == '#')
			numTrees++;
	}

	return numTrees;
}