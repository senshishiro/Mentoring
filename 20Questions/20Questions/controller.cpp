#include "stdafx.h"
#include "controller.h"

using namespace std;


void GameController::gameStart()
{
	QTree test;
	bool bPlayAgain = true;

	// import questions from text file, and build tree.
	test.importQuestions();
	drawIntro();

	do 
	{	
		// start tree navigation
		test.treeTraversal(test.root);

		drawLine();

		// ask player if they want to play again
		bPlayAgain = test.playAgain();

		if (bPlayAgain)
		{
			drawIntro();
		}

	} while (bPlayAgain);
	
	drawLine();

	if (test.bModified)
	{
		// update text file when exiting
		test.updateTxt();
	}

	cout << "Thanks for playing!\n";
}

void GameController::drawLine()
{
	cout << "-------------------------------------\n";
}

void GameController::drawIntro()
{
	drawLine();
	cout << "Guessing Game\n"
		 << "Please think of an object, and the computer will try to guess it.\n";
	drawLine();
}


