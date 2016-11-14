#pragma once
#include <string>
#include <iostream>

using namespace std;

class Inputs
{
public:
	static string toLowercase(string strText);
	static bool getInput();
	static string getWord();
};