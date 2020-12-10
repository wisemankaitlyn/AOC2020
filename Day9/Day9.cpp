// day 9
// kaitlyn wiseman
// 12/09/2020

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

string filename = "Day9.txt";

int main() {
	vector<long long> numbers;
	ifstream in;
	in.open(filename);

	while (!in.eof())
	{
		long long temp;
		in >> temp;
		numbers.push_back(temp);
	}

	bool done = false;
	long long invalidVal = -1;
	int preamble = 25;
	for (int i = preamble; i < numbers.size(); i++)
	{
		bool validNo = false;
		for (int j = 1; j <= preamble; j++)
		{
			for (int k = j + 1; k <= preamble; k++)
			{
				if (numbers.at(i) == numbers.at(i - j) + numbers.at(i - k))
				{
					validNo = true;
					break;
				}
			}
			if (validNo) break;
		}
		if (!validNo)
		{
			invalidVal = numbers.at(i);
			break;
		}
	}

	cout << "part 1: the first invalid value is " << invalidVal << endl;

	long long sumVal = -1;
	int index;
	for (int i = 0; i < numbers.size(); i++)
	{
		index = 1;
		long long sum = numbers.at(i);
		while (sum < invalidVal && i + index < numbers.size())
		{
			sum += numbers.at(i + index);
			index++;
		}
		if (sum == invalidVal && index > 1)
		{
			long long smallestVal = numbers.at(i);
			long long largestVal = numbers.at(i);
			for (int j = i; j <= i + index; j++)
			{
				if (numbers.at(j) < smallestVal) smallestVal = numbers.at(j);
				if (numbers.at(j) > largestVal) largestVal = numbers.at(j);
			}
			sumVal = smallestVal + largestVal;
			break;
		}
	}

	cout << "part 2: the sum of the smallest and largest number is " << sumVal;

	return 0;
}