#pragma once

//---------------------------------------
#include <iostream>
#include <sstream>
#include <vector>
//---------------------------------------



//---------------------------------------
using namespace std;
class turnInfo
{
public:
	//coords
	int row,col;

	//sign
	string sign;

	//setMove

	bool setCoords(string input);

private:
	void split(string s, char delim, vector<string> &elems);
};

class gameboard
{
public:
	//Grid array
	string gridArray[3][3];
};


class gameState
{
public:
	bool bExit = false;
	bool bPlayAgain = true;
	bool bFirstTurn = false;


};

