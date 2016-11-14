#pragma once
#include <vector>
#include <algorithm>
#include "dict.h"
#include "inputs.h"

class Controller
{
	Dict dictionary;
	Inputs input;

	void drawLine();
	vector<string> findSuggestions(string word);
	void printList(vector<string> list);
	void checkDictionary(string temp, vector<string> &list);
	bool printVariantMsg(string word, string root);
	bool checkRootWord(string word);

public:
	void spellCheck();
};
