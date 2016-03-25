/*
Number Guesseing Game X
by: Chi Kong
Description: An Advanced version of the previous number guessing game.

*/


#include "stdafx.h"
#include "time.h"
#include <iostream>
#include <sstream>

using namespace std;

//Draws a dotted line.
void drawLine()
{
	for (int i = 0; i < 40; i++)
	{
		cout << "-";
	}
	cout << endl;
}

string getInput()
{
	string strInput;
	getline(cin, strInput);
	//cout << "you entered: " << strInput << endl;
	return strInput;	
}

//function that converts strings to lowercase
string toLowercase(string strText)
{
	for (int i = 0; i < strText.length(); i++)
	{
		strText[i] = tolower(strText[i]);
	}

	return strText;
}

bool numberCompare(int iValue1, int iValue2)
{
	if (iValue1 == iValue2)
		return true;
	else
		return false;
}

int genRandNum()
{
	int x;
	srand(time(NULL));
	x = rand() % 10 + 1;

	return x;
}

void drawIntro()
{
	cout << "Number Guessing Game X\n";
	cout << "Please enter a number between 1-10.\n";
	cout << "Press X anytime to exit.\n";
	drawLine();
}


// Ask the user if they want to play again
bool exit()
{
	string strInput="";
	bool x = true;

	while (x)
	{
		cout << "Would you like to play again(Y/N)? ";
		getline(cin, strInput);
		strInput = toLowercase(strInput);

		if (strInput == "n")
			return true;
		else if (strInput == "y")
			return false;
		else
			cout << "Please enter y/n.\n";
	};

	return true;

}

int _tmain(int argc, _TCHAR* argv[])
{

	int iGuessCount;	 //tracks number of guesses
	int iRandNum;
	string strUserEntry = "";
	int iTest = 0;
	bool bExit;

	//Initialization. 
	iRandNum = genRandNum(); //Generate random number between 1-10
	iGuessCount = 0;
	bExit = false;

	drawIntro();

	//main game loop. Loop keeps running until the player gusses correctly.
	do
	{
		cout << "Enter a Value: ";
		strUserEntry = getInput();
		
		//check if string can be converted and stored into an int
		if (!(stringstream(strUserEntry) >> iTest))
		{
			//Check if the user entered a x, or some other letter/jiberish
			if (toLowercase(strUserEntry) == "x")
				bExit = true;
			else
				cerr << "Please enter a number, or x to exit\n";
		}
		else
		{
			if (iTest > 0 && iTest <= 10)
			{
				iGuessCount++; //tracking guess count

				if (numberCompare(iTest, iRandNum))
				{
					//plural check 
					string strGuess = "guesses";
					if (iGuessCount == 1)
						strGuess = "guess";

					cout << "You have guessed correctly with " << iGuessCount << " " << strGuess << "!\n";
					bExit = exit();

					//reinitialize to play again
					if (!bExit)
					{	
						iGuessCount = 0;
						iRandNum = genRandNum();
						cout << endl;
						drawIntro();
					}
				}
				else
				{
					cout << "You have guessed incorrectly. Please try again.\n";	
				}
				
			}
			else
				cerr << "Please enter a number between 1-10.\n";
		}


	} while (!bExit);

	//exit message
	drawLine();
	cout << "Thanks for Playing!\n";

	return 0;
}


