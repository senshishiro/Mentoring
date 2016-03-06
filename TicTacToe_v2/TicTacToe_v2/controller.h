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
	GridModel gridInfo;
	GridView gridV;

	void drawGrid();
	bool updateGrid(GridModel &gridInfo, TurnModel playerTurn);
	bool checkWins(GridModel &gridInfo, TurnModel playerTurn);
	bool isFull();
};

//=========================================================================================
class CompController 
{
public:
	CompModel compInfo;
	void compTurn(TurnModel &activePlayer, GridController &gControl, PlayerModel playerInfo, bool &bQuit);

private:
	void compRandomTurn(GridController &GridC);
	bool compPotentialWins(GridController GridC);
	bool compBlockWins(GridController GridC, TurnModel playerInfo);
};

//=========================================================================================
class PlayerController
{
public:
	PlayerModel playerInfo;
	DrawUI ui;
	string strUserInput;
	errorStrings errors;

	//Player Setup
	bool playerSetup(CompController &comp);

	//PlayAgain
	bool playAgain();
	
	//player turn
	void playerTurn(TurnModel &activePlayer, GridController &gControl, bool &bQuit);

private:
	//Player Setup Functions
	bool turnOrder();
	void setXO(CompController &comp);
	
	//Player Turn Functions
	bool getMove(GridController GridControl, bool &bQuit);
	bool setCoords(GridController GridControl, string input, string &err, bool &bQuit);
	void split(string s, char delim, vector<string> &elems);
	
	//Converts input into a string
	string getInput();

	//Function that converts strings to lowercase
	string toLowercase(string strText);
};

//=========================================================================================
class GameController
{
private:
	//controllers
	GridController gControl;
	PlayerController player;
	CompController comp;

	//Temp Player info
	TurnModel activePlayer;

	//Game States
	GameModel gameInfo;

	//UI
	DrawUI UI;

	// Get first turn and player mark info. Draw empty grid if player id going first.
	void gameSetup();

	// Ask player if they want to play again. Reset game settings if yes.
	void gamePlayAgainSetup();

public:

	void gameStart();
};