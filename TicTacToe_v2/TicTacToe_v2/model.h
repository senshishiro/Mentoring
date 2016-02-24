#pragma once

//---------------------------------------
#include <iostream>
#include <sstream>
#include <vector>
//---------------------------------------



//---------------------------------------
using namespace std;

typedef vector<int> coords;
typedef vector<coords> matrix;

// error strings
class errorStrings
{
public:
	const string invalid_coords = "Please enter a valid row and column.\n";
	const string invalid_entryFormat = "Please enter only two numbers spearated by a space.\n";
	const string invalid_occupiedSpace = "spot is already filled\n";
	const string invalid_yesno = "Please enter y / n.\n";
	const string invalid_xo = "Please enter X or O.\n";
};


class turnModel
{
private:
	int row, col;
	string sign;
	string winMessage;

	
protected:

	vector<int> prevTurn = { row, col };


public:
	
	//Set and get rows
	void setRow(int x)
	{
		row = x;
	}

	int getRow()
	{
		return row;
	}
	//Set and get cols
	void setCol(int y)
	{
		col = y;
	}

	int getCol()
	{
		return col;
	}

	//Set and get sign
	void setSign(string s)
	{
		sign = s;
	}
	
	string getSign()
	{
		return sign;
	}

	//Set and get win message
	void SetWinMessage(string s)
	{
		winMessage = s;
	}

	string getWinMessage()
	{
		return winMessage;
	}

};

class playerModel: public turnModel
{
public:

	string winMessage = "Congratulations! You Won!.\n";

	bool prevTurnExists()
	{
		if (prevTurn.size() > 0)
			return true;
		else
			return false;
	}
};

class compModel : public turnModel
{
	vector<int> bestMove;
	
public:
	string winMessage = "You have been Defeated.Computer won!\n";


	void SetBestMove(vector<int> temp)
	{
		bestMove = temp;
	}

	void OverrideMove()
	{
		setRow(bestMove[0]);
		setCol(bestMove[1]);
	}
};

class gridModel
{
private:
	//Grid is full
	bool bFull = false;

public:
	//Diagonals
	const matrix right_Diagonals = { { 0, 0 },{ 1, 1 },{ 2, 2 } };
	const matrix left_Diagonals = { { 2, 0 },{ 1, 1 },{ 0, 2 } };

	//Grid Array
	string gridArray[3][3];

	/*
	string (&getGrid())[3][3]
	{
		return gridArray[3][3];
	}*/

	bool isFull()
	{
		return bFull;
	}

	matrix searchGrid(gridModel grid, string str);
	void isGridFull(gridModel grid);
	bool checkWins(gridModel &gridInfo, turnModel playerInfo);

	bool rowCheck(gridModel grid, string compMark, int row, vector<int> &Move);
	bool colCheck(gridModel grid, string compMark, int col, vector<int> &Move);
	bool checkDiags(gridModel grid, matrix diags, string compMark, vector<int> &Move);

};

/*
class gameState
{
public:
	bool bExit = false;
	bool bPlayAgain = true;
	bool bFirstTurn = false;
};*/



