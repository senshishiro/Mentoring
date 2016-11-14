#include "stdafx.h"
#include "dict.h"

// Load dictionary
// loads list into a map
void Dict::loadDict()
{
	string line;
	ifstream file (TEXTPATH);
	int count = 0;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			dict[line] = line;
			count++;
		}

		cout << count << " words loaded.\n";
	}
	else
	{
		cerr << "Unable to read file.\n";
	}
	file.close();
}

// wordExist
// checks if the word exists in the dictionary
bool Dict::wordExist(string word)
{
	if (dict.find(word) == dict.end())
	{
		// word does not exist in the list
		return false;
	}
	else
	{
		// word exists in the list
		return true;
	}
}

/*
void Dict::printDict()
{
	for (auto key = dict.cbegin(); key != dict.cend(); key ++)
	{
		cout << key->first << endl;
	}
}
*/