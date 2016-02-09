//----------------------------------------------
// model.cpp
//----------------------------------------------

//----------------------------------------------
#include "stdafx.h"
#include "model.h"


using namespace std;


//Function that converts strings to lowercase
string toLowercase(string strText)
{
	int k = strText.length();
	for (int i = 0 ; i < k ; i++)
	{
		strText[i] = tolower(strText[i]);
	}

	return strText;
}


//Splits string by delimiter. returns values in a vector
void split(string s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	}
}

//grid

//Turn