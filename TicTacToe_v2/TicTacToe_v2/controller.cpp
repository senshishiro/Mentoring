//----------------------------------------------
// controller.cpp
//----------------------------------------------

//---------------------------------------
#include "stdafx.h"
#include "controller.h"
#include "model.h"
//---------------------------------------

using namespace std;

//Converts input into a string
string getInput()
{
	string strInput;
	getline(cin, strInput);
	return strInput;
}




//Validates player's move and updates grid
bool updateGrid(string(*grid)[3][3], int x, int y, string playerSign)
{
	if ((*grid)[x][y].length() == 0)
	{
		(*grid)[x][y] = playerSign;
		return true;
	}
	else if ((*grid)[x][y].length() > 0)
	{
		cout << "spot is already filled\n";
		return false;
	}
	else
	{
		//cout << x << " " << y << endl;
		return false;
	}
}

//win logic