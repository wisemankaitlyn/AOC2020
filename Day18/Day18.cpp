// day 18
// kaitlyn wiseman
// 12/18/2020

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<list>

#define DIGIT 1
#define OPER  2
#define PAREN 3
#define OPAREN 4

using namespace std;

int main()
{
	vector<long long> vals;
	vector<long> currRow;
	vector<string> lines;
	vector<list<char>> formOP;
	long long sum = 0;
	ifstream in;
	in.open("Day18.txt");
	string line;

	getline(in, line);
	while (!in.eof())
	{
		lines.push_back(line);
		getline(in, line);
	}
	lines.push_back(line);

	list<char> operator_stack;
	list<char> output_queue;

	for (auto line : lines)
	{
		for (char c : line)
		{
			if (isdigit(c))
			{
				output_queue.push_back(c);
			}
			else if (c == '+' || c == '*')
			{
				while (operator_stack.size() > 0
					&& (operator_stack.back() == '*' || operator_stack.back() == '+')
					&& (operator_stack.back() != '('))
				{
					output_queue.push_back(operator_stack.back());
					operator_stack.pop_back();
				}
				operator_stack.push_back(c);
			}
			else if (c == '(')
			{
				operator_stack.push_back(c);
			}
			else if (c == ')')
			{
				while (operator_stack.back() != '(')
				{
					output_queue.push_back(operator_stack.back());
					operator_stack.pop_back();
				}
				// pop the left parentheses
				operator_stack.pop_back();
			}
		}

		while (operator_stack.size() > 0)
		{
			output_queue.push_back(operator_stack.back());
			operator_stack.pop_back();
		}
		formOP.push_back(output_queue);
		output_queue.clear();
	}

	for (auto line : formOP)
	{
		long long result = 0;
		vector<long long> lineAst;
		while (line.size() > 0)
		{
			lineAst.push_back(line.front());
			line.pop_front();
		}
		int i = 0;
		while (lineAst.size() > 1)
		{
			if (lineAst.at(i) == '*')
			{
				if (lineAst.at(i - 1) != '+' && lineAst.at(i - 1) != '*'
					&& lineAst.at(i - 2) != '+' && lineAst.at(i - 2) != '*')
				{
					result = (lineAst.at(i - 1) - '0') * (lineAst.at(i - 2) - '0');
					lineAst.at(i - 2) = result + '0';
					lineAst.erase(lineAst.begin() + (i - 1));
					lineAst.erase(lineAst.begin() + (i - 1));
					i = 0;
				}
				else i++;
			}
			else if (lineAst.at(i) == '+')
			{
				if (lineAst.at(i - 1) != '+' && lineAst.at(i - 1) != '*'
					&& lineAst.at(i - 2) != '+' && lineAst.at(i - 2) != '*')
				{
					result = (lineAst.at(i - 1) - '0') + (lineAst.at(i - 2) - '0');
					lineAst.at(i - 2) = result + '0';
					lineAst.erase(lineAst.begin() + (i - 1));
					lineAst.erase(lineAst.begin() + (i - 1));
					i = 0;
				}
				else i++;
			}
			else
			{
				i++;
				continue;
			}
		}

		vals.push_back(lineAst.at(0) - '0');
	}

	for (auto val : vals)
	{
		sum += val;
	}

	cout << "part 1: the sum is: " << sum << endl;


	// part 2
	vals.clear();
	currRow.clear();
	lines.clear();
	in.close();
	in.open("Day18.txt");
	lines.clear();
	getline(in, line);
	while (!in.eof())
	{
		lines.push_back(line);
		getline(in, line);
	}
	lines.push_back(line);

	operator_stack.clear();
	output_queue.clear();
	vals.clear();
	formOP.clear();

	for (auto line : lines)
	{
		for (char c : line)
		{
			if (isdigit(c))
			{
				output_queue.push_back(c);
			}
			else if (c == '*')
			{
				while (operator_stack.size() > 0
					&& (operator_stack.back() == '+')
					&& (operator_stack.back() != '('))
				{
					output_queue.push_back(operator_stack.back());
					operator_stack.pop_back();
				}
				operator_stack.push_back(c);
			}
			else if (c == '+')
			{
				while (operator_stack.size() > 0
					&& (operator_stack.back() != '*')
					&& (operator_stack.back() != '('))
				{
					output_queue.push_back(operator_stack.back());
					operator_stack.pop_back();
				}
				operator_stack.push_back(c);
			}
			else if (c == '(')
			{
				operator_stack.push_back(c);
			}
			else if (c == ')')
			{
				while (operator_stack.back() != '(')
				{
					output_queue.push_back(operator_stack.back());
					operator_stack.pop_back();
				}
				// pop the left parentheses
				operator_stack.pop_back();
			}
		}

		while (operator_stack.size() > 0)
		{
			output_queue.push_back(operator_stack.back());
			operator_stack.pop_back();
		}
		formOP.push_back(output_queue);
		output_queue.clear();
	}

	for (auto line : formOP)
	{
		long long result = 0;
		vector<long long> lineAst;
		while (line.size() > 0)
		{
			lineAst.push_back(line.front());
			line.pop_front();
		}
		int i = 0;
		while (lineAst.size() > 1)
		{
			if (lineAst.at(i) == '*')
			{
				if (lineAst.at(i - 1) != '+' && lineAst.at(i - 1) != '*'
					&& lineAst.at(i - 2) != '+' && lineAst.at(i - 2) != '*')
				{
					result = (lineAst.at(i - 1) - '0') * (lineAst.at(i - 2) - '0');
					lineAst.at(i - 2) = result + '0';
					lineAst.erase(lineAst.begin() + (i - 1));
					lineAst.erase(lineAst.begin() + (i - 1));
					i = 0;
				}
				else i++;
			}
			else if (lineAst.at(i) == '+')
			{
				if (lineAst.at(i - 1) != '+' && lineAst.at(i - 1) != '*'
					&& lineAst.at(i - 2) != '+' && lineAst.at(i - 2) != '*')
				{
					result = (lineAst.at(i - 1) - '0') + (lineAst.at(i - 2) - '0');
					lineAst.at(i - 2) = result + '0';
					lineAst.erase(lineAst.begin() + (i - 1));
					lineAst.erase(lineAst.begin() + (i - 1));
					i = 0;
				}
				else i++;
			}
			else
			{
				i++;
				continue;
			}
		}

		vals.push_back(lineAst.at(0) - '0');
	}

	sum = 0;

	for (auto val : vals)
	{
		sum += val;
	}

	cout << "part 2: the new sum is: " << sum;

	return 0;
}