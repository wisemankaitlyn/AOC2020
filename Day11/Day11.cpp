// day 11
// kaitlyn wiseman
// 12/11/2020

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;
string filename = "Day11.txt";

int main() {
	vector<string> lines;
	ifstream in;

	in.open(filename);
	while (!in.eof())
	{
		string temp;
		getline(in, temp, '\n');
		lines.push_back(temp);
	}
	// lines.at(y).at(x);

	vector<string> b2 = lines;  // for pt 2 

	bool changing = true;
	while (changing)
	{
		changing = false;
		vector<string> newBoard = lines;
		for (int y = 0; y < lines.size(); y++)
		{
			for (int x = 0; x < lines.at(0).size(); x++)
			{
				int numOcc = 0;
				switch (lines.at(y).at(x))
				{
					case 'L':  // if there are no occupied seats adjacent to it,
						       // the seat becomes occupied, '#'.
						if ( ((y == 0 || x == 0) || (y > 0 && x > 0 && lines.at(y - 1).at(x - 1) != '#'))	 // UL
							&& (y == 0 || lines.at(y - 1).at(x) != '#')								   // UM
							&& ((y == 0 || x == lines.at(0).size() - 1) || (y > 0 && x < lines.at(0).size() - 1 && lines.at(y - 1).at(x + 1) != '#'))  // UR
							&& (x == 0 || lines.at(y).at(x - 1) != '#')  // L
							&& (x == lines.at(0).size() - 1 || lines.at(y).at(x + 1) != '#')  // R
							&& ((y == lines.size() - 1 || x == 0) || (y < lines.size() - 1 && x > 0 && lines.at(y + 1).at(x - 1) != '#'))  // LL
							&& (y == lines.size() - 1 || lines.at(y + 1).at(x) != '#')  // LM
							&& ((y == lines.size() - 1 || x == lines.at(0).size() - 1) || (y < lines.size() - 1 && x < lines.at(0).size() - 1 && lines.at(y + 1).at(x + 1) != '#'))
								)
						{
							changing = true;
							newBoard.at(y).at(x) = '#';
						}
						break;
					case '#':  // if four or more seats adjacent to it are also
							   // occupied, the seat becomes empty, 'L'.
						if (y > 0 && x > 0 && lines.at(y - 1).at(x - 1) == '#') numOcc++;
						if (y > 0 && lines.at(y - 1).at(x) == '#') numOcc++;
						if (y > 0 && x < lines.at(0).size() - 1 && lines.at(y - 1).at(x + 1) == '#') numOcc++;
						if (x > 0 && lines.at(y).at(x - 1) == '#') numOcc++;
						if (x < lines.at(0).size() - 1 && lines.at(y).at(x + 1) == '#') numOcc++;
						if (y < lines.size() - 1 && x > 0 && lines.at(y + 1).at(x - 1) == '#') numOcc++;
						if (y < lines.size() - 1 && lines.at(y + 1).at(x) == '#') numOcc++;
						if (y < lines.size() - 1 && x < lines.at(0).size() - 1 && lines.at(y + 1).at(x + 1) == '#') numOcc++;

						if (numOcc >= 4)
						{
							changing = true;
							newBoard.at(y).at(x) = 'L';
						}

						break;
					default:  // do nothing.
						break;
				}
			}
		}

		lines = newBoard;
	}

	int finNumOcc = 0;

	for (auto l : lines)
	{
		for (auto seat : l)
		{
			if (seat == '#') finNumOcc++;
		}
	}

	cout << "part 1: final number of occupied seats is " << finNumOcc << endl;


	// part 2

	changing = true;
	while (changing)
	{
		changing = false;
		vector<string> newBoard = b2;
		for (int y = 0; y < b2.size(); y++)
		{
			for (int x = 0; x < b2.at(0).size(); x++)
			{
				if (b2.at(y).at(x) == '.') continue;
				int numOcc = 0;
				// find out how many seats w/i sight are occupied
				// above
				for (int i = 1; y - i >= 0; i++)
				{
					if (b2.at(y - i).at(x) == 'L') break;
					else if (b2.at(y - i).at(x) == '#') {
						numOcc++; break;
					}
				}
				// below
				for (int i = 1; y + i <= b2.size() - 1; i++)
				{
					if (b2.at(y + i).at(x) == 'L') break;
					else if (b2.at(y + i).at(x) == '#') {
						numOcc++; break;
					}
				}
				// left
				for (int j = 1; x - j >= 0; j++)
				{
					if (b2.at(y).at(x - j) == 'L') break;
					else if (b2.at(y).at(x - j) == '#') {
						numOcc++; break;
					}
				}
				// right
				for (int j = 1; x + j <= b2.at(0).size() - 1; j++)
				{
					if (b2.at(y).at(x + j) == 'L') break;
					else if (b2.at(y).at(x + j) == '#') {
						numOcc++; break;
					}
				}
				// UL diag
				for (int i = 1; y - i >= 0 && x - i >= 0; i++)
				{
					if (b2.at(y - i).at(x - i) == 'L') break; 
					else if (b2.at(y - i).at(x - i) == '#') {
						numOcc++; break;
					}
				}
				// UR diag
				for (int i = 1; y - i >= 0 && x + i <= b2.at(0).size() - 1; i++)
				{
					if (b2.at(y - i).at(x + i) == 'L') break;
					else if (b2.at(y - i).at(x + i) == '#') {
						numOcc++; break;
					}
				}
				// LL diag
				for (int i = 1; (y + i <= b2.size() - 1 && x - i >= 0); i++)
				{
					if (b2.at(y + i).at(x - i) == 'L') break;
					else if (b2.at(y + i).at(x - i) == '#') {
						numOcc++; break;
					}
				}
				// LR diag
				for (int i = 1; y + i <= b2.size() - 1 && x + i <= b2.at(0).size() - 1; i++)
				{
					if (b2.at(y + i).at(x + i) == 'L') break;
					else if (b2.at(y + i).at(x + i) == '#') {
						numOcc++; break;
					}
				}


				switch (b2.at(y).at(x))
				{
				case 'L':  // if there are no occupied seats in sight of this seat,
						   // the seat becomes occupied, '#'.
					if (numOcc == 0)
					{
						changing = true;
						newBoard.at(y).at(x) = '#';
					}
					break;
				case '#':  // if four or more seats in sight are also
						   // occupied, the seat becomes empty, 'L'.
					if (numOcc >= 5)
					{
						changing = true;
						newBoard.at(y).at(x) = 'L';
					}
					break;
				default:  // do nothing.
					break;
				}
			}
		}

		b2 = newBoard;
	}
	
	finNumOcc = 0;
	for (auto l : b2)
	{
		for (auto seat : l)
		{
			if (seat == '#') finNumOcc++;
		}
	}

	cout << "part 2: the num of occupied seats is: " << finNumOcc;

	return 0;
}