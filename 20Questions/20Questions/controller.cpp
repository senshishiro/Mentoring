#include "stdafx.h"
#include "controller.h"

using namespace std;

// constructor
GameController::GameController()
{
	bWin = false;
}


void GameController::gameStart()
{

	bool bPlayAgain = true;

	// import questions from text file, and build tree.
	importQuestions();
	
	if (test.root == NULL)
	{
		cout << "Unable to start game\n";
	}
	else
	{
		drawIntro();

		do
		{
			// start tree navigation
			test.askQuestion(test.root, bWin);

			drawLine();

			if (bWin)
			{
				cout << "You Win!\n";
				askToCreateAnswer();
			}
			else
			{
				cout << "Computer Wins!\n";
			}

			// ask player if they want to play again
			bPlayAgain = playAgain();

			if (bPlayAgain)
			{
				drawIntro();
				bWin = false;
			}

		} while (bPlayAgain);

		drawLine();

		if (test.isModified())
		{
			// update text file when exiting
			updateTxt();
		}

		cout << "Thanks for playing!\n";
	}

}

// convertQuestionText
// read questions from text file. store data into the a vector.
vector<Qset> GameController::convertQuestionText()
{
	ifstream questions(TEXTPATH);
	string line;
	vector <Qset> qStorage;
	Qset dataSet;


	if (questions.is_open())
	{
		while (getline(questions, line))
		{
			//@TODO convert to true/false for type?
			if ((line.at(0) == 'A' || line.at(0) == 'Q') && line.at(1) == ':')
			{
				dataSet.type = line.at(0);
			}
			else
			{
				dataSet.data = line;
			}

			if (dataSet.type != "" && dataSet.data != "")
			{
				// add to vector when both type and data have been filled. Then reset the values.
				qStorage.push_back(dataSet);
				dataSet.type = "";
				dataSet.data = "";
			}
		}
		questions.close();
	}
	else
	{
		cout << "Unable to read file\n";
	}

	return qStorage;
}

// importQuestions
// populate tree with questions from vector
void GameController::importQuestions()
{
	cout << "Loading Questions...";
	vector<Qset> questions = convertQuestionText();

	// count is used to advance the questions in the vector
	unsigned int count = 0;

	if (questions.size() > 0)
	{
		cout << "Done. " << questions.size() << " questions loaded.\n" << "Building Tree...";

		// build question tree
		test.insertNode(test.root, questions, count);

		cout << "Done. Nodes created : " << count << "\n";
	}

}

void GameController::askToCreateAnswer()
{
	cout << "Would you like to add your object to list?\n";

	if (Inputs::getInput())
	{
		NewAnswer answer;
		answer = getNewAnswer();
		test.addNewAnswer(answer, test.lastAnswer, test.previousToLastAnswer);
		test.updateModified(true);
		cout << "Thank You! Your question and answer has been added.\n";
	}
}

NewAnswer GameController::getNewAnswer()
{
	NewAnswer answer;
	bool verify = false;

	do
	{
		// get new answer from player
		cout << "What were you thinking of?\n";
		cout << "Answer:";
		answer.obj = Inputs::getData();

		// get new question from player
		cout << "Please enter a yes no question that differentiates your object from the computer's object?\n";
		cout << "Question:";
		answer.question = Inputs::getData();

		// get new question from player
		cout << "What is the answer to the your question a yes or no?\n";
		answer.leftRight = Inputs::getInput();

		// verify
		cout << "---------------------------------------------\n";
		cout << "Computer's answer: " << test.lastAnswer->data << endl;
		cout << "Object: " << answer.obj << endl;
		cout << "Question: " << answer.question << endl;
		cout << "Answer: ";

		if (answer.leftRight)
		{
			cout << "yes\n";
		}
		else
		{
			cout << "no\n";
		}

		cout << "Does this info look correct?\n";
		verify = Inputs::getInput();

		if (!verify)
		{
			answer.obj = "";
			answer.question = "";
			answer.leftRight = false;
		}

	} while (!verify);

	return answer;
}


//-----------------------------------------------
// updateTxt()
// Dumps all of the trees contents into a text file

void GameController::updateTxt()
{
	fstream txtFile(TEXTPATH);

	if (txtFile.is_open())
	{
		printToTxt(txtFile, test.root);
		txtFile.close();
		//cout << "text file updated\n";
	}
	else
	{
		cerr << "Cannot access file. Unable to save updates from this session!\n";
	}
}

void GameController::printToTxt(fstream &stream, Node * node)
{
	if (node == NULL)
		return;

	if (node->isQuestion)
	{
		stream << "Q:\n";
	}
	else
	{
		stream << "A:\n";
	}

	stream << node->data << endl;

	printToTxt(stream, node->right);
	printToTxt(stream, node->left);
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

//Asks player if they want to exit
bool GameController::playAgain()
{
	cout << "Would you like to play again?\n";
	return Inputs::getInput();
}
