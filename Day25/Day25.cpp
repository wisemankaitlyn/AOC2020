// day 25!!!
// kaitlyn wiseman
// 12/25/2020

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main()
{
	long long subject_number = 7;
	long long value = 1;
	long long card_public_key = 19241437;
	long long door_public_key = 17346587;
	long long card_loop_size = 0;
	long long door_loop_size = 0;
	
	// determine card loop size 
	while (value != card_public_key)
	{
		value *= subject_number;
		value %= 20201227;
		card_loop_size++;
	}

	value = 1;

	// determine door loop size
	while (value != door_public_key)
	{
		value *= subject_number;
		value %= 20201227;
		door_loop_size++;
	}

	long long encryption_key = 1;

	for (long long i = 0; i < card_loop_size; i++)
	{
		encryption_key *= door_public_key;
		encryption_key %= 20201227;
	}

	cout << "part 1: the encryption key is " << encryption_key << endl;


	return 0;
}