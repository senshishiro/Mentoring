#pragma once
#include <string>
#include <iostream>
#include "qtree.h"
#include "inputs.h"


class GameController
{
private:
	//const string TEXTPATH = "question.txt";
	const string TEXTPATH = "bigquestion.txt";
	
	QTree test;
	bool bWin;

	// loads text file into a vector
	vector<Qset> convertQuestionText();

	void drawLine();
	void drawIntro();
	bool playAgain();

	//Load questions and build tree
	void importQuestions();

	NewAnswer getNewAnswer();
	// recursive function for dumping info from the tree to text file
	void updateTxt();
	void printToTxt(fstream &stream, Node * node);

public:
	GameController();
	void gameStart();

	// ask player if they want to add a new answer/question
	void askToCreateAnswer();

};
