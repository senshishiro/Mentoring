//----------------------------------------------
// model.cpp
//----------------------------------------------

//----------------------------------------------
#include "stdafx.h"
#include "model.h"
#include "controller.h"

using namespace std;


//=========================================================================================
//Turn Model Functions
//=========================================================================================

//Set and get rows
void TurnModel::setRow(int x)
{
	row = x;
}

int TurnModel::getRow()
{
	return row;
}
//Set and get cols
void TurnModel::setCol(int y)
{
	col = y;
}

int TurnModel::getCol()
{
	return col;
}

//Set and get sign
void TurnModel::setSign(string s)
{
	sign = s;
}

string TurnModel::getSign()
{
	return sign;
}

//Set and get win message
void TurnModel::setWinMessage(string s)
{
	winMessage = s;
}

string TurnModel::getWinMessage()
{
	return winMessage;
}


//=========================================================================================
//Player Model Functions
//=========================================================================================

//Comp Constructor. Set up win Message.
PlayerModel::PlayerModel()
{
	winMessage = "Congratulations! You Won!.\n";
}

//Check if previous turn exists
bool PlayerModel::prevTurnExists()
{
	if (prevTurn.size() > 0)
		return true;
	else
		return false;
}

//=========================================================================================
//Comp Model Functions
//=========================================================================================

//Comp Constructor. Set up win Message.
CompModel::CompModel()
{
	winMessage = "You have been Defeated.Computer won!\n";
}

//Sets Best Move
void CompModel::SetBestMove(vector<int> temp)
{
	bestMove = temp;
}

//Update ROw and Col with the best move
void CompModel::OverrideMove()
{
	setRow(bestMove[0]);
	setCol(bestMove[1]);
}

//=========================================================================================
//Grid Model Functions
//=========================================================================================

//Constuctor. Set up defaults for diagonals. 
GridModel::GridModel()
{
	right_Diagonals = { { 0, 0 },{ 1, 1 },{ 2, 2 } };
	left_Diagonals = { { 2, 0 },{ 1, 1 },{ 0, 2 } };
}

//Return state of the grid
bool GridModel::isFull()
{
	return bFull;
}

// Searches grid for a string
matrix GridModel::searchGrid(GridModel grid, string str)
{
	matrix moves;

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			if (grid.gridArray[i][k] == str)
			{
				moves.push_back({ i,k });
			}
		}
	}
	return moves;
}

//Check if there are empty spaces in the grid
void GridModel::isGridFull(GridModel grid)
{
	string str = "";
	if (searchGrid(grid, str).size() > 0)
	{
		bFull = false;
	}
	else
	{
		bFull = true;
	}
}


//Check for win conditions and draw
bool GridModel::checkWins(GridModel &gridInfo, TurnModel playerInfo)
{
	bool bWin = false;
	bool bEmpty = true;
	
	string playerSign = playerInfo.getSign();
	int x = playerInfo.getRow();
	int y = playerInfo.getCol();


	// Checks Row for a win
	if ((gridInfo.gridArray[x][0] == playerSign) && (gridInfo.gridArray[x][1] == playerSign) && (gridInfo.gridArray[x][2] == playerSign))
	{
		bWin = true;
	}
	// Checks Col for a win
	else if ((gridInfo.gridArray[0][y] == playerSign) && (gridInfo.gridArray[1][y] == playerSign) && (gridInfo.gridArray[2][y] == playerSign))
	{
		bWin = true;
	}
	// Checks left Diag for a win
	else if ((gridInfo.gridArray[0][0] == playerSign) && (gridInfo.gridArray[1][1] == playerSign) && (gridInfo.gridArray[2][2] == playerSign))
	{
		bWin = true;
	}
	// Checks right Diag for a win
	else if ((gridInfo.gridArray[0][2] == playerSign) && (gridInfo.gridArray[1][1] == playerSign) && (gridInfo.gridArray[2][0] == playerSign))
	{
		bWin = true;
	}

	//Searches through the grid for empty spaces
	isGridFull(gridInfo);

	//Win
	if (bWin)
	{
		return true;
	}
	//Draw
	else if (!bWin && gridInfo.isFull())
	{
		return false;
	}
	else
	{
		return false;
	}
}


//Scans the row for two of the same mark and empty space
bool GridModel::rowCheck(GridModel grid, string compMark, int row, vector<int> &Move)
{
	int count = 0;

	vector<int> temp;

	// scan rows for player mark and empty spaces
	for (int i = 0; i < 3; i++)
	{
		if (grid.gridArray[row][i] == compMark)
		{
			count++;
		}
		else if (grid.gridArray[row][i] == "")
		{
			temp = { row, i };
		}
	}

	// return the empty spot if there are two matches
	if (count == 2 && !temp.empty())
	{
		Move = temp;
		temp.clear();
		count = 0;
		return true;
	}
	else
	{
		return false;
	}
}

//Scans the column of a grid 
bool GridModel::colCheck(GridModel grid, string compMark, int col, vector<int> &Move)
{
	int count = 0;
	vector<int> temp;

	for (int i = 0; i < 3; i++)
	{
		if (grid.gridArray[i][col] == compMark)
		{
			count++;
		}
		else if (grid.gridArray[i][col] == "")
		{
			temp = { i, col };
		}
	}

	// return the empty spot if there are two matches
	if (count == 2 && !temp.empty())
	{
		Move = temp;
		temp.clear();
		count = 0;
		return true;
	}
	else
	{
		return false;
	}
}

// Scans the diagonals of the grid looking for two marks and an empty space
bool GridModel::checkDiags(GridModel grid, matrix diags, string compMark, vector<int> &Move)
{
	int count = 0;
	vector<int> temp;

	for (int i = 0; i < 3; i++)
	{
		int x = diags[i][0];
		int y = diags[i][1];

		if (grid.gridArray[x][y] == compMark)
		{
			count++;
		}
		else if (grid.gridArray[x][y] == "")
		{
			temp = { x, y };
		}
	}

	if (count == 2 && !temp.empty())
	{
		Move = temp;
		temp.clear();
		count = 0;
		return true;
	}
	else
	{
		return false;
	}
}

// Searches grid for a string
void GridModel::gridReset()
{

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			gridArray[i][k] = "";

		}
	}
}

//=========================================================================================
//Game Model Functions
//=========================================================================================

//Constructor with default values
GameModel::GameModel()
{
	bWin = false;
	bQuit = false;
	bPlayerTurn = true;
	bPlayAgain = false;
}


void GameModel::resetModel()
{
	//Calling constructor to reset the defaults. Is this valid?
	GameModel();
	/*
	bWin = false;
	bQuit = false;
	bPlayerTurn = true;
	bPlayAgain = false;
	*/
}