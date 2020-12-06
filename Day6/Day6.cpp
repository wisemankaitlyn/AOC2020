// day 6
// kaitlyn wiseman
// 12/06/2020

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

string filename = "Day6.txt";

int main() {
	ifstream in;
	in.open(filename);
	string person;
	vector<char> questions;
	int questionSum = 0;

	while (!in.eof())
	{
		getline(in, person, '\n');
		if (person == "")
		{
			questionSum += questions.size();
			questions.clear();
		}
		else
		{
			for (char q : person)
			{
				if (find(questions.begin(), questions.end(), q) == questions.end())
					questions.push_back(q);
			}
		}
	}

	cout << "Part 1: the sum is " << questionSum << endl;

	in.close();

	// part 2
	questionSum = 0;
	questions.clear();
	in.open(filename);
	int personNum = 0;
	while (!in.eof())
	{
		getline(in, person, '\n');
		if (person == "")
		{
			questionSum += questions.size();
			questions.clear();
			personNum = 0;
		}
		else
		{
			if (personNum == 0)
			{
				for (char q : person)
				{
					questions.push_back(q);
				}
			}
			else
			{
				vector<char> toRemove;
				for (char q : questions)
				{
					if (person.find(q) == string::npos)
					{
						toRemove.push_back(q);
					}
				}
				for (char q : toRemove)
				{
					questions.erase(find(questions.begin(), questions.end(), q));
				}
			}
			personNum++;
		}
	}

	cout << "Part 2: the sum is " << questionSum << endl;

	return 0;
}
