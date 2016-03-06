//----------------------------------------------
// view.cpp
//----------------------------------------------

//---------------------------------------
#include "stdafx.h"
#include "view.h"

//---------------------------------------

using namespace std;


//Draws the Grid
void GridView::drawGrid(GridModel grid)
{
	cout << "   | 1 | 2 | 3\n";
	cout << "---+---+---+---\n";

	for (int i = 0; i < 3; i++)
	{
		//Draw column number
		cout << " " << i + 1 << " | ";

		for (int j = 0; j < 3; j++)
		{
			cout << grid.gridArray[i][j];

			//Draw empty space		
			if (grid.gridArray[i][j] == "")
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


//Draw text
void DrawUI::draw(string s)
{
	cout << s;
}

//Draws errors
void DrawUI::errorOutput(string errStr)
{
	cerr << errStr;
}

// Draws a line
void DrawUI::drawLine()
{
	cout << "----------------------------------------\n";
}

//Draw intro
void DrawUI::drawIntro()
{
	drawLine();
	cout << "Tic Tac Toe\n";
	cout << "Create a row of three to win\n";
	cout << "Hit Q anytime when entering coordinates to quit.\n";
	drawLine();
}

