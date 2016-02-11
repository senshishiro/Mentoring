//----------------------------------------------
// model.cpp
//----------------------------------------------

//----------------------------------------------
#include "stdafx.h"
#include "model.h"


using namespace std;


bool turnInfo::setCoords(string userCoords)
{
	int x, y;
	vector<string> input;
	split(userCoords, ' ', input);

	if (input.size() == 2 && (stringstream(input[0]) >> x) && (stringstream(input[1]) >> y))
	{
		x = x - 1;
		y = y - 1;

		if ((x >= 0 && x < 3) && (y >= 0 && y < 3))
		{
			row = x;
			col = y;
		}
		else
		{
			cerr << "Please enter a valid row and column.\n";
		}
	}
}


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
void turnInfo::split(string s, char delim, vector<string> &elems)
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