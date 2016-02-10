#pragma once

//---------------------------------------
#include <iostream>
#include <sstream>
#include <vector>
//---------------------------------------
class turnInfo
{
	public:
	//coords
	int x,y;

	//sign
	std::string sign;

	bool setRow(int row)
	{
		if (row > 1 && row < 3)
		{
			x = row;
			return true;
		}
		else
		{
			return false;
		}
	}



};

class board
{
	public:
	//Grid array
	std::string gridArray[3][3];
};