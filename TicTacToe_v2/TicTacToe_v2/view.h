#pragma once
#include <iostream>
#include <sstream>
#include "model.h"

using namespace std;

class gridView 
{
public:
	void drawGrid(gridModel grid);
};


class drawUI
{

public:
	//strings for game
	const string game_draw = "Draw! No moves left.\n";
	const string game_playAgain = "Would you like to play again?";
	const string game_goFirst = "Would you like to go first?[y/n]:";
	const string game_First = "You are going first.\n";
	const string game_Second = "Computer is going first.\n";
	const string game_end = "Thanks for Playing!\n";
	const string game_playerTurn = "Your Turn.\n";
	const string game_compTurn = "Computer's Turn...\n";
	const string game_enterCoords = "Enter Coordinates: ";
	const string game_XO = "Would you to be X or O?:";
	const string game_X = "You are X.\n";
	const string game_O = "You are O.\n";


	void errorOutput(string errStr);
	void drawLine();
	void drawIntro();

	void draw(string s)
	{
		cout << s;
	}
};