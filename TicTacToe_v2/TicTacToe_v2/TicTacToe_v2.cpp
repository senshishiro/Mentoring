// TicTacToe_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "model.h"
//#include "controller.h"
#include "view.h"
#include <iostream>

int main()
{
	gameboard grid_;
	gridUI test;
	//drawIntro();

	test.drawGrid(grid_);
	
    return 0;
}

