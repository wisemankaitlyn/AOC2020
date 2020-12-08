// day 7
// kaitlyn wiseman
// 12/07/2020

// style and sense both died while i was writing this code :)

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include "Bag.h"

using namespace std;

int main() {
	string filename = "Day7.txt";
	int part;
	cout << "part 1 or 2: ";
	cin >> part;
	
	if (part == 1) 
	{
		ifstream in;
		in.open(filename);

		vector<vector<string>> bags;
		vector<string> emptyBags;

		while (!in.eof())
		{
			string line;
			string temp1;
			string temp2;
			in >> temp1 >> temp2;
			string primary = temp1 + " " + temp2;
			getline(in, line);

			bool hasDigit = false;
			for (char c : line)
				if (isdigit(c)) hasDigit = true;
			if (!hasDigit)
			{
				emptyBags.push_back(primary);
				continue;
			}

			vector<string> temp;
			temp.push_back(primary);
			while (line != "")
			{
				char digit = '1';
				for (char c : line)
					if (isdigit(c)) {
						digit = c;
						break;
					}
				line.erase(0, line.find(digit) + 2);
				temp1 = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);
				temp2 = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);
				temp.push_back(temp1 + " " + temp2);
				if (line.find(",") == string::npos)
				{
					line = "";
				}
			}
			bags.push_back(temp);
		}

		vector<string> canHold;

		for (auto color : bags)
		{
			// is shiny gold?
			if (color.at(0) == "shiny gold")
			{
				continue;
			}
			bool done = false;
			for (int i = 1; i < color.size(); i++)
			{
				// can hold directly?
				if (color.at(i) == "shiny gold")
				{
					canHold.push_back(color.at(0));
					done = true;
					break;
				}
			}
			if (done) continue;

			vector<string> toCheck;
			for (int i = 1; i < color.size(); i++)
			{
				toCheck.push_back(color.at(i));
			}
			while (!toCheck.empty())
			{
				bool deadEnd = false;
				for (auto bag : emptyBags)
				{
					if (bag == toCheck.back())
					{
						deadEnd = true;
						toCheck.pop_back();
						break;
					}
				}
				if (deadEnd) continue;
				for (auto bag : bags)
				{
					if (bag.at(0) == toCheck.back())
					{
						toCheck.pop_back();
						for (int i = 1; i < bag.size(); i++)
						{
							if (bag.at(i) == "shiny gold")
							{
								done = true;
								break;
							}
							else
							{
								toCheck.push_back(bag.at(i));
							}
						}
						break;
					}
				}
				if (done) break;
			}
			if (done) {
				canHold.push_back(color.at(0));
				cout << " found one! " << endl;
			}
		}

		cout << "part 1: the number of bags is " << canHold.size() << endl;
	}
	else if (part == 2)
	{
		// i hate c++ save me
		ifstream in;
		in.open(filename);
		int numBags = 0;

		vector<Bag> bags;

		while (!in.eof())
		{
			string temp1;
			string temp2;
			string line;
			Bag tempBag;
			in >> temp1 >> temp2;
			tempBag.color = temp1 + " " + temp2;

			getline(in, line);

			bool hasDigit = false;
			for (char c : line)
				if (isdigit(c)) hasDigit = true;
			if (!hasDigit)
			{
				bags.push_back(tempBag);
				continue;
			}

			while (line != "")
			{
				char digit = '1';
				int idigit = 1;
				for (char c : line)
					if (isdigit(c)) {
						digit = c;
						idigit = c - '0';
						break;
					}
				line.erase(0, line.find(digit) + 2);
				temp1 = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);
				temp2 = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);
				for (int i = 0; i < idigit; i++)
				{
					tempBag.inside.push_back(temp1 + " " + temp2);
				}
				if (line.find(",") == string::npos)
				{
					line = "";
				}
			}
			bags.push_back(tempBag);
		}

		vector<string> toCheck;
		for (auto bag : bags)
		{
			if (bag.color == "shiny gold")
			{
				for (string s : bag.inside)
				{
					toCheck.push_back(s);
				}
				break;
			}
		}
		while (!toCheck.empty())
		{
			for (auto bag : bags)
			{
				if (bag.color == toCheck.back())
				{
					numBags++;
					toCheck.pop_back();
					for (string s : bag.inside)
					{
						toCheck.push_back(s);
					}
					break;
				}
			}
		}
		
		cout << "part 2: the number of bags inside your shiny gold bag is " << numBags;
	}

	return 0;
	
}