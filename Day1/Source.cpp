


#include<iostream>
#include<vector>
#include<fstream>

using namespace std;



int main()
{
	vector<int> expenses;
	
	// get list of expenses
	ifstream in;
	in.open("records.txt");

	int temp;
	while (!in.eof())
	{
		in >> temp;
		expenses.push_back(temp);
	}
	in.close();

	// PART 1: 
	/*/

	for (int i = 0; i < expenses.size(); i++)
	{
		for (int j = i + 1; j < expenses.size(); j++)
		{
			if (expenses.at(i) + expenses.at(j) == 2020)
			{
				cout << expenses.at(i) << " + " << expenses.at(j) << " = 2020" << endl
					 << expenses.at(i) << " * " << expenses.at(j) << " = "
					 << expenses.at(i) * expenses.at(j);
				return 0;
			}
		}
	} /**/

	// PART 2:
	/**/

	for (int i = 0; i < expenses.size(); i++)
	{
		for (int j = i + 1; j < expenses.size(); j++)
		{
			for (int k = j + 1; k < expenses.size(); k++)
			{
				if (expenses.at(i) + expenses.at(j) + expenses.at(k) == 2020)
				{
					cout << expenses.at(i) << " + " << expenses.at(j) << " + " << expenses.at(k)
						<< " = 2020" << endl
						<< expenses.at(i) << " * " << expenses.at(j) << " * " << expenses.at(k)
						<< " = " << (long long)expenses.at(i) * (long long)expenses.at(j) * (long long)expenses.at(k);
					return 0;
				}
			}
		}
	}/**/


}