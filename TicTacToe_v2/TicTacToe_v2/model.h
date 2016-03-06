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

//=========================================================================================
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

//=========================================================================================
//turnModel - Contains turn coordinats and win message

class TurnModel
{
private:
	string sign;
		
protected:
	int row, col;
	string winMessage;
	vector<int> prevTurn = { row, col };

public:
	
	//Set and get rows
	void setRow(int x);
	int getRow();

	//Set and get cols
	void setCol(int y);
	int getCol();

	//Set and get sign
	void setSign(string s);
	string getSign();

	//Set and get win message
	void setWinMessage(string s);
	string getWinMessage();

};

//=========================================================================================

class PlayerModel: public TurnModel
{
public:
	//Constuctor
	PlayerModel();

	//Check if previous turn exists
	bool prevTurnExists();	
};

//=========================================================================================

class CompModel : public TurnModel
{
private:
	vector<int> bestMove;
	
public:
	//Constuctor
	CompModel();

	//Sets Best Move
	void SetBestMove(vector<int> temp);

	//Update ROw and Col with the best move
	void OverrideMove();
};

//=========================================================================================

class GridModel
{
private:
	//Grid is full
	bool bFull = false;

public:
	//Diagonals

	//Doesn't compile in vs2013
	//const matrix right_Diagonals = { { 0, 0 },{ 1, 1 },{ 2, 2 } };
	//const matrix left_Diagonals = { { 2, 0 },{ 1, 1 },{ 0, 2 } };

	matrix right_Diagonals; 
	matrix left_Diagonals;
	
	//Grid Array
	string gridArray[3][3];
	
	//Constructor
	GridModel();

	//Return state of the grid
	bool isFull();
	
	//Reset the grid
	void gridReset();
	
	//Scans grid for a string
	matrix searchGrid(GridModel grid, string str);
	
	//Scans grid for empty spaces. 
	void isGridFull(GridModel grid);
	
	//Check functions
	bool checkWins(GridModel &gridInfo, TurnModel playerInfo);
	
	//Check Functions for comp
	bool rowCheck(GridModel grid, string compMark, int row, vector<int> &Move);
	bool colCheck(GridModel grid, string compMark, int col, vector<int> &Move);
	bool checkDiags(GridModel grid, matrix diags, string compMark, vector<int> &Move);

};

//=========================================================================================
class GameModel
{
public:
	bool bWin = false;
	bool bQuit = false;
	bool bPlayerTurn = true;
	bool bPlayAgain = false;

	//constructor
	GameModel();

	void resetModel();
};



