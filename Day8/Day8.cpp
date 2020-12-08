// day 8
// kaitlyn wiseman
// 12/08/2020

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#define PART 2

using namespace std;

struct Instruct {
	string type;
	int value;
};

int execute(vector<Instruct> i);

string filename = "Day8.txt";
bool STOP_PART_1 = false;
vector<int> cI;
int index = 0;

int main() {
	vector<Instruct> i;
	ifstream in;
	in.open(filename);

	while (!in.eof())
	{
		Instruct temp;
		in >> temp.type >> temp.value;

		i.push_back(temp);
	}

	int runTimes = 0;
	int accumulator = 0;

	if (PART == 1)
		for (index = 0; index < i.size(); index++)
		{
			for (int done : cI)
			{
				if (index == done)
				{
					STOP_PART_1 = true;
					break;
				}
			}
			if (STOP_PART_1)
				break;
			accumulator += execute(i);
		}

	
	if (PART == 2)
		for (int instNo = 0; instNo < i.size(); instNo++)
		{
			cout << "instruction number " << instNo << endl;
			if (i.at(instNo).type == "jmp") i.at(instNo).type = "nop";
			else if (i.at(instNo).type == "nop") if (i.at(instNo).value != 0) i.at(instNo).type = "jmp";
			else continue;
			runTimes = 0;
			accumulator = 0;
			for (index = 0; index < i.size(); index++)
			{
				try {
					accumulator += execute(i);
				}
				catch (out_of_range)
				{
					break;
				}
				runTimes++;
				if (runTimes >= 1000)
					break;
			}

			if (i.at(instNo).type == "jmp") i.at(instNo).type = "nop";
			else if (i.at(instNo).type == "nop") i.at(instNo).type = "jmp";
		}

	if (PART == 1)
		cout << "part 1: the value in the accumulator before an instruction is repeated is " << accumulator;
	else if (PART == 2)
		cout << "part 2: the value of the accumulator after the program terminates is " << accumulator;

	return 0;
}


int execute(vector<Instruct> i)
{
	if (PART == 1) cI.push_back(index);
	if (i.at(index).type == "acc")
	{
		return i.at(index).value;
	}
	else if (i.at(index).type == "jmp")
	{
		index += i.at(index).value;
		if (PART == 1)
			for (int done : cI)
			{
				if (done == index)
				{
					STOP_PART_1 = true;
					return 0;
				}
			}
		return execute(i);
	}
	else if (i.at(index).type == "nop")
	{
		return 0;
	}
}