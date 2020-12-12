// day 12
// kaitlyn wiseman
// 12/12/2020

#define EAST 0
#define SOUTH 90
#define WEST 180
#define NORTH 270
#define X 0
#define Y 1

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;
string filename = "Day12.txt";

int main() {
	int pos[2] = { 0, 0 }; // currentPos[0] = x, currentPos[1] = y
	int deg = EAST;
	vector<string> inst;
	ifstream in;
	in.open(filename);

	while (!in.eof())
	{
		string temp;
		in >> temp;
		inst.push_back(temp);
	}
	
	for (auto i : inst)
	{
		int val = atoi((i.substr(1, i.size()-1)).c_str());

		switch (i[0])
		{
			case 'N':  // increase y by given val
				pos[1] += val;
				break;
			case 'S':  // decrease y by given val
				pos[1] -= val;
				break;
			case 'E':  // increase x by given val
				pos[0] += val;
				break;
			case 'W':  // decrease x by given val
				pos[0] -= val;
				break;
			case 'L':  // subtract val from deg (w/o going negative)
				deg += 360 - val;
				break;
			case 'R':  // add val to deg
				deg += val;
				break;
			case 'F':
				switch (deg % 360)
				{
					case EAST:  // increase x by given val
						pos[0] += val;
						break;
					case SOUTH:  // decrease y by given val
						pos[1] -= val;
						break;
					case WEST:  // decrease x by given val
						pos[0] -= val;
						break;
					case NORTH:  // increase y by given val
						pos[1] += val;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
	

	cout << "part 1: manhattan distance is: " << abs(pos[0]) + abs(pos[1]) << endl;


	// part 2
	pos[0] = 10;
	pos[1] = 1;

	int diffPos[] = { 0, 0 };

	for (auto i : inst)
	{
		int val = atoi((i.substr(1, i.size() - 1)).c_str());
		int newPos[] = { pos[X], pos[Y] };
		switch (i[0])
		{
		case 'N':  // increase y by given val
			pos[Y] += val;
			break;
		case 'S':  // decrease y by given val
			pos[Y] -= val;
			break;
		case 'E':  // increase x by given val
			pos[X] += val;
			break;
		case 'W':  // decrease x by given val
			pos[X] -= val;
			break;
		case 'L':  // move waypoint left
			while (val > 0)
			{
				newPos[X] = -pos[Y];
				newPos[Y] = pos[X];
				pos[X] = newPos[X];
				pos[Y] = newPos[Y];
				val -= 90;
			}
			break;
		case 'R':  
			while (val > 0)
			{
				newPos[X] = pos[Y];
				newPos[Y] = -pos[X];
				pos[X] = newPos[X];
				pos[Y] = newPos[Y];
				val -= 90;
			}
			break;
		case 'F':
			diffPos[X] += pos[X] * val;
			diffPos[Y] += pos[Y] * val;
			break;
		default:
			break;
		}
	}

	cout << "part 2: the manhattan distance is: " << abs(diffPos[X]) + abs(diffPos[Y]) << endl;

	return 0;
}