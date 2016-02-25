#pragma once


//---------------------------------------
#include <iostream>
#include <sstream>
#include <vector>
#include "view.h"
#include "model.h"
#include "time.h"
//---------------------------------------
/*
class Controller
{
public:



};
*/

class GridController
{

public:
	gridModel gridInfo;
	gridView gridV;

	void drawGrid()
	{
		gridV.drawGrid(gridInfo);
	}
	/*
	string (&grid())
	{
		return gridInfo.getGrid();
	}
	*/
	//bool slotOccupied(gridModel gridC, PlayerController player);

	bool updateGrid(gridModel &gridInfo, turnModel playerTurn);

	bool checkWins(gridModel &gridInfo, turnModel playerTurn)
	{
		return gridInfo.checkWins(gridInfo, playerTurn);
	}

	bool isFull()
	{
		return gridInfo.isFull();
	}
};

class compController 
{
public:
	compModel compInfo;
	
	void compTurn(turnModel &activePlayer, GridController &gControl, playerModel playerInfo, bool &bQuit);
	void compRandomTurn(GridController &GridC);
	bool compPotentialWins(GridController GridC);
	bool compBlockWins(GridController GridC, turnModel playerInfo);

};

class PlayerController
{
public:
	playerModel playerInfo;
	drawUI ui;
	string strUserInput;
	errorStrings errors;

	bool playerSetup(compController &comp)
	{
		bool firstMove;
		// Ask if player want to go first
		firstMove = turnOrder();

		//Ask if player wants to be X or O
		setXO(comp);

		return firstMove;
	}

	void playerTurn(turnModel &activePlayer, GridController &gControl, bool &bQuit);
	bool getMove(GridController GridControl, bool &bQuit);
	
	bool turnOrder();
	void setXO(compController &comp);
	bool playAgain();



	//Converts input into a string
	string getInput()
	{
		string strInput;
		getline(cin, strInput);
		return strInput;
	}


private:
	void split(string s, char delim, vector<string> &elems);
	bool setCoords(GridController GridControl, string input, string &err, bool &bQuit);

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