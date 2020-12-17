// day 16
// kaitlyn wiseman
// 12/16/2020

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;
string filename = "Day16.txt";
#define PART2 1

struct Field {
	string name;
	int LB1, UB1, LB2, UB2;
};

int main()
{
	ifstream in;
	in.open(filename);
	long long errRate = 0;
	string nxtName;
	string temp1;
	int temp2;
	vector<Field> fields;
	vector<int> yT;
	vector<vector<int>> nbT;
	int txSz = 20;
	
	getline(in, nxtName, ':');
	while (nxtName != "\nyour ticket")
	{		
		Field nxtField;
		nxtField.name = nxtName;
		in >> nxtField.LB1;  // first number
		getline(in, temp1, '-');  // clear '-'
		in >> nxtField.UB1;  // second number
		in >> temp1;  // clear 'or'
		in >> nxtField.LB2;  // third number
		getline(in, temp1, '-');  // clear '-'
		in >> nxtField.UB2;

		fields.push_back(nxtField);

		getline(in, nxtName, '\n');
		getline(in, nxtName, ':');
	}

	in >> temp2;  // get first number
	yT.push_back(temp2);

	while (yT.size() < txSz)
	{
		getline(in, temp1, ',');  // get ','
		in >> temp2;  // get first number
		yT.push_back(temp2);
	}

	getline(in, temp1, ':');  // clear 'nearby tickets:'

	while (!in.eof())
	{
		vector<int> curTx;
		in >> temp2;
		curTx.push_back(temp2);

		while (curTx.size() < txSz)
		{
			getline(in, temp1, ',');  // get ','
			in >> temp2;  // get first number
			curTx.push_back(temp2);
		}

		nbT.push_back(curTx);
	}

	vector<int> toErase;
	for (int i = 0; i < nbT.size(); i++)
	{
		for (auto val : nbT.at(i))
		{
			bool valid = false;

			for (auto fld : fields)
			{
				if ((val >= fld.LB1 && val <= fld.UB1)
					|| (val >= fld.LB2 && val <= fld.UB2))
				{
					valid = true;
				}
			}

			if (!valid)
			{
				errRate += val;
				if (find(toErase.begin(), toErase.end(), i) == toErase.end())
				{
					toErase.push_back(i);
				}
			}
		}
	}

	for (int i = toErase.size() - 1; i >= 0; i--)
	{
		nbT.erase(nbT.begin() + (toErase.at(i)));
	}

	cout << "part 1: error rate is " << errRate << endl;
	
	vector<int> fldToInd(fields.size(), -1);  // fldToInd.at(field number as in fields vector) = index at which to find field on ticket
	vector<vector<int>> colVldFlds(fields.size());
	for (int i = 0; i < txSz; i++)  // field no. in ticket
	{
		vector<vector<int>> valFlds(nbT.size());
		for (int j = 0; j < nbT.size(); j++)  // ticket no.
		{
			int numVld = 0;
			int indLstValFld;
			for (int k = 0; k < fields.size(); k++)  // field in field list
			{
				if ((nbT.at(j).at(i) >= fields.at(k).LB1 && nbT.at(j).at(i) <= fields.at(k).UB1) ||
					(nbT.at(j).at(i) >= fields.at(k).LB2 && nbT.at(j).at(i) <= fields.at(k).UB2))
				{
					numVld++;
					valFlds.at(j).push_back(k);
				}
			}
		}

		for (int x = 0; x < valFlds.at(0).size(); x++)
		{
			bool valid = true;
			for (auto tx : valFlds)
			{
				bool fnd = false;
				for (auto fld : tx)
				{
					if (fld == valFlds.at(0).at(x)) fnd = true;
				}
				if (!fnd)
				{
					valid = false;
					break;
				}
			}

			if (valid)
			{
				colVldFlds.at(i).push_back(valFlds.at(0).at(x));
			}
		}
	}

	bool done = false;
	while (!done)
	{
		int delFld = -1;
		for (int i = 0; i < colVldFlds.size(); i++)
		{
			if (colVldFlds.at(i).size() == 1)
			{
				fldToInd.at(colVldFlds.at(i).at(0)) = i;
				delFld = colVldFlds.at(i).at(0);
				break;
			}
		}

		for (int i = 0; i < colVldFlds.size(); i++)
		{
			auto iter = find(colVldFlds.at(i).begin(), colVldFlds.at(i).end(), delFld);
			if (iter != colVldFlds.at(i).end())
			{
				colVldFlds.at(i).erase(iter);
			}
		}

		done = true;
		for (auto val : fldToInd)
		{
			if (val == -1)
				done = false;
		}
	}

	long long val = 1;

	for (int i = 0; i < 6; i++)
	{
		val *= yT.at(fldToInd.at(i));
	}

	cout << "part 2: the value is " << val << endl;

	return 0;
}