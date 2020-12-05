// day 5
// kaitlyn wiseman
// 12/05/2020

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

int main() {
	ifstream in;
	in.open("Day5.txt");
	vector<string> passes;
	vector<int> seatIDs;

	while (!in.eof())
	{
		string temp;
		in >> temp;
		passes.push_back(temp);
	}

	int highRow = 127;
	int lowRow = 0;
	int highCol = 7;
	int lowCol = 0;
	for (string pass : passes)
	{
		for (char c : pass)
		{
			switch (c) {
				case 'F':  // take the lower half; rows
					highRow = ((highRow - lowRow) / 2) + lowRow;
					break;
				case 'B':  // take the higher half; rows
					lowRow = ((highRow - lowRow) / 2) + lowRow;
					break;
				case 'L':  // take the lower half; cols
					highCol = ((highCol - lowCol) / 2) + lowCol;
					break;
				case 'R':  // take the higher half; cols
					lowCol = ((highCol - lowCol) / 2) + lowCol;
					break;
			}
		}
		seatIDs.push_back(highRow * 8 + highCol);
		highRow = 127;
		lowRow = 0;
		highCol = 7;
		lowCol = 0;
	}

	int highestID = seatIDs.at(0);
	for (int ID : seatIDs)
	{
		if (ID > highestID)
		{
			highestID = ID;
		}
	}

	cout << "Part 1: Highest id: " << highestID << endl;
	int myID = -1;
	for (int ID : seatIDs)
	{
		if (find(seatIDs.begin(), seatIDs.end(), ID + 1) == seatIDs.end() && find(seatIDs.begin(), seatIDs.end(), ID + 2) != seatIDs.end())
		{
			myID = ID + 1;
			break;
		}
		else if (find(seatIDs.begin(), seatIDs.end(), ID - 1) == seatIDs.end() && find(seatIDs.begin(), seatIDs.end(), ID - 2) != seatIDs.end())
		{
			myID = ID - 1;
			break;
		}
	}

	cout << "Part 2: my id is: " << myID;

}