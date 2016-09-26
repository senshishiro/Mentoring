#pragma once
#include <string>
#include <iostream>

using namespace std;

struct Qset
{
	string type;
	string data;
};

struct NewAnswer
{
	string obj;
	string question;
	bool leftRight;
};

class Inputs
{
public:
	static string toLowercase(string strText);
	static bool getInput();
	static string getData();
};