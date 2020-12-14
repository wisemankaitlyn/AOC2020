// kaitlyn wiseman
// day 13
// 12/13/2020

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;
string filename = "Day13.txt";

int main() {
	int myTime;
	vector<int> buses;
	ifstream in;
	in.open(filename);
	in >> myTime;
	
	string tempBus = "";
	char temp;
	in >> temp;
	while (!in.eof())
	{
		if (temp == 'x') {
			buses.push_back(-1);
		}
		else if (temp == ',' && tempBus != "")
		{
			buses.push_back(atoi(tempBus.c_str()));
			tempBus = "";
		}
		else if (temp == ',') {}
		else if (isdigit(temp))
		{
			tempBus += temp;
		}
		in >> temp;
	}
	if (tempBus != "") buses.push_back(atoi(tempBus.c_str()));

	int busID = buses.at(0);
	int waitTime = buses.at(0) - myTime % buses.at(0);
	
	for (auto bus : buses)
	{
		if (bus > 0
			&& bus - myTime % bus < waitTime)
		{
			waitTime = bus - myTime % bus;
			busID = bus;
		}
	}

	cout << "part 1: busID * waitTime = " << busID * waitTime << endl;

	// part 2
	unsigned long long maxVal = 1;
	for (auto bus : buses)
	{
		if (bus == -1) continue;
		maxVal *= bus;
	}

	unsigned long long timestamp = 0;
	unsigned long long iter = buses.at(0);
	for (int i = 1; i < buses.size(); i++)
	{
		cout << "i = " << i << endl;
		if (buses.at(i) == -1) continue;
		while (true)
		{
			timestamp += iter;
			cout << timestamp << endl;
			bool done = true;
			if ((i == 0 && timestamp % buses.at(i) != 0) ||
				(i != 0 && buses.at(i) - timestamp % buses.at(i) != i))
			{
				done = false;
			}
			if (done) break;
		}

		iter *= buses.at(i);

		if (timestamp > maxVal)
		{
			cout << "error: surpassed maxval";
		}
	}
	

	cout << "part 2: the earliest timestamp is " << timestamp;


	return 0;
}