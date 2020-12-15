// day 14
// kaitlyn wiseman
// 12/14/2020

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<bitset>

using namespace std;
string filename = "Day14.txt";

struct Pair {
	long long mem;
	long long val;
};

vector<Pair> writemem(long long memind, long long memval, vector<Pair> memory);

int main() {
	ifstream in;
	in.open(filename);
	vector<Pair> memory;
	long long mask0 = 0;  // with accurate zeros; OR-ed with val
	long long mask1 = 0;  // with accurate ones; AND-ed with val
	string temp = "";

	for (int i = 0; i < 4; i++)
	{
		char c;
		in >> c;
		temp += c;
	}

	while (!in.eof())
	{
		if (temp == "mask")
		{
			// update mask
			in >> temp;  // clear the '='
			in >> temp;  // get mask

			mask0 = 0;
			mask1 = 0;

			for (int i = temp.length() - 1, j = 0; i >= 0 && j < temp.length(); i--, j++)
			{
				switch (temp.at(i))
				{
					case 'X':  // nothing gets changed
							   // put a 0 in this pos for mask0, put a 1 in this pos for mask 1
						// nothing changes for mask0
						mask1 += pow(2, j);
						break;
					case '0':  // a zero gets written here 
							   // put a 0 in this pos for mask0; put a 0 in this pos for mask 1
						// nothing changes for mask0
						// nothing changes for mask1
						break;
					case '1':  // a one gets written here
							   // put a 1 in this pos for mask0; put a 1 in this pos for mask 1
						mask0 += pow(2, j);
						mask1 += pow(2, j);
						break; 
					default:
						break;
				}
			}
		}
		else
		{
			// write masked val to place in memory
			int memkey;
			long long newval;
			in >> memkey;  // get memory val
			in >> temp; // clear ]
			in >> temp; // clear =
			in >> newval;

			newval |= mask0;
			newval &= mask1;

			bool written = false;
			for (int i = 0; i < memory.size(); i++)
			{
				if (memory.at(i).mem == memkey)
				{
					written = true;
					memory.at(i).val = newval;
				}
			}
			if (!written)
			{
				Pair t;
				t.mem = memkey;
				t.val = newval;
				memory.push_back(t);
			}
		}

		temp = "";
		for (int i = 0; i < 4; i++)
		{
			char c;
			in >> c;
			temp += c;
		}
	}

	long long total = 0;
	for (auto pair : memory)
	{
		total += pair.val;
	}

	cout << "part 1: the sum of vals in memory is: " << total << endl;

	in.close();

	// part 2
	
	memory.clear();
	in.open(filename);
	vector<int> floating;
	long long memmask0 = 0;
	long long memmask1 = 0;
	
	temp = "";
	for (int i = 0; i < 4; i++)
	{
		char c;
		in >> c;
		temp += c;
	}

	while (!in.eof())
	{
		if (temp == "mask")
		{
			// update mask
			in >> temp;  // clear the '='
			in >> temp;  // get mask

			memmask0 = 0;
			memmask1 = 0;
			floating.clear();

			for (int i = temp.length() - 1, j = 0; i >= 0 && j < temp.length(); i--, j++)
			{
				switch (temp.at(i))
				{
				case 'X':  // nothing gets changed
						   // put a 0 in this pos for mask0, put a 1 in this pos for mask 1
					// nothing changes for mask0
					floating.push_back(j);
					break;
				case '0':  // a zero gets written here 
						   // put a 0 in this pos for mask0; put a 0 in this pos for mask 1
					// nothing changes for mask0
					// nothing changes for mask1
					memmask1 += pow(2, j);
					break;
				case '1':  // a one gets written here
						   // put a 1 in this pos for mask0; put a 1 in this pos for mask 1
					memmask0 += pow(2, j);
					memmask1 += pow(2, j);
					break;
				default:
					break;
				}
			}
		}
		else
		{
			// write masked val to place in memory
			long long memkey;
			long long newval;
			in >> memkey;  // get memory val
			in >> temp; // clear ]
			in >> temp; // clear =
			in >> newval;


			if (floating.size() == 0)
			{
				memkey |= memmask0;
				memkey &= memmask1;

				memory = writemem(memkey, newval, memory);
			}
			else {
				unsigned long long arrVal = 0;
				while (arrVal < pow(2, floating.size()))
				{
					long long tmemmask0 = memmask0;
					long long tmemmask1 = memmask1;
					bitset<14> tb(arrVal);
					for (int i = 0; i < tb.size(); i++)
					{
						if (tb[i] == 1)
						{
							// if this bit is on, then the val at this index of floating() is supposed to be 1
							tmemmask0 += pow(2, floating.at(i));
							tmemmask1 += pow(2, floating.at(i));
						}
					}

					long long tempkey = memkey;
					tempkey |= tmemmask0;
					tempkey &= tmemmask1;
					memory = writemem(tempkey, newval, memory);

					arrVal++;
				}
			}
		}

		temp = "";
		for (int i = 0; i < 4; i++)
		{
			char c;
			in >> c;
			temp += c;
		}
		cout << "done!" << endl;
	}

	total = 0;
	for (auto pair : memory)
	{
		total += pair.val;
	}

	cout << "part 2: the total val in memory is: " << total;

	return 0;
}

vector<Pair> writemem(long long memind, long long memval, vector<Pair> memory)
{
	bool written = false;
	for (int i = 0; i < memory.size(); i++)
	{
		if (memory.at(i).mem == memind)
		{
			written = true;
			memory.at(i).val = memval;
		}
	}
	if (!written)
	{
		Pair t;
		t.mem = memind;
		t.val = memval;
		memory.push_back(t);
	}

	return memory;
}