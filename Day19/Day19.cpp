// day 19
// kaitlyn wiseman
// 12/19/2020

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct Rule {
	vector<int> r1, r2;
	bool hasTwo = false;
	char c = 0;
};

bool isMatch(string line, vector<Rule> rules, int match, int* index);


int main() {
	vector<Rule> rules(500);
	vector<string> lines;
	ifstream in;
	in.open("Day19.txt");
	string temp;
	int num;
	bool part2 = true;


	in >> temp;
	while (temp.find(':') != string::npos)
	{
		Rule r;
		int ruleNo = atoi(temp.c_str());
		in >> temp;
		if (isdigit(temp[0]))
		{
			r.r1.push_back(atoi(temp.c_str()));
			in >> temp;
		}
		else if (temp[0] == '"')
		{
			r.c = temp[1];
			rules.at(ruleNo) = r;
			in >> temp;
			continue;
		}
		while (temp.find(':') == string::npos)
		{
			if (temp.find('a') != string::npos || temp.find('b') != string::npos)
			{
				break;
			}
			if (isdigit(temp[0]))
			{
				if (r.hasTwo)
				{
					r.r2.push_back(atoi(temp.c_str()));
				}
				else
				{
					r.r1.push_back(atoi(temp.c_str()));
				}
			}
			else if (temp == "|")
			{
				r.hasTwo = true;
			}
			in >> temp;
		}
		rules.at(ruleNo) = r;
	}

	while (!in.eof())
	{
		lines.push_back(temp);
		in >> temp;
	}
	lines.push_back(temp);


	int numValid = 0;
	int index = 0;
	int i = 0;

	if (part2) goto PART2;

	for (auto line : lines)
	{
		if (isMatch(line, rules, 0, &index) && index == line.size()) numValid++;
		index = 0;
	}


	cout << "part 1: the number of valid lines is " << numValid << endl;

	PART2:

	cout << "now... for part 2!" << endl;

	Rule eight;
	eight.r1.push_back(42);
	eight.r2.push_back(42);
	eight.r2.push_back(8);
	eight.hasTwo = true;
	rules.at(8) = eight;
	Rule eleven;
	eleven.r1.push_back(42);
	eleven.r1.push_back(31);
	eleven.r2.push_back(42);
	eleven.r2.push_back(11);
	eleven.r2.push_back(31);
	eleven.hasTwo = true;
	rules.at(11) = eleven;

	numValid = 0;
	index = 0;
	i = 0;

	for (auto line : lines)
	{
		int num42 = 0;
		int num31 = 0;
		bool valid = true;
		while (isMatch(line, rules, 42, &index))
		{
			num42++;
		}
		while (isMatch(line, rules, 31, &index))
		{
			num31++;
		}
		if (index == line.size() && num42 > num31 && num31 > 0)
		{
			numValid++;
		}
		index = 0;
	}

	cout << "part 2: the new number of valid lines is " << numValid << endl;

	return 0;
}


bool isMatch(string line, vector<Rule> rules, int match, int *index)
{
	int lastIndex = *index;
	int newIndex;
	if (rules.at(match).hasTwo)
	{
		if (rules.at(match).r1.size() == 2 && rules.at(match).r2.size() == 3)
		{
			if (isMatch(line, rules, rules.at(match).r1.at(0), index) && isMatch(line, rules, rules.at(match).r1.at(1), index))
			{
				return true;
			}
			else
			{
				*index = lastIndex;
			}

			if (isMatch(line, rules, rules.at(match).r2.at(0), index) && isMatch(line, rules, rules.at(match).r2.at(1), index)
				&& isMatch(line, rules, rules.at(match).r2.at(2), index))
			{
				return true;
			}
			else {
				*index = lastIndex;
				return false;
			}
		}
		if (rules.at(match).r1.size() == 2 && rules.at(match).r2.size() == 2)
		{
			if (isMatch(line, rules, rules.at(match).r1.at(0), index) && isMatch(line, rules, rules.at(match).r1.at(1), index))
			{
				return true;
			}
			else
			{
				*index = lastIndex;
			}

			if (isMatch(line, rules, rules.at(match).r2.at(0), index) && isMatch(line, rules, rules.at(match).r2.at(1), index))
			{
				return true;
			}
			else {
				*index = lastIndex;
				return false;
			}
		}
		else if (rules.at(match).r1.size() == 1 && rules.at(match).r2.size() == 2)
		{
			if (isMatch(line, rules, rules.at(match).r1.at(0), index))
			{
				return true;
			}
			else
			{
				*index = lastIndex;
			}

			if (isMatch(line, rules, rules.at(match).r2.at(0), index) && isMatch(line, rules, rules.at(match).r2.at(1), index))
			{
				return true;
			}
			else {
				*index = lastIndex;
				return false;
			}
		}
		else if (rules.at(match).r1.size() == 2 && rules.at(match).r2.size() == 1)
		{
			if (isMatch(line, rules, rules.at(match).r1.at(0), index) && isMatch(line, rules, rules.at(match).r1.at(1), index))
			{
				return true;
			}
			else
			{
				*index = lastIndex;
			}

			if (isMatch(line, rules, rules.at(match).r2.at(0), index))
			{
				return true;
			}
			else {
				*index = lastIndex;
				return false;
			}
		}
		else if (rules.at(match).r1.size() == 1 && rules.at(match).r2.size() == 1)
		{
			if (isMatch(line, rules, rules.at(match).r1.at(0), index))
			{
				return true;
			}
			else
			{
				*index = lastIndex;
			}

			if (isMatch(line, rules, rules.at(match).r2.at(0), index))
			{
				return true;
			}
			else {
				*index = lastIndex;
				return false;
			}
		}
	}
	else if (!rules.at(match).r1.empty())
	{
		if (rules.at(match).r1.size() == 2)
		{
			if (isMatch(line, rules, rules.at(match).r1.at(0), index) && isMatch(line, rules, rules.at(match).r1.at(1), index))
			{
				return true;
			}
			else
			{
				*index = lastIndex;
				return false;
			}
		}
		else if (rules.at(match).r1.size() == 3)
		{
			if (isMatch(line, rules, rules.at(match).r1.at(0), index) && isMatch(line, rules, rules.at(match).r1.at(1), index)
				&& isMatch(line, rules, rules.at(match).r1.at(2), index))
			{
				return true;
			}
			else
			{
				*index = lastIndex;
				return false;
			}
		}
		else
		{
			if (isMatch(line, rules, rules.at(match).r1.at(0), index))
			{
				return true;
			}
			else
			{
				*index = lastIndex;
				return false;
			}
		}
	}
	else if (rules.at(match).c == 'a')
	{
		try {
			if (line.at(*index) == 'a')
			{
				(*index)++;
				return true;
			}
			else
			{
				return false;
			}
		}
		catch (std::out_of_range)
		{
			return false;
		}
		
	}
	else if (rules.at(match).c == 'b')
	{
		try
		{
			if (line.at(*index) == 'b')
			{
				(*index)++;
				return true;
			}
			else
			{
				return false;
			}
		}
		catch (out_of_range)
		{
			return false;
		}
	}
}