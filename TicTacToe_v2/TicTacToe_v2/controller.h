#pragma once


//---------------------------------------
#include <iostream>
#include <sstream>
#include <vector>
#include "view.h"
#include "model.h"
#include "time.h"
//---------------------------------------


class GridController
{

public:
	gridModel gridInfo;
	gridView gridV;

	void drawGrid()
	{
		gridV.drawGrid(gridInfo);
	}

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

//=========================================================================================
class compController 
{
public:
	compModel compInfo;
	
	void compTurn(turnModel &activePlayer, GridController &gControl, playerModel playerInfo, bool &bQuit);

private:
	void compRandomTurn(GridController &GridC);
	bool compPotentialWins(GridController GridC);
	bool compBlockWins(GridController GridC, turnModel playerInfo);
};

//=========================================================================================
class PlayerController
{
public:
	playerModel playerInfo;
	drawUI ui;
	string strUserInput;
	errorStrings errors;

	//Player Setup
	bool playerSetup(compController &comp);

	//PlayAgain
	bool playAgain();
	
	//player turn
	void playerTurn(turnModel &activePlayer, GridController &gControl, bool &bQuit);

private:
	//Player Setup Functions
	bool turnOrder();
	void setXO(compController &comp);
	
	//Player Turn Functions
	bool getMove(GridController GridControl, bool &bQuit);
	bool setCoords(GridController GridControl, string input, string &err, bool &bQuit);
	void split(string s, char delim, vector<string> &elems);
	
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

//=========================================================================================
class GameController
{

	//controllers
	GridController gControl;
	PlayerController player;
	compController comp;

	//Temp Player info
	turnModel activePlayer;

	//Game States
	gameModel gameInfo;

	//UI
	drawUI UI;

	// Get first turn and player mark info. Draw empty grid if player id going first.
	void gameSetup();

	// Ask player if they want to play again. Reset game settings if yes.
	void gamePlayAgainSetup();

public:

	void gameStart();
};