//-------------------------------------
// TicTacToe.cpp 
// by Chi Kong
// Date: 01/16/2016
//-------------------------------------


#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "time.h"

using namespace std;

typedef vector<int> coords;
typedef vector<coords> matrix;

//Draws a dotted line.
void drawLine()
{
	cout << "----------------------------------------\n";
}

//Draw intro
void drawIntro()
{
	drawLine();
	cout << "Tic Tac Toe\n";
	cout << "Create a row of three to win\n";
	cout << "Hit Q anytime when entering coordinates to quit.\n";
	drawLine();
}


//Function that converts strings to lowercase
string toLowercase(string strText)
{
	for (int i = 0; i < strText.length(); i++)
	{
		strText[i] = tolower(strText[i]);
	}

	return strText;
}


//Splits string by delimiter. returns values in a vector
void split(string s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	}
}


//Converts input into a string
string getInput()
{
	string strInput;
	getline(cin, strInput);
	return strInput;
}


//Asks player if they want to go first
bool turnOrder()
{
	string strInput;
	bool exit = false;

	do
	{
		cout << "Would you like to go first?[y/n]:";
		strInput = getInput();
		if (toLowercase(strInput) == "y")
		{
			exit = true;
			cout << "You are going first.\n";
			drawLine();
			return true;
		}	
		else if (toLowercase(strInput) == "n")
		{
			exit = true;
			cout << "Computer is going first.\n";
			drawLine();
			return false;
		}		
		else
		{
			cerr << "Please enter y/n.\n";
		}			
	} while (!exit);

	return true;
}


//Asks player if they want to be X or O
bool setXO()
{
	string strInput;
	bool exit = false;

	do
	{
		cout << "Would you to be X or O?:";
		strInput = getInput();
		if (toLowercase(strInput) == "x")
		{
			exit = true;
			cout << "You are X.\n";
			drawLine();
			return true;
		}
		else if (toLowercase(strInput) == "o")
		{
			exit = true;
			cout << "You are O.\n";
			drawLine();
			return false;
		}
		else
		{
			cerr << "Please enter X or O.\n";
		}
	} while (!exit);

	return true;
}

//Asks player if they want to exit
bool playAgain()
{
	string strInput = "";
	bool x = true;

	while (x)
	{
		drawLine();
		cout << "Would you like to play again(Y/N)? ";
		getline(cin, strInput);
		strInput = toLowercase(strInput);

		if (strInput == "n")
		{
			return true;
		}
		else if (strInput == "y")
		{
			drawLine();
			return false;
		}
		else
		{
			cout << "Please enter y/n.\n";
		}
	};

	return true;
}

//Validates player's move and updates grid
bool updateGrid(string(*grid)[3][3], int x, int y, string playerSign)
{		
	if ((*grid)[x][y].length() == 0)
	{
		(*grid)[x][y] = playerSign;
		return true;
	}
	else if ((*grid)[x][y].length() > 0)
	{
		cout << "spot is already filled\n";
		return false;
	}
	else
	{
		//cout << x << " " << y << endl;
		return false;
	}
}


//Get player's coordinates and validate
void getMove(string(*grid)[3][3], int &row, int &col, string PlayerSign, bool &exit)
{
	string strUserInput = "";
	int x, y;
	vector<string> input;
	bool bValidAnswer = false;

	do
	{
		cout << "Enter Coordinates: ";
		strUserInput = getInput();
		split(strUserInput, ' ', input);

		if (input.size() == 2 && (stringstream(input[0]) >> x) && (stringstream(input[1]) >> y))
		{
			x = x - 1;
			y = y - 1;

			if ((x >= 0 && x < 3) && (y >= 0 && y < 3))
			{
				bValidAnswer = updateGrid(grid, x, y, PlayerSign);
				row = x;
				col = y;
			}
			else
			{
				cerr << "Please enter a valid row and column.\n";
			}
		}
		else if (input.size() > 2)
		{
			cerr << "Please enter only two numbers spearated by a space.\n";
			bValidAnswer = false;
		}
		//Quit check
		else if (input.size() == 1 && toLowercase(input[0]) == "q")
		{
			exit = true;
			bValidAnswer = true;
		}
		else
		{
			cerr << "Please enter a valid row and column.\n";
			bValidAnswer = false;
		}

		input.clear();
	} while (!bValidAnswer);
}

//Searches grid for string
matrix searchGrid(string (*grid)[3][3], string str)
{
	matrix moves;

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			if ((*grid)[i][k] == str)
			{
				moves.push_back({i,k});
			}
		}
	}
	return moves;
}

//Check if there are empty spaces in the grid
bool isGridEmpty(string(*grid)[3][3], string str)
{

	if ((searchGrid(grid, str)).size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Scans the row of a grid 
bool rowCheck(string(*grid)[3][3], string compMark, int row, vector<int> &Move)
{
	int count = 0;
	vector<int> temp;

	for (int i = 0; i < 3; i++)
	{
		if ((*grid)[row][i] == compMark) 
		{
			count++;
		}
		else if ((*grid)[row][i] == "")
		{
			temp = { row, i };
		}
	}

	if (count == 2 && !temp.empty())
	{
		//cout << "X win " << temp[0] << " " << temp[1] << endl;
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
bool colCheck(string(*grid)[3][3], string compMark, int col, vector<int> &Move)
{
	int count = 0;
	vector<int> temp;

	for (int i = 0; i < 3; i++)
	{
		if ((*grid)[i][col] == compMark)
		{
			count++;
		}
		else if ((*grid)[i][col] == "")
		{
			temp = { i, col };
		}
	}

	if (count == 2 && !temp.empty())
	{
		//cout << "Y win " << temp[0] << " " << temp[1] << endl;
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

// Scans the diagonals of the grid
bool checkDiags(string(*grid)[3][3], matrix set,string compMark, vector<int> &Move)
{
	int count = 0;
	vector<int> temp;

	for (int i = 0; i < 3; i++)
	{
		int x = set[i][0];
		int y = set[i][1];

		if ((*grid)[x][y] == compMark)
		{
			count++;
		}
		else if ((*grid)[x][y] == "")
		{
			temp = { x, y };
		}
	}

	if (count == 2 && !temp.empty())
	{
		//cout << "diag win " << temp[0] << " " << temp[1] << endl;
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

//Scans the grids for potential computer wins
bool compPotentialWins(string(*grid)[3][3], string compMark, vector <int> &bestMove)
{
	vector<int> temp;
	matrix right_Diagonal = { { 0, 0 }, { 1, 1 }, { 2, 2 } };
	matrix left_Diagonal = { { 2, 0 }, { 1, 1 }, { 0, 2 } };

	for (int i = 0; i < 3; i++)
	{	
		if (rowCheck(grid, compMark, i,temp))
		{
			bestMove = temp;
			return true;
		}
		else if (colCheck(grid, compMark, i, temp))
		{
			bestMove = temp;
			return true;
		}
		else if (checkDiags(grid, right_Diagonal, compMark, temp))
		{
			bestMove = temp;
			return true;
		}
		else if (checkDiags(grid, left_Diagonal, compMark, temp))
		{
			bestMove = temp;
			return true;
		}
	}
	return false;
}

// Searches the grid for two in a row to block player wins
bool compBlockWins(string(*grid)[3][3], vector <int> prevTurn, string playerMark, vector <int> &bestMove)
{
	//player's previous turn
	int x = prevTurn[0];
	int y = prevTurn[1];

	//temp vectors
	vector<int> temp;
	
	//A vector for holding moves
	matrix potentialMoves;

	//Diagonal values
	matrix right_diagonal = { { 0, 0 }, { 1, 1 }, { 2, 2 } };
	matrix left_diagonal = { { 2, 0 }, { 1, 1 }, { 0, 2 } };
	
	//Loop for scanning col, row, diagonals based on player's last coords
	for (int i = 0; i < 3; i++)
	{
		// Scan rows for potential player wins
		if (rowCheck(grid, playerMark, i, temp))
		{
			potentialMoves.push_back(temp);
			temp.clear();
		}
		// Scan columns for potential player wins
		if (colCheck(grid, playerMark, i, temp))
		{
			potentialMoves.push_back(temp);
			temp.clear();
		}
		// Scan right diagonal for potential player wins
		if (checkDiags(grid, right_diagonal ,playerMark, temp))
		{
			potentialMoves.push_back(temp);
			temp.clear();
		}
		// Scan left diagonal for potential player wins
		if (checkDiags(grid, left_diagonal, playerMark, temp))
		{
			potentialMoves.push_back(temp);
			temp.clear();
		}
	}

	//Randomly select a move from list of potential moves
	if (potentialMoves.size() > 0)
	{
		int id;
		srand(time(NULL));
		id = (rand() % potentialMoves.size());
		bestMove = { potentialMoves[id][0], potentialMoves[id][1] };

		return true;
	}
	else
	{
		cout << "no good moves\n";
		return false;
	}
}


//Check for win conditions and draw
bool checkWins(string (*grid)[3][3], int x, int y, string playerSign, bool &isEmpty)
{
	bool bWin = false;
	bool bEmpty = true;

	if (((*grid)[x][0] == playerSign) && ((*grid)[x][1] == playerSign) && ((*grid)[x][2] == playerSign))
	{
		bWin = true;
	}
	else if (((*grid)[0][y] == playerSign) && ((*grid)[1][y] == playerSign) && ((*grid)[2][y] == playerSign))
	{
		bWin = true;
	}
	else if (((*grid)[0][0] == playerSign) && ((*grid)[1][1] == playerSign) && ((*grid)[2][2] == playerSign))
	{
		bWin = true;
	}
	else if (((*grid)[0][2] == playerSign) && ((*grid)[1][1] == playerSign) && ((*grid)[2][0] == playerSign))
	{
		bWin = true;
	}

	//Searches through the grid for empty spaces
	bEmpty = isGridEmpty(grid, "");

	//Win
	if (bWin)
	{
		return true;
	}
	//Draw
	else if (!bWin && !bEmpty)
	{
		isEmpty = false;
		return false;
	}
	else
	{
		return false;
	}
}


//Draws the grid
void drawGrid(string (*grid)[3][3])
{
	cout << "   | 1 | 2 | 3\n";
	cout << "---+---+---+---\n";

	for (int i = 0; i < 3; i++)
	{
		//Draw column number
		cout << " " << i + 1 << " | ";

		for (int j = 0; j < 3; j++)
		{
			cout << (*grid)[i][j];

			//Draw empty space		
			if ((*grid)[i][j] == "")
			{
				cout << " ";
			}
			
			if (j < 2)
			{
				cout << " | ";
			}
			else if (j == 2)
			{
				cout << endl;
			}
		}
		
		//line between rows
		if (i < 2)
		{
			cout << "---+---+---+---\n";
		}
	}
}


//Finds random spaces and randomly select one of them
void compRandomTurn(string(*grid)[3][3], int &row, int &col, string PlayerSign)
{
	vector<int> vecRow;
	vector<int> vecCol;
	matrix emptyMoves;
	bool turn = false;
	unsigned int id;

	//Get empty spaces from grid	
	emptyMoves = searchGrid(grid, "");

	//Create random number between 0 and the size of the vector
	srand(time(NULL));
	id = (rand() % emptyMoves.size());
	row = emptyMoves[id][0];
	col = emptyMoves[id][1];

	updateGrid(grid, row, col, PlayerSign);
}


int tictactoe(bool &bEndGame)
{
	bool bExit = false;
	bool bPlayerTurn = true;
	bool bWin = false;
	bool isEmpty = true;
	string strUserInput = "";
	string strPlayerSign ="";
	string strCompSign = "";
	string sign = "";
	string winMessage = "";
	int iRow, iCol;

	//Grid array
	string grid[3][3];
	
	vector <int> prevPlayerturn;
	vector <int> compBestMove;
	//Set player turn
	bPlayerTurn = turnOrder();

	//Set player marker
	if (setXO())
	{
		strPlayerSign = "X";
		strCompSign = "O";
	}
	else
	{
		strPlayerSign = "O";
		strCompSign = "X";
	}
	
	//Draw grid if the player is going first
	if (bPlayerTurn)
	{
		drawGrid(&grid);
	}
	
	// main game loop
	do
	{
		if (bPlayerTurn)
		{
			cout << "Your Turn.\n";
			getMove(&grid, iRow, iCol, strPlayerSign, bExit);
			sign = strPlayerSign;
			winMessage = "Congradtulations! You Won!.\n";
			bPlayerTurn = false;
			prevPlayerturn = {iRow, iCol};
		}
		else
		{
			cout << "Computer's Turn...\n";
			//compTurn(&grid, iRow, iCol, strCompSign);
			//getMove(&grid, iRow, iCol, strCompSign, bExit);
			if (prevPlayerturn.size() > 0)
			{
				//logic for computer detecing wins first, then blocking player wins
				if (compPotentialWins(&grid, strCompSign, compBestMove))
				{
					iRow = compBestMove[0];
					iCol = compBestMove[1];
					//cout << "Win move: " << iRow << " " << iCol << endl;
					updateGrid(&grid, iRow, iCol, strCompSign);
					prevPlayerturn.clear();
					compBestMove.clear();
				}
				else if (compBlockWins(&grid, prevPlayerturn, strPlayerSign, compBestMove))
				{
					
					iRow = compBestMove[0];
					iCol = compBestMove[1];
					//cout << "best move: " << iRow << " " << iCol << endl;
					updateGrid(&grid, iRow, iCol, strCompSign);
					prevPlayerturn.clear();
					compBestMove.clear();
				}
				else
				{
					compRandomTurn(&grid, iRow, iCol, strCompSign);
					//cout << "Random: " << iRow << " " << iCol << endl;
				}
			}	
			else
			{
				compRandomTurn(&grid, iRow, iCol, strCompSign);
			}

			sign = strCompSign;
			winMessage = "You have been Defeated. Computer won!\n";
			bPlayerTurn = true;
			
		}

		//Do not run if the player wants to exit
		if (!bExit)
		{ 
			drawGrid(&grid);
			bWin = checkWins(&grid, iRow, iCol, sign, isEmpty);
			drawLine();

			if (bWin)
			{
				cout << winMessage;
				bEndGame = playAgain();
				bExit = true;
			}
			else if (!bWin && !isEmpty)
			{
				cout << "Draw! No moves left.\n";
				bEndGame = playAgain();
				bExit = true;
			}
		}
		else if (bExit)
		{
			bEndGame = true;
		}
	} while (!bExit);
	
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool bEndGame = false;
	drawIntro();

	do
	{
		tictactoe(bEndGame);

	} while (!bEndGame);
	
	drawLine();
	cout << "Thanks for Playing!\n";

	return 0;
}
