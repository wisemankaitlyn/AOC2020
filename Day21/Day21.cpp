// day 21
// kaitlyn wiseman
// 12/21/2020

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct Food {
	vector<string> i;  // ingredients
	vector<string> a;  // listed allergens
};

struct Translation {
	string e;  // english
	vector<string> t;  // translated
};


int main() {
	vector<Food> f;
	ifstream in;
	in.open("Day21.txt");
	string temp;

	// get all lists of ingredients
	while (!in.eof())
	{
		Food list;
		in >> temp;
		while (find(temp.begin(), temp.end(), '(') == temp.end())
		{
			list.i.push_back(temp);
			in >> temp;
		}
		in >> temp;
		while (find(temp.begin(), temp.end(), ')') == temp.end())
		{
			temp.pop_back();
			list.a.push_back(temp);
			in >> temp;
		}
		temp.pop_back();
		list.a.push_back(temp);

		f.push_back(list);
	}


	// find which foreign words correspond to which allergen
	// - create vector of translations
	vector<Translation> tr;
	// - create vector of possible foreign words
	vector<string> possible;
	// - make the vector of possible foreign words to be the list of
	//   ingredients of the first list containing that allergen
	for (auto line : f)
	{
		for (auto allergen : line.a)
		{
			// check that we haven't already translated this allergen...
			bool done = false;
			for (auto trans : tr)
			{
				if (allergen == trans.e)
				{
					done = true;
					break;
				}
			}
			if (done) continue;

			possible = line.i;

			// - go through each other list containing that allergen, and 
			//   narrow down the list of possible foreign words

			for (auto oLine : f)
			{
				if (find(oLine.a.begin(), oLine.a.end(), allergen) == oLine.a.end()) continue;
				vector<string> toRemove;

				for (int i = 0; i < possible.size(); i++)
				{
					if (find(oLine.i.begin(), oLine.i.end(), possible.at(i)) == oLine.i.end())
					{
						toRemove.push_back(possible.at(i));
					}
				}
				for (auto s : toRemove)
				{
					possible.erase(find(possible.begin(), possible.end(), s));
				}
			}

			// - add the allergen and its translation to the vector of
			//   translations
			Translation thisT;
			thisT.e = allergen;
			thisT.t = possible;
			tr.push_back(thisT);
		}
	}


	// find the number of occurences of words which cannot be allergens
	// - loop through the words in each line, and + 1 for each word not
	//   contained in the vector of translations
	int numWords = 0;
	vector<string> possible_allergens;
	for (auto trans : tr)
	{
		for (auto i : trans.t)
		{
			possible_allergens.push_back(i);
		}
	}
	for (auto line : f)
	{
		for (auto i : line.i)
		{
			if (find(possible_allergens.begin(), possible_allergens.end(), i) == possible_allergens.end()) numWords++;
		}
	}

	cout << "part 1: the number of occurrences of words that couldn't possibly be allergens is " << numWords << endl;


	while (true)
	{
		bool d = true;
		for (auto t : tr)
		{
			if (t.t.size() != 1) d = false;
		}
		if (d) break;

		for (int i = 0; i < tr.size(); i++)
		{
			if (tr.at(i).t.size() == 1)
			{
				string rem = tr.at(i).t.at(0);

				for (int j = 0; j < tr.size(); j++)
				{
					if (i == j) continue;

					if (find(tr.at(j).t.begin(), tr.at(j).t.end(), rem) != tr.at(j).t.end())
					{
						tr.at(j).t.erase(find(tr.at(j).t.begin(), tr.at(j).t.end(), rem));
					}
				}
			}
		}
	}

	string output = "";

	for (int i = 'a'; i <= 'z'; i++)
	{
		for (int j = 'a'; j <= 'z'; j++)
		{
			for (auto trans : tr)
			{
				if (trans.e[0] == i && trans.e[1] == j)
				{
					output += trans.t.at(0) + ",";
				}
			}
		}
	}
	output.pop_back();

	cout << "part 2: the canonical dangerous ingredient list is: " << endl
		<< output << endl;

	return 0;
}

