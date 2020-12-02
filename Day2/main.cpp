// day 2
// author: kaitlyn wiseman
// 12/02/2020


#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main()
{
	string password;
	ifstream in;
	int minNum;
	int maxNum;
	char required;
	int numCorrect = 0;
	int numPasswords = 0;
	string temp;

	cout << "Part 1 or 2? ";
	cin >> temp;

	// PART 1
	if (temp == "1")
	{
		in.open("passwords.txt");
		while (!in.eof())
		{
			numPasswords++;

			getline(in, temp, '-');
			minNum = atoi(temp.c_str());

			getline(in, temp, ' ');
			maxNum = atoi(temp.c_str());

			getline(in, temp, ':');
			required = temp[0];

			getline(in, password, '\n');

			int num = 0;  
			// determine how many times the character shows up
			for (int i = 0; i < password.length(); i++)
			{
				if (password[i] == required)
				{
					num++;
				}
			}

			// determine whether the password meets the criteria
			if (num >= minNum && num <= maxNum)
			{
				numCorrect++;
			}
		}
	}
	// PART 2
	else if (temp == "2")
	{
		in.open("passwords.txt");
		while (!in.eof())
		{
			numPasswords++;

			getline(in, temp, '-');
			minNum = atoi(temp.c_str());

			getline(in, temp, ' ');
			maxNum = atoi(temp.c_str());

			getline(in, temp, ':');
			required = temp[0];

			getline(in, password, '\n'); // includes the leading space

			if ((password.at(minNum) == required) != (password.at(maxNum) == required))
			{
				numCorrect++;
			}
		}
		in.close();
	}

	cout << "The number of valid passwords out of " << numPasswords
		<< " is " << numCorrect << ".";

	return 0;
}