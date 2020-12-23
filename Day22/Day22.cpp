// day 22
// kaitlyn wiseman
// 12/22/2020

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<queue>
#include<deque>

using namespace std;

bool recurse(deque<int> p1, deque<int> p2);  // returns true if p1 wins, false if p2 wins

int main()
{
	// get input
	queue<int> p1;
	queue<int> p2;
	queue<int> p12;
	queue<int> p22;
	string temp;
	ifstream in;
	in.open("Day22.txt");

	in >> temp;
	in >> temp;
	in >> temp; // get the first number
	
	while (find(temp.begin(), temp.end(), 'P') == temp.end())
	{
		p1.push(atoi(temp.c_str()));
		in >> temp;
	}

	in >> temp;
	in >> temp;

	while (!in.eof())
	{
		p2.push(atoi(temp.c_str()));
		in >> temp;
	}
	p2.push(atoi(temp.c_str()));

	// set aside for pt 2,,,
	p12 = p1;
	p22 = p2;

	// simulate game

	while (p1.size() > 0 && p2.size() > 0)
	{
		if (p1.front() > p2.front())
		{
			// p1 wins the round
			p1.push(p1.front());
			p1.push(p2.front());
			p1.pop();
			p2.pop();
		}
		else
		{
			// p2 wins the round
			p2.push(p2.front());
			p2.push(p1.front());
			p2.pop();
			p1.pop();
		}
	}

	int score = 0;
	queue<int> winner;
	if (p1.size() > 0)
	{
		winner = p1;
	}
	else
	{
		winner = p2;
	}

	int multiplier = winner.size();
	while (winner.size() > 0)
	{
		score += winner.front() * multiplier;
		winner.pop();
		multiplier--;
	}

	cout << "part 1: the winner's score is: " << score << endl;

	// PART 2

	// construct the deques
	deque<int> player1, player2;
	vector<vector<deque<int>>> prev;

	while (p12.size() > 0)
	{
		player1.push_back(p12.front());
		p12.pop();
	}
	while (p22.size() > 0)
	{
		player2.push_back(p22.front());
		p22.pop();
	}

	// we have to play the top-level game up here to keep score
	while (player1.size() > 0 && player2.size() > 0)
	{
		vector<deque<int>> thisround;
		thisround.push_back(player1);
		thisround.push_back(player2);

		if (find(prev.begin(), prev.end(), thisround) != prev.end())
		{
			// game ends, player 1 wins
			while (player2.size() > 0)
			{
				player2.pop_back();
			}

			break;
		}
		else
		{
			prev.push_back(thisround);
		}

		if (player1.front() > player1.size() - 1 || player2.front() > player2.size() - 1)
		{
			// p1 wins the round
			if (player1.front() > player2.front())
			{
				player1.push_back(player1.front());
				player1.push_back(player2.front());
				player1.pop_front();
				player2.pop_front();
				continue;
			}
			else  // p2 wins the round
			{
				player2.push_back(player2.front());
				player2.push_back(player1.front());
				player2.pop_front();
				player1.pop_front();
				continue;
			}
		}

		int p1front = player1.front();
		int p2front = player2.front();
		player1.pop_front();
		player2.pop_front();

		// construct new deques
		deque<int> nextp1 = player1;
		while (nextp1.size() > p1front)
		{
			nextp1.pop_back();
		}
		deque<int> nextp2 = player2;
		while (nextp2.size() > p2front)
		{
			nextp2.pop_back();
		}

		if (recurse(nextp1, nextp2))
		{
			// p1 won
			player1.push_back(p1front);
			player1.push_back(p2front);
			continue;
		}
		else
		{
			// p2 won
			player2.push_back(p2front);
			player2.push_back(p1front);
			continue;
		}
	}

	deque<int> win;
	if (player1.size() > 0)
	{
		win = player1;
	}
	else
	{
		win = player2;
	}
	score = 0;
	multiplier = win.size();
	while (win.size() > 0)
	{
		score += win.front() * multiplier;
		win.pop_front();
		multiplier--;
	}

	cout << "part 2: the winner's score is: " << score << endl;


	return 0;
}


bool recurse(deque<int> p1, deque<int> p2)
{
	vector<vector<deque<int>>> prev;

	while (p1.size() > 0 && p2.size() > 0)
	{
		vector<deque<int>> thisround;
		thisround.push_back(p1);
		thisround.push_back(p2);
		if (prev.size() > 5000) return true;

		if (find(prev.begin(), prev.end(), thisround) != prev.end())
		{
			// game ends, p1 wins
			return true;
		}
		else {
			prev.push_back(thisround);
		}

		if (p1.front() > p1.size() - 1 || p2.front() > p2.size() - 1)
		{
			// p1 wins the round
			if (p1.front() > p2.front())
			{
				p1.push_back(p1.front());
				p1.push_back(p2.front());
				p1.pop_front();
				p2.pop_front();
				continue;
			}
			else  // p2 wins the round
			{
				p2.push_back(p2.front());
				p2.push_back(p1.front());
				p2.pop_front();
				p1.pop_front();
				continue;
			}
		}

		int p1front = p1.front();
		int p2front = p2.front();
		p1.pop_front();
		p2.pop_front();

		// construct new deques
		deque<int> nextp1 = p1;
		while (nextp1.size() > p1front)
		{
			nextp1.pop_back();
		}
		deque<int> nextp2 = p2;
		while (nextp2.size() > p2front)
		{
			nextp2.pop_back();
		}

		if (recurse(nextp1, nextp2))
		{
			// p1 won
			p1.push_back(p1front);
			p1.push_back(p2front);
			continue;
		}
		else
		{
			// p2 won
			p2.push_back(p2front);
			p2.push_back(p1front);
			continue;
		}
	}

	if (p1.size() > 0) return true;
	else return false;

}