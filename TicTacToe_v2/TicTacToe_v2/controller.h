#pragma once


//---------------------------------------
#include <iostream>
#include <sstream>
#include <vector>
#include "view.h"
#include "model.h"
#include "time.h"
//---------------------------------------

class Controller
{
public:
	//Converts input into a string
	string getInput()
	{
		string strInput;
		getline(cin, strInput);
		return strInput;
	}

	//Function that converts strings to lowercase
	string toLowercase(string strText)
	{
		int k = strText.length();
		for (int i = 0; i < k; i++)
		{
			strText[i] = tolower(strText[i]);
		}

		return strText;
	}
};


class GridController
{

public:
	gridModel gridInfo;
	gridView test;

	void drawGrid()
	{
		test.drawGrid(gridInfo);
	}

	//bool slotOccupied(gridModel gridC, PlayerController player);

	bool updateGrid(gridModel &gridInfo, turnModel playerTurn);

	bool checkWins(gridModel &gridInfo, turnModel playerTurn)
	{
		return gridInfo.checkWins(gridInfo, playerTurn);
	}

};

class compController 
{
public:
	turnModel compInfo;
	vector<int> bestMove;

	void compRandomTurn(GridController &GridC, turnModel compInfo);
	bool compPotentialWins(GridController GridC, turnModel compInfo);
	bool compBlockWins(GridController GridC, turnModel playerInfo);

};

class PlayerController : public Controller
{
public:
	turnModel playerInfo;
	drawUI ui;
	string strUserInput;
	errorStrings errors;

	bool getMove(GridController GridControl, bool &bQuit);
	bool setCoords(GridController GridControl, string input, string &err, bool &bQuit);
	bool turnOrder();
	void setXO(compController &comp);
	bool playAgain();

private:
	void split(string s, char delim, vector<string> &elems);

};