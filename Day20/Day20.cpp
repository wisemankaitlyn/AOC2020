// day 20
// kaitlyn wiseman
// 12/20/2020

#include<iostream>
#include<string>
#include<fstream>
#include<vector>

#define TOP 0
#define BOTTOM 1
#define LEFT 2
#define RIGHT 3

using namespace std;


struct Tile {
	int ID;
	vector<string> matrix;
	int orient = 0;
	bool isFrozen = false;
};

void rotate_right(vector<string>* m);
void flip_about_x(vector<string>* m);
void flip_about_y(vector<string>* m);
string get_left_side(vector<string>* m);
string get_right_side(vector<string>* m);


int main() {
	vector<Tile> t;
	ifstream in;
	in.open("Day20.txt");
	string temp;
	int ti;
	vector<int> corners;

	in >> temp;
	while (!in.eof())
	{
		Tile tile;
		in >> ti;
		tile.ID = ti;
		tile.matrix.resize(10);
		in >> temp; // get rid of :
		for (int i = 0; i < 10; i++)
		{
			in >> tile.matrix.at(i);
		}
		t.push_back(tile);
		in >> temp;
	}

	// to find the four corner tiles, find the four tiles who have two sides that don't match
	// a side on another tile

	long long ans = 1;
	for (int i = 0; i < t.size(); i++)
	{
		// SIDE 1
		vector<string> side(4);
		side.at(0) = (t.at(i).matrix.at(0));
		vector<string> rside(4);
		rside.at(0) = side.at(0);
		reverse(rside.at(0).begin(), rside.at(0).end());

		// SIDE 2
		side.at(1) = t.at(i).matrix.at(t.at(i).matrix.size() - 1);
		rside.at(1) = side.at(1);
		reverse(rside.at(1).begin(), rside.at(1).end());

		// SIDE 3
		side.at(2) = "";
		for (auto s : t.at(i).matrix)
		{
			side.at(2) += s.at(0);
		}
		rside.at(2) = side.at(2);
		reverse(rside.at(2).begin(), rside.at(2).end());

		// SIDE 4
		side.at(3) = "";
		for (auto s : t.at(i).matrix)
		{
			side.at(3) += s.at(s.size() - 1);
		}
		rside.at(3) = side.at(3);
		reverse(rside.at(3).begin(), rside.at(3).end());


		int matches = 0;

		for (int j = 0; j < i; j++)
		{
			string ls = "";
			for (auto s : t.at(j).matrix)
			{
				ls += s.at(0);
			}
			string rs = "";
			for (auto s : t.at(j).matrix)
			{
				rs += s.at(s.size() - 1);
			}

			for (auto s : side)
			{
				if (t.at(j).matrix.at(0) == s
					|| t.at(j).matrix.at(t.at(j).matrix.size() - 1) == s
					|| ls == s || rs == s)
					matches++;
			}
			for (auto s : rside)
			{
				if (t.at(j).matrix.at(0) == s
					|| t.at(j).matrix.at(t.at(j).matrix.size() - 1) == s
					|| ls == s || rs == s)
					matches++;
			}
			
		}
		for (int j = i + 1; j < t.size(); j++)
		{
			string ls = "";
			for (auto s : t.at(j).matrix)
			{
				ls += s.at(0);
			}
			string rs = "";
			for (auto s : t.at(j).matrix)
			{
				rs += s.at(s.size() - 1);
			}

			for (auto s : side)
			{
				if (t.at(j).matrix.at(0) == s
					|| t.at(j).matrix.at(t.at(j).matrix.size() - 1) == s
					|| ls == s || rs == s)
					matches++;
			}
			for (auto s : rside)
			{
				if (t.at(j).matrix.at(0) == s
					|| t.at(j).matrix.at(t.at(j).matrix.size() - 1) == s
					|| ls == s || rs == s)
					matches++;
			}
		}

		if (matches == 2)
		{
			ans *= t.at(i).ID;
			corners.push_back(i);
		}
	}


	cout << "part 1: the answer is: " << ans << endl;

	// part 2 (save me)
	vector<int> lol(12, -1);
	vector<string> image(400, "");
	vector<vector<int>> grid(12, lol);   // grid.at(y).at(x) ugh

	// orient corners.at(0) as top right corner
	int trc = corners.at(0);
	grid.at(0).at(0) = trc;
	vector<int> n;
	
	n.push_back(108);
	n.push_back(120);  // because i am a tired cheater
	bool oriented = false;


	for (int i = 0; i < 4; i++)
	{
		string right = get_right_side(&(t.at(trc).matrix));
		string bottom = t.at(trc).matrix.back();

		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				string left = get_left_side(&(t.at(n.at(0)).matrix));
				string top = t.at(n.at(1)).matrix.at(0);

				if (right == left && bottom == top)
				{
					oriented = true;
					break;
				}

				rotate_right(&(t.at(n.at(0)).matrix));
			}

			if (oriented) break;

			flip_about_x(&(t.at(n.at(0)).matrix));

			for (int k = 0; k < 4; k++)
			{
				string left = get_left_side(&(t.at(n.at(0)).matrix));
				string top = t.at(n.at(1)).matrix.at(0);

				if (right == left && bottom == top)
				{
					oriented = true;
					break;
				}

				rotate_right(&(t.at(n.at(0)).matrix));
			}

			if (oriented) break;

			rotate_right(&(t.at(n.at(1)).matrix));
		}

		if (!oriented)
		{
			flip_about_x(&(t.at(n.at(1)).matrix));
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					string left = get_left_side(&(t.at(n.at(0)).matrix));
					string top = t.at(n.at(1)).matrix.at(0);

					if (right == left && bottom == top)
					{
						oriented = true;
						break;
					}

					rotate_right(&(t.at(n.at(0)).matrix));
				}

				if (oriented) break;

				flip_about_x(&(t.at(n.at(0)).matrix));

				for (int k = 0; k < 4; k++)
				{
					string left = get_left_side(&(t.at(n.at(0)).matrix));
					string top = t.at(n.at(1)).matrix.at(0);

					if (right == left && bottom == top)
					{
						oriented = true;
						break;
					}

					rotate_right(&(t.at(n.at(0)).matrix));
				}

				if (oriented) break;

				rotate_right(&(t.at(n.at(1)).matrix));
			}
		}

		if (!oriented)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					string left = get_left_side(&(t.at(n.at(1)).matrix));
					string top = t.at(n.at(0)).matrix.at(0);

					if (right == left && bottom == top)
					{
						oriented = true;
						break;
					}

					rotate_right(&(t.at(n.at(1)).matrix));
				}

				if (oriented) break;

				flip_about_x(&(t.at(n.at(1)).matrix));

				for (int k = 0; k < 4; k++)
				{
					string left = get_left_side(&(t.at(n.at(1)).matrix));
					string top = t.at(n.at(0)).matrix.at(0);

					if (right == left && bottom == top)
					{
						oriented = true;
						break;
					}

					rotate_right(&(t.at(n.at(1)).matrix));
				}

				if (oriented) break;

				rotate_right(&(t.at(n.at(0)).matrix));
			}

			
		}

		if (!oriented)
		{
			flip_about_x(&(t.at(n.at(0)).matrix));
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					string left = get_left_side(&(t.at(n.at(1)).matrix));
					string top = t.at(n.at(0)).matrix.at(0);

					if (right == left && bottom == top)
					{
						oriented = true;
						break;
					}

					rotate_right(&(t.at(n.at(1)).matrix));
				}

				if (oriented) break;

				flip_about_x(&(t.at(n.at(1)).matrix));

				for (int k = 0; k < 4; k++)
				{
					string left = get_left_side(&(t.at(n.at(1)).matrix));
					string top = t.at(n.at(0)).matrix.at(0);

					if (right == left && bottom == top)
					{
						oriented = true;
						break;
					}

					rotate_right(&(t.at(n.at(1)).matrix));
				}

				if (oriented) break;

				rotate_right(&(t.at(n.at(0)).matrix));
			}
		}

		if (oriented) break;

		rotate_right(&(t.at(trc).matrix));
	}

	if (!oriented) {
		flip_about_x(&(t.at(trc).matrix));

		for (int i = 0; i < 4; i++)
		{
			string right = get_right_side(&(t.at(trc).matrix));
			string bottom = t.at(trc).matrix.back();

			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					string left = get_left_side(&(t.at(n.at(0)).matrix));
					string top = t.at(n.at(1)).matrix.at(0);

					if (right == left && bottom == top)
					{
						oriented = true;
						break;
					}

					rotate_right(&(t.at(n.at(0)).matrix));
				}

				if (oriented) break;

				flip_about_x(&(t.at(n.at(0)).matrix));

				for (int k = 0; k < 4; k++)
				{
					string left = get_left_side(&(t.at(n.at(0)).matrix));
					string top = t.at(n.at(1)).matrix.at(0);

					if (right == left && bottom == top)
					{
						oriented = true;
						break;
					}

					rotate_right(&(t.at(n.at(0)).matrix));
				}

				if (oriented) break;

				rotate_right(&(t.at(n.at(1)).matrix));
			}

			if (!oriented)
			{
				flip_about_x(&(t.at(n.at(1)).matrix));
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						string left = get_left_side(&(t.at(n.at(0)).matrix));
						string top = t.at(n.at(1)).matrix.at(0);

						if (right == left && bottom == top)
						{
							oriented = true;
							break;
						}

						rotate_right(&(t.at(n.at(0)).matrix));
					}

					if (oriented) break;

					flip_about_x(&(t.at(n.at(0)).matrix));

					for (int k = 0; k < 4; k++)
					{
						string left = get_left_side(&(t.at(n.at(0)).matrix));
						string top = t.at(n.at(1)).matrix.at(0);

						if (right == left && bottom == top)
						{
							oriented = true;
							break;
						}

						rotate_right(&(t.at(n.at(0)).matrix));
					}

					if (oriented) break;

					rotate_right(&(t.at(n.at(1)).matrix));
				}
			}

			if (!oriented)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						string left = get_left_side(&(t.at(n.at(1)).matrix));
						string top = t.at(n.at(0)).matrix.at(0);

						if (right == left && bottom == top)
						{
							oriented = true;
							break;
						}

						rotate_right(&(t.at(n.at(1)).matrix));
					}

					if (oriented) break;

					flip_about_x(&(t.at(n.at(1)).matrix));

					for (int k = 0; k < 4; k++)
					{
						string left = get_left_side(&(t.at(n.at(1)).matrix));
						string top = t.at(n.at(0)).matrix.at(0);

						if (right == left && bottom == top)
						{
							oriented = true;
							break;
						}

						rotate_right(&(t.at(n.at(1)).matrix));
					}

					if (oriented) break;

					rotate_right(&(t.at(n.at(0)).matrix));
				}


			}

			if (!oriented)
			{
				flip_about_x(&(t.at(n.at(0)).matrix));
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						string left = get_left_side(&(t.at(n.at(1)).matrix));
						string top = t.at(n.at(0)).matrix.at(0);

						if (right == left && bottom == top)
						{
							oriented = true;
							break;
						}

						rotate_right(&(t.at(n.at(1)).matrix));
					}

					if (oriented) break;

					flip_about_x(&(t.at(n.at(1)).matrix));

					for (int k = 0; k < 4; k++)
					{
						string left = get_left_side(&(t.at(n.at(1)).matrix));
						string top = t.at(n.at(0)).matrix.at(0);

						if (right == left && bottom == top)
						{
							oriented = true;
							break;
						}

						rotate_right(&(t.at(n.at(1)).matrix));
					}

					if (oriented) break;

					rotate_right(&(t.at(n.at(0)).matrix));
				}
			}

			if (oriented) break;

			rotate_right(&(t.at(trc).matrix));
		}
	}

	// we should now be oriented.

	for (int i = 0; i < 10; i++)
	{
		image.at(i) += t.at(trc).matrix.at(i);
	}

	if (t.at(trc).matrix.back() == t.at(n.at(0)).matrix.front())
	{
		for (int i = 0; i < 10; i++)
		{
			image.at(i) += t.at(n.at(1)).matrix.at(i);
		}
		for (int i = 10; i < 20; i++)
		{
			image.at(i) += t.at(n.at(0)).matrix.at(i - 10);
		}
		grid.at(0).at(1) = n.at(1);
		grid.at(1).at(0) = n.at(0);
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			image.at(i) += t.at(n.at(0)).matrix.at(i);
		}
		for (int i = 10; i < 20; i++)
		{
			image.at(i) += t.at(n.at(1)).matrix.at(i - 10);
		}
		grid.at(0).at(1) = n.at(0);
		grid.at(1).at(0) = n.at(1);
	}
	
	// let's get started with the rest of the tiles.
	grid.at(0).at(0) = 41;
	grid.at(1).at(0) = 108;
	t.at(trc).isFrozen = true;
	t.at(41).isFrozen = true;
	t.at(108).isFrozen = true;

	for (int y = 0; y < 12; y++)
	{
		
		// find first in row
		if (grid.at(y).at(0) == -1)
		{
			string bottom = t.at(grid.at(y - 1).at(0)).matrix.back();

			oriented = false;

			for (int i = 0; i < t.size(); i++)
			{
				if (i == grid.at(y - 1).at(0)) continue;
				if (t.at(i).isFrozen) continue;

				for (int j = 0; j < 4; j++)
				{
					string top = t.at(i).matrix.at(0);

					if (top == bottom)
					{
						oriented = true;
						break;
					}
					rotate_right(&(t.at(i).matrix));
				}

				if (!oriented)
				{
					flip_about_x(&(t.at(i).matrix));

					for (int j = 0; j < 4; j++)
					{
						string top = t.at(i).matrix.at(0);

						if (top == bottom)
						{
							oriented = true;
							break;
						}
						rotate_right(&(t.at(i).matrix));
					}
				}

				if (oriented)
				{
					grid.at(y).at(0) = i;
					t.at(i).isFrozen = true;
					break;
				}
				
			}
			for (int i = 0; i < 10; i++)
			{
				image.at(10 * y + i) += t.at(grid.at(y).at(0)).matrix.at(i);
			}
		}

		for (int x = 1; x < 12; x++)
		{
			if (grid.at(y).at(x) != -1) continue;

			int lstInd = grid.at(y).at(x - 1);
			if (lstInd == -1) break;
			string right = get_right_side(&(t.at(lstInd).matrix));
			oriented = false;

			for (int i = 0; i < t.size(); i++)
			{
				if (i == lstInd) continue;
				if (t.at(i).isFrozen) continue;

				for (int j = 0; j < 4; j++)
				{
					string left = get_left_side(&(t.at(i).matrix));

					if (right == left)
					{
						oriented = true;
						break;
					}

					rotate_right(&(t.at(i).matrix));
				}

				if (!oriented)
				{
					flip_about_x(&(t.at(i).matrix));

					for (int j = 0; j < 4; j++)
					{
						string left = get_left_side(&(t.at(i).matrix));

						if (right == left)
						{
							oriented = true;
							break;
						}

						rotate_right(&(t.at(i).matrix));
					}
				}

				if (oriented)
				{
					grid.at(y).at(x) = i;
					t.at(i).isFrozen = true;
					break;
				}
			}

			for (int i = 0; i < 10; i++)
			{
				image.at(10 * y + i) += t.at(grid.at(y).at(x)).matrix.at(i);
			}
		}
	}

	
	image.resize(120);

	// remove borders
	for (int i = 119; i > 0; i -= 10)
	{
		image.erase(image.begin() + i);
		image.erase(image.begin() + i - 9);
	}

	for (int j = 0; j < image.size(); j++)
	{
		for (int i = 119; i > 0; i -= 10)
		{
			image.at(j).erase(image.at(j).begin() + i);
			image.at(j).erase(image.at(j).begin() + i - 9);
		}
	}

	cout << "done removing borders !" << endl;

	// find monsters :)

	int numMonsters = 0;  // :)

	for (int k = 0; k < 4; k++)
	{
		for (int i = 1; i < image.size() - 1; i++)
		{
			for (int j = 0; j < image.at(i).size() - 19; j++)
			{
				if (image.at(i).at(j) != '#') continue;

				if (image.at(i + 1).at(j + 1) != '#') continue;

				if (image.at(i + 1).at(j + 4) != '#') continue;

				if (image.at(i).at(j + 5) != '#') continue;

				if (image.at(i).at(j + 6) != '#') continue;

				if (image.at(i + 1).at(j + 7) != '#') continue;

				if (image.at(i + 1).at(j + 10) != '#') continue;

				if (image.at(i).at(j + 11) != '#') continue;

				if (image.at(i).at(j + 12) != '#') continue;

				if (image.at(i + 1).at(j + 13) != '#') continue;

				if (image.at(i + 1).at(j + 16) != '#') continue;

				if (image.at(i).at(j + 17) != '#') continue;

				if (image.at(i).at(j + 18) != '#') continue;

				if (image.at(i - 1).at(j + 18) != '#') continue;

				if (image.at(i).at(j + 19) != '#') continue;

				numMonsters++;  // :)

				image.at(i).at(j) = 'O';
				image.at(i + 1).at(j + 1) = 'O';
				image.at(i + 1).at(j + 4) = 'O';
				image.at(i).at(j + 5) = 'O';
				image.at(i).at(j + 6) = 'O';
				image.at(i + 1).at(j + 7) = 'O';
				image.at(i + 1).at(j + 10) = 'O';
				image.at(i).at(j + 11) = 'O';
				image.at(i).at(j + 12) = 'O';
				image.at(i + 1).at(j + 13) = 'O';
				image.at(i + 1).at(j + 16) = 'O';
				image.at(i).at(j + 17) = 'O';
				image.at(i).at(j + 18) = 'O';
				image.at(i - 1).at(j + 18) = 'O';
				image.at(i).at(j + 19) = 'O';
			}
		}

		if (numMonsters > 0) break;

		rotate_right(&image);
	}


	if (numMonsters == 0)
	{
		flip_about_x(&image);

		for (int k = 0; k < 4; k++)
		{
			for (int i = 1; i < image.size() - 1; i++)
			{
				for (int j = 0; j < image.at(i).size() - 19; j++)
				{
					if (image.at(i).at(j) != '#') continue;

					if (image.at(i + 1).at(j + 1) != '#') continue;

					if (image.at(i + 1).at(j + 4) != '#') continue;

					if (image.at(i).at(j + 5) != '#') continue;

					if (image.at(i).at(j + 6) != '#') continue;

					if (image.at(i + 1).at(j + 7) != '#') continue;

					if (image.at(i + 1).at(j + 10) != '#') continue;

					if (image.at(i).at(j + 11) != '#') continue;

					if (image.at(i).at(j + 12) != '#') continue;

					if (image.at(i + 1).at(j + 13) != '#') continue;

					if (image.at(i + 1).at(j + 16) != '#') continue;

					if (image.at(i).at(j + 17) != '#') continue;

					if (image.at(i).at(j + 18) != '#') continue;

					if (image.at(i - 1).at(j + 18) != '#') continue;

					if (image.at(i).at(j + 19) != '#') continue;

					numMonsters++;  // :)

					image.at(i).at(j) = 'O';
					image.at(i + 1).at(j + 1) = 'O';
					image.at(i + 1).at(j + 4) = 'O';
					image.at(i).at(j + 5) = 'O';
					image.at(i).at(j + 6) = 'O';
					image.at(i + 1).at(j + 7) = 'O';
					image.at(i + 1).at(j + 10) = 'O';
					image.at(i).at(j + 11) = 'O';
					image.at(i).at(j + 12) = 'O';
					image.at(i + 1).at(j + 13) = 'O';
					image.at(i + 1).at(j + 16) = 'O';
					image.at(i).at(j + 17) = 'O';
					image.at(i).at(j + 18) = 'O';
					image.at(i - 1).at(j + 18) = 'O';
					image.at(i).at(j + 19) = 'O';
				}
			}

			if (numMonsters > 0) break;

			rotate_right(&image);
		}
	}

	cout << "part 2: the number of monsters was: " << numMonsters << endl;  // :)

	int numHash = 0;

	for (auto line : image)
	{
		for (auto c : line)
		{
			if (c == '#') numHash++;
		}
	}

	cout << "the number of hashes remaining is " << numHash;


	return 0;
}


void rotate_right(vector<string>* m)
{
	vector<string> temp(m->at(0).size(), "");

	for (int i = 0; i < m->at(0).size(); i++)
	{
		for (auto line : *m)
		{
			temp.at(i) += line.at(i);
		}
	}

	flip_about_y(&(temp));

	*m = temp;

	return;
}

void flip_about_x(vector<string>* m)
{
	string temp;
	for (int i = 0; i < (m->size()) / 2; i++)
	{
		temp = m->at(i);
		m->at(i) = m->at(m->size() - 1 - i);
		m->at(m->size() - 1 - i) = temp;
	}

	return;
}

void flip_about_y(vector<string>* m)
{
	vector<string> temp = *m;
	for (int i = 0; i < temp.size(); i++)
	{
		reverse(temp.at(i).begin(), temp.at(i).end());
	}

	*m = temp;

	return;
}

string get_left_side(vector<string>* m)
{
	string temp = "";

	for (auto line : *m)
	{
		temp += line.at(0);
	}

	return temp;
}

string get_right_side(vector<string>* m)
{
	string temp = "";
	for (auto line : *m)
	{
		temp += line.back();
	}

	return temp;
}