//----------------------------------------------
// controller.cpp
//----------------------------------------------

//---------------------------------------
#include "stdafx.h"
#include "controller.h"
//---------------------------------------

using namespace std;

//Find all open spots and randomly chooses one
void compController::compRandomTurn(GridController &GridC)
{
	vector<int> vecRow;
	vector<int> vecCol;
	matrix emptyMoves;
	bool turn = false;
	unsigned int id;

	//Get empty spaces from grid	
	emptyMoves = GridC.gridInfo.searchGrid(GridC.gridInfo, "");

	//Create random number between 0 and the size of the vector
	srand(time(NULL));
	id = (rand() % emptyMoves.size());
	compInfo.setRow(emptyMoves[id][0]);
	compInfo.setCol(emptyMoves[id][1]);

	//GridC.updateGrid(GridC.gridInfo, compInfo);
}

//Scan the whole grid for winning moves
bool compController::compPotentialWins(GridController GridC)
{
	vector<int> temp;
	matrix right_Diagonal = GridC.gridInfo.right_Diagonals;
	matrix left_Diagonal = GridC.gridInfo.left_Diagonals;
	string compMark = compInfo.getSign();
	gridModel gridM = GridC.gridInfo;

	//scans all rows and columns
	for (int i = 0; i < 3; i++)
	{
		if (gridM.rowCheck(gridM, compMark,i, temp))
		{
			compInfo.SetBestMove(temp);
			return true;
		}
		else if (gridM.colCheck(gridM, compMark, i, temp))
		{
			compInfo.SetBestMove(temp);
			return true;
		}
	}

	//Scans diagonals
	if (gridM.checkDiags(gridM, right_Diagonal, compMark, temp))
	{
		compInfo.SetBestMove(temp);
		return true;
	}
	if (gridM.checkDiags(gridM, left_Diagonal, compMark, temp))
	{
		compInfo.SetBestMove(temp);
		return true;
	}

	return false;
}


// Searches the grid for two in a row to block player wins
bool compController::compBlockWins(GridController GridC, turnModel playerInfo)
{
	//player's previous turn
	int x = playerInfo.getRow();
	int y = playerInfo.getCol();
	string playerMark = playerInfo.getSign();
	matrix right_Diagonal = GridC.gridInfo.right_Diagonals;
	matrix left_Diagonal = GridC.gridInfo.left_Diagonals;
	gridModel gridM = GridC.gridInfo;

	//temp vectors
	vector<int> temp;

	//A vector for holding moves
	matrix potentialMoves;

	//Loop for scanning col, row, diagonals based on player's last coords
	for (int i = 0; i < 3; i++)
	{
		// Scan rows for potential player wins
		if (gridM.rowCheck(gridM, playerMark, i, temp))
		{
			potentialMoves.push_back(temp);
			temp.clear();
		}
		// Scan columns for potential player wins
		if (gridM.colCheck(gridM, playerMark, i, temp))
		{
			potentialMoves.push_back(temp);
			temp.clear();
		}
	}


	// Scan right diagonal for potential player wins
	if (gridM.checkDiags(gridM, right_Diagonal, playerMark, temp))
	{
		potentialMoves.push_back(temp);
		temp.clear();
	}
	// Scan left diagonal for potential player wins
	if (gridM.checkDiags(gridM, left_Diagonal, playerMark, temp))
	{
		potentialMoves.push_back(temp);
		temp.clear();
	}


	//Randomly select a move from list of potential moves
	if (potentialMoves.size() > 0)
	{
		vector<int>  randomMove;
		int id;
		srand(time(NULL));
		id = (rand() % potentialMoves.size());
		randomMove = { potentialMoves[id][0], potentialMoves[id][1] };
		compInfo.SetBestMove(randomMove);

		return true;
	}
	else
	{
		return false;
	}
}


//Splits string by delimiter. returns values in a vector
void PlayerController::split(string s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	}
}

//Get moves from the player. Loops when player enters invalid coordinates
bool PlayerController::getMove(GridController GridControl, bool &bQuit)
{
	string err = "";
	bool bValidAnswer = false;
	do
	{
		ui.draw(ui.game_enterCoords);
		strUserInput = getInput();

		if (setCoords(GridControl, strUserInput, err, bQuit))
		{
			bValidAnswer = true;
			return true;
		}
		else
		{
			ui.errorOutput(err);
		}
	} while (!bValidAnswer);

	//cout << playerInfo.row << " " << playerInfo.col << endl;
}

// Coordinate validation and Sets the error message when invalid
bool PlayerController::setCoords(GridController gridC, string userCoords, string &err, bool &bQuit )
{
	int x, y;
	errorStrings errors;
	vector<string> input;
	gridModel grid = gridC.gridInfo;
	
	split(userCoords, ' ', input);

	if (input.size() == 2 && (stringstream(input[0]) >> x) && (stringstream(input[1]) >> y))
	{
		x = x - 1;
		y = y - 1;

		if ((x >= 0 && x < 3) && (y >= 0 && y < 3) && grid.gridArray[x][y].length() == 0)
		{
			playerInfo.setRow(x);
			playerInfo.setCol(y);

			cout << playerInfo.getRow() << " " << playerInfo.getCol() << endl;
			return true;
		}
		else if ((x >= 0 && x < 3) && (y >= 0 && y < 3) && grid.gridArray[x][y].length() > 0)
		{
			err = errors.invalid_occupiedSpace;
			return false;
		}
		else
		{
			err = errors.invalid_coords;
			return false;
		}
	}
	//Quit check
	else if (input.size() == 1 && toLowercase(input[0]) == "q")
	{
		bQuit = true;
		return true;
	}
	else
	{
		err = errors.invalid_entryFormat;
		return false;
	}
}



//Asks player if they want to go first
bool PlayerController::turnOrder()
{
	string strInput;
	bool exit = false;

	do
	{
		ui.draw(ui.game_goFirst);
		strInput = getInput();
		if (toLowercase(strInput) == "y")
		{
			exit = true;
			ui.draw(ui.game_First);
			ui.drawLine();
			return true;
		}
		else if (toLowercase(strInput) == "n")
		{
			exit = true;
			ui.draw(ui.game_Second);
			ui.drawLine();
			return false;
		}
		else
		{
			ui.errorOutput(errors.invalid_yesno);
		}
	} while (!exit);

	return true;
}

//Asks player if they want to be X or O
void PlayerController::setXO(compController &comp)
{
	string strInput;
	bool exit = false;

	do
	{
		ui.draw(ui.game_XO);
		strInput = getInput();

		if (toLowercase(strInput) == "x")
		{
			exit = true;
			playerInfo.setSign("X");
			comp.compInfo.setSign("O");
			ui.draw(ui.game_X);
			ui.drawLine();
			//return true;
		}
		else if (toLowercase(strInput) == "o")
		{
			exit = true;
			playerInfo.setSign("O");
			comp.compInfo.setSign("X");
			ui.draw(ui.game_O);
			ui.drawLine();
			//return false;
		}
		else
		{
			ui.errorOutput(errors.invalid_xo);
		}
	} while (!exit);

	//return true;
}



//Asks player if they want to exit
bool PlayerController::playAgain()
{
	string strInput = "";
	bool x = true;

	while (x)
	{
		ui.drawLine();
		ui.draw(ui.game_playAgain);
		getline(cin, strInput);
		strInput = toLowercase(strInput);

		if (strInput == "n")
		{
			return true;
		}
		else if (strInput == "y")
		{
			ui.drawLine();
			return false;
		}
		else
		{
			ui.errorOutput(errors.invalid_yesno);
		}
	};

	return true;
}

//Validates player's move and updates grid
bool GridController::updateGrid(gridModel &grid, turnModel playerTurn)
{
	int x = playerTurn.getRow();
	int y = playerTurn.getCol();
	string sign = playerTurn.getSign();
	
	if (grid.gridArray[x][y].length() == 0)
	{
		grid.gridArray[x][y] = sign;
		return true;
	}
	else
	{
		//cout << x << " " << y << endl;
		return false;
	}
}

