// day 23
// kaitlyn wiseman
// 12/23/2020

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>

using namespace std;

string input = "792845136";
int numMoves = 10000000;

int main()
{
	list<int> circle;
	list<int> removed;
	vector<int> map(1000001, -1);

	map.at(7) = 9;
	map.at(9) = 2;
	map.at(2) = 8;
	map.at(8) = 4;
	map.at(4) = 5;
	map.at(5) = 1;
	map.at(1) = 3;
	map.at(3) = 6;
	map.at(6) = 10;
	int l = 10;
	while (l < 1000000)
	{
		map.at(l) = l + 1;
		l++;
	}
	map.at(999998) = 999999;
	map.at(999999) = 1000000;
	map.at(1000000) = 7;


	int currentCup = 7;
	for (int i = 0; i < numMoves; i++)
	{
		// take out three cups following the current cup
		for (int j = 0; j < 3; j++)
		{
			removed.push_back(map.at(currentCup));
			map.at(currentCup) = map.at(map.at(currentCup));
			map.at(removed.back()) = -1;
		}

		int next = -1;
		if (currentCup - 1 > 0 && map.at(currentCup - 1) != -1)
		{
			next = currentCup - 1;
		}
		else if (currentCup - 2 > 0 && map.at(currentCup - 2) != -1)
		{
			next = currentCup - 2;
		}
		else if (currentCup - 3 > 0 && map.at(currentCup - 3) != -1)
		{
			next = currentCup - 3;
		}
		else if (currentCup - 4 > 0 && map.at(currentCup - 4) != -1)
		{
			next = currentCup - 4;
		}
		else if (map.at(1000000) != -1)
		{
			next = 1000000;
		}
		else if (map.at(999999) != -1)
		{
			next = 999999;
		}
		else if (map.at(999998) != -1)
		{
			next = 999998;
		}
		else if (map.at(999997) != -1)
		{
			next = 999997;
		}

		int temp = map.at(next);
		map.at(next) = removed.front();
		map.at(removed.front()) = temp;
		removed.pop_front();

		next = map.at(next);
		
		temp = map.at(next);
		map.at(next) = removed.front();
		map.at(removed.front()) = temp;
		removed.pop_front();

		next = map.at(next);

		temp = map.at(next);
		map.at(next) = removed.front();
		map.at(removed.front()) = temp;
		removed.pop_front();
		
		currentCup = map.at(currentCup);
	}

	cout << (long long)(map.at(1)) * (long long)(map.at(map.at(1)));

	return 0;
}