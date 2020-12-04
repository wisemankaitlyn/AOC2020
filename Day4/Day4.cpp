// day 4
// kaitlyn wiseman
// 12/04/2020

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstring>

using namespace std;

int main() {
	ifstream in;
	string line = "";
	string temp2;
	vector<vector<string>> passports;
	vector<string> temp_pass;
	int numValid = 0;
	int part;

	cout << "part 1 or 2? ";
	cin >> part;

	in.open("Day4.txt");
	
	while (!in.eof())
	{
		getline(in, line, '\n');
		while (line != "")
		{
			string field = line.substr(0, line.find(':'));
			line.erase(0, line.find(':') + 1);

			if (part == 2) {

				if (field == "byr")
				{
					int year = atoi(line.substr(0, 4).c_str());
					line.erase(0, 4);
					if (year < 1920 || year > 2002) field = "invalid";
				}
				else if (field == "iyr")
				{
					int year = atoi(line.substr(0, 4).c_str());
					line.erase(0, 4);
					if (year < 2010 || year > 2020) field = "invalid";
				}
				else if (field == "eyr")
				{
					int year = atoi(line.substr(0, 4).c_str());
					line.erase(0, 4);
					if (year < 2020 || year > 2030) field = "invalid";
				}
				else if (field == "hgt")
				{
					string height = line.substr(0, 6);
					if (height.find("cm") != string::npos)
					{
						int measure = atoi(line.substr(0, line.find("cm")).c_str());
						if (measure < 150 || measure > 193) field = "invalid";
					}
					else if (height.find("in") != string::npos)
					{
						int measure = atoi(line.substr(0, line.find("in")).c_str());
						if (measure < 59 || measure > 76) field = "invalid";
					}
					else field = "invalid";
				}
				else if (field == "hcl")
				{
					string color = line.substr(0, 7);
					if (color.find('#') == string::npos) field = "invalid";
					for (char c : color)
					{
						switch (c) {
						case '#':
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
						case 'a':
						case 'b':
						case 'c':
						case 'd':
						case 'e':
						case 'f':
							continue;
							break;
						default:
							field = "invalid";
							break;
						}
					}
				}
				else if (field == "ecl")
				{
					string color = line.substr(0, 3);
					if (color != "amb" && color != "blu" && color != "brn" && color != "gry" &&
						color != "grn" && color != "hzl" && color != "oth")
						field = "invalid";
				}
				else if (field == "pid")
				{
					if ((line.find(" ") != string::npos && line.find(" ") == 9) || line.length() == 9)
					{
						string pid = line.substr(0, 9).c_str();
						for (char c : pid)
						{
							if (!isdigit(c)) field = "invalid";
						}
					}
					else field = "invalid";
				}
			}

			if (field != "invalid") temp_pass.push_back(field);

			if (line.find(" ") != string::npos)
			{
				line.erase(0, line.find(" ") + 1);
				continue;
			}
			else
			{
				getline(in, line, '\n');
				if (line == "") break;
				else continue;
			}
		}
		passports.push_back(temp_pass);
		temp_pass.clear();
	}
	int validFields = 0;
	for (auto p : passports)
	{
		for (auto s : p)
		{
			if (s == "byr") validFields++;
			else if (s == "iyr") validFields++;
			else if (s == "eyr") validFields++;
			else if (s == "hgt") validFields++;
			else if (s == "hcl") validFields++;
			else if (s == "ecl") validFields++;
			else if (s == "pid") validFields++;
		}

		if (validFields == 7) numValid++;
		validFields = 0;
	}

	cout << "the number of \"valid\" passports is: " << numValid;

	return 0;
}
