#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Dict
{
	const string TEXTPATH = "words.txt";
	

public:
	map<string, string> dict;
	void loadDict();
	void printDict();
	bool wordExist(string word);
};
