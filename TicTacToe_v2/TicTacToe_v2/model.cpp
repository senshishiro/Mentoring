//----------------------------------------------
// model.cpp
//----------------------------------------------

//----------------------------------------------
#include "stdafx.h"
#include "model.h"
#include "controller.h"

using namespace std;

//=========================================================================================
//Grid Model Functions
//=========================================================================================

// Searches grid for a string
matrix gridModel::searchGrid(gridModel grid, string str)
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
void gridModel::isGridFull(gridModel grid)
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
bool gridModel::checkWins(gridModel &gridInfo, turnModel playerInfo)
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
bool gridModel::rowCheck(gridModel grid, string compMark, int row, vector<int> &Move)
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
bool gridModel::colCheck(gridModel grid, string compMark, int col, vector<int> &Move)
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
bool gridModel::checkDiags(gridModel grid, matrix diags, string compMark, vector<int> &Move)
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
void gridModel::gridReset()
{

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			gridArray[i][k] = "";

		}
	}
}