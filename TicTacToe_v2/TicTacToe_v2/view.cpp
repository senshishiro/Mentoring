//----------------------------------------------
// view.cpp
//----------------------------------------------

//---------------------------------------
#include "stdafx.h"
#include <iostream>
//---------------------------------------

using namespace std;

void drawLine()
{
	cout << "----------------------------------------\n";
}

//Draw intro
void drawIntro()
{
	drawLine();
	cout << "Tic Tac Toe\n";
	cout << "Create a row of three to win\n";
	cout << "Hit Q anytime when entering coordinates to quit.\n";
	drawLine();
}

//Asks player if they want to go first
bool turnOrder()
{
	string strInput;
	bool exit = false;

	do
	{
		cout << "Would you like to go first?[y/n]:";
		strInput = getInput();
		if (toLowercase(strInput) == "y")
		{
			exit = true;
			cout << "You are going first.\n";
			drawLine();
			return true;
		}
		else if (toLowercase(strInput) == "n")
		{
			exit = true;
			cout << "Computer is going first.\n";
			drawLine();
			return false;
		}
		else
		{
			cerr << "Please enter y/n.\n";
		}
	} while (!exit);

	return true;
}


//Asks player if they want to be X or O
bool setXO()
{
	string strInput;
	bool exit = false;

	do
	{
		cout << "Would you to be X or O?:";
		strInput = getInput();
		if (toLowercase(strInput) == "x")
		{
			exit = true;
			cout << "You are X.\n";
			drawLine();
			return true;
		}
		else if (toLowercase(strInput) == "o")
		{
			exit = true;
			cout << "You are O.\n";
			drawLine();
			return false;
		}
		else
		{
			cerr << "Please enter X or O.\n";
		}
	} while (!exit);

	return true;
}
