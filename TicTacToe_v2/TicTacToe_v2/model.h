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
public:

	int row,col;
	vector<int> prevTurn = { row, col };
	string sign;
	string winMessage = "Congratulations! You Won!.\n";

	bool prevTurnExists()
	{
		if (prevTurn.size() > 0)
			return true;
		else
			return false;
	}
};

class gridModel
{
public:
	//Diagonals
	const matrix right_Diagonals = { { 0, 0 },{ 1, 1 },{ 2, 2 } };
	const matrix left_Diagonals = { { 2, 0 },{ 1, 1 },{ 0, 2 } };

	//Grid Array
	string gridArray[3][3];

	//Grid is full
	bool isFull = false;

	matrix searchGrid(gridModel grid, string str);
	bool isGridFull(gridModel grid, string str);
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



