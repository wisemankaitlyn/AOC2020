// day 24
// kaitlyn wiseman
// 12/25/2020

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main()
{
	vector<bool> t(300, true);
	vector<vector<bool>> u(300, t);
	vector<vector<vector<bool>>> grid(300, u);  // starting position is (150, 150, 150)

	// grid.at(x).at(y).at(z);

	string temp;
	ifstream in;
	in.open("Day24.txt");
	int numBlk = 0;

	while (!in.eof())
	{
		in >> temp;  // get tile line

		int x = 150;
		int y = 150;
		int z = 150;

		for (int i = 0; i < temp.size(); i++)
		{
			switch (temp.at(i))
			{
				case 'e':
					y--;
					x++;
					break;
				case 'w':
					y++;
					x--;
					break;
				case 'n':
					if (temp.at(i + 1) == 'e')
					{
						z--;
						x++;
					}
					else  // == 'w'
					{
						z--;
						y++;
					}
					i++;
					break;
				case 's':
					if (temp.at(i + 1) == 'e')
					{
						z++;
						y--;
					}
					else  // == 'w'
					{
						x--;
						z++;
					}
					i++;
					break;
				default:
					break;
			}
		}

		grid.at(x).at(y).at(z) = !grid.at(x).at(y).at(z);
		if (grid.at(x).at(y).at(z)) numBlk--;
		else numBlk++;
	}

	std::cout << "part 1: the number of black tiles is " << numBlk << endl;

	vector<vector<vector<bool>>> nextGrid = grid;

	for (int i = 0; i < 100; i++)
	{
		for (int x = 120 - i; x < 179 + i; x++)
		{
			for (int y = 120 - i; y < 179 + i; y++)
			{
				for (int z = 120 - i; z < 179 + i; z++)
				{
					int numAdjBlk = 0;
					if (!grid.at(x + 1).at(y).at(z - 1)) numAdjBlk++;
					if (!grid.at(x + 1).at(y - 1).at(z)) numAdjBlk++;
					if (!grid.at(x).at(y - 1).at(z + 1)) numAdjBlk++;
					if (!grid.at(x - 1).at(y).at(z + 1)) numAdjBlk++;
					if (!grid.at(x - 1).at(y + 1).at(z)) numAdjBlk++;
					if (!grid.at(x).at(y + 1).at(z - 1)) numAdjBlk++;

					if (!grid.at(x).at(y).at(z)
						&& (numAdjBlk == 0 || numAdjBlk > 2))
					{
						nextGrid.at(x).at(y).at(z) = true;
					}
					else if (grid.at(x).at(y).at(z)
						&& numAdjBlk == 2)
					{
						nextGrid.at(x).at(y).at(z) = false;
					}
				}
			}
		}

		grid = nextGrid;
	}

	numBlk = 0;

	for (auto a : grid)
		for (auto b : a)
			for (auto c : b)
				if (!c) numBlk++;

	std::cout << "part 2: the number of black tiles after 100 days is " << numBlk << endl;

	return 0;
}