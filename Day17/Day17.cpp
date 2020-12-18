// day 17
// kaitlyn wiseman
// 12/18/2020


#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

int main()
{
	vector<vector<string>> grid(15);  // grid.at(z).at(y).at(x)  z = 7 is the initial layer (normally zero)
	ifstream in;
	in.open("Day17.txt");
	string temp;
	in >> temp;
	for (int i = 0; i < 7; i++)
	{
		grid.at(7).push_back(string(22, '.'));
	}
	while (!in.eof())
	{
		grid.at(7).push_back(string(7, '.') + temp + string(7, '.'));
		in >> temp;
	}
	grid.at(7).push_back(string(7, '.') + temp + string(7, '.'));
	for (int i = 0; i < 7; i++)
	{
		grid.at(7).push_back(string(22, '.'));
	}

	vector<string> emptGrd;
	for (int i = 0; i < 22; i++)
	{
		emptGrd.push_back(string(22, '.'));
	}

	for (int i = 0; i < 7; i++)
	{
		grid.at(i) = emptGrd;
	}
	for (int i = 8; i < 15; i++)
	{
		grid.at(i) = emptGrd;
	}

	// END GRID SET UP
	// BEGIN SIMULATION

	for (int t = 0; t < 6; t++)
	{
		vector<vector<string>> nxtGrd(15);
		for (int i = 0; i < nxtGrd.size(); i++)
		{
			nxtGrd.at(i) = emptGrd;
		}

		for (int z = 1; z < grid.size() - 1; z++)
		{
			for (int y = 1; y < grid.at(0).size() - 1; y++)
			{
				for (int x = 1; x < grid.at(0).at(0).size() - 1; x++)
				{
					int numAct = 0;

					for (int zz = z - 1; zz <= z + 1; zz++)
					{
						for (int yy = y - 1; yy <= y + 1; yy++)
						{
							for (int xx = x - 1; xx <= x + 1; xx++)
							{
								if (zz == z && yy == y && xx == x) continue;

								if (grid.at(zz).at(yy).at(xx) == '#') numAct++;
							}
						}
					}

					switch (grid.at(z).at(y).at(x))
					{
						case '.':
							if (numAct == 3) nxtGrd.at(z).at(y).at(x) = '#';
							break;
						case '#':
							if (numAct == 2 || numAct == 3) nxtGrd.at(z).at(y).at(x) = '#';
							break;
						default:
							break;
					}
				}
			}
		}

		grid = nxtGrd;
	}

	long numAct = 0;
	for (auto plane : grid)
	{
		for (auto line : plane)
		{
			for (auto c : line)
			{
				if (c == '#') numAct++;
			}
		}
	}

	cout << "part 1: num active at the end is: " << numAct << endl;

	// PART 2:
	vector<vector<vector<string>>> grid2(15);  //grid.at(w).at(z).at(y).at(x)
	in.close();
	in.open("Day17.txt");
	in >> temp;

	vector<vector<string>> emptGrdGrd(15);
	for (int i = 0; i < emptGrdGrd.size(); i++)
	{
		emptGrdGrd.at(i) = emptGrd;
	}
	for (int i = 0; i < grid2.size(); i++)
	{
		grid2.at(i) = emptGrdGrd;
	}
	
	int fgh = 7;
	while (!in.eof())
	{
		grid2.at(7).at(7).at(fgh) = (string(7, '.') + temp + string(7, '.'));
		in >> temp;
		fgh++;
	}
	grid2.at(7).at(7).at(fgh) = (string(7, '.') + temp + string(7, '.'));


	// END GRID SET UP
	// BEGIN SIMULATION

	for (int t = 0; t < 6; t++)
	{
		vector<vector<string>> nxtGrd(15);
		for (int i = 0; i < nxtGrd.size(); i++)
		{
			nxtGrd.at(i) = emptGrd;
		}
		vector<vector<vector<string>>> nxtGrd2(15);
		for (int i = 0; i < nxtGrd2.size(); i++)
		{
			nxtGrd2.at(i) = nxtGrd;
		}

		for (int w = 1; w < grid2.size() - 1; w++)
		{
			for (int z = 1; z < grid2.at(0).size() - 1; z++)
			{
				for (int y = 1; y < grid2.at(0).at(0).size() - 1; y++)
				{
					for (int x = 1; x < grid2.at(0).at(0).at(0).size() - 1; x++)
					{
						int numAct = 0;

						for (int ww = w - 1; ww <= w + 1; ww++)
						{
							for (int zz = z - 1; zz <= z + 1; zz++)
							{
								for (int yy = y - 1; yy <= y + 1; yy++)
								{
									for (int xx = x - 1; xx <= x + 1; xx++)
									{
										if (ww == w && zz == z && yy == y && xx == x) continue;

										if (grid2.at(ww).at(zz).at(yy).at(xx) == '#') numAct++;
									}
								}
							}
						}

						switch (grid2.at(w).at(z).at(y).at(x))
						{
						case '.':
							if (numAct == 3) nxtGrd2.at(w).at(z).at(y).at(x) = '#';
							break;
						case '#':
							if (numAct == 2 || numAct == 3) nxtGrd2.at(w).at(z).at(y).at(x) = '#';
							break;
						default:
							break;
						}
					}
				}
			}
		}

		grid2 = nxtGrd2;
	}

	numAct = 0;
	for (auto field : grid2)
	{
		for (auto plane : field)
		{
			for (auto line : plane)
			{
				for (auto c : line)
				{
					if (c == '#') numAct++;
				}
			}
		}
	}
	
	cout << "part 2: the number active at the end is " << numAct;

	return 0;
}