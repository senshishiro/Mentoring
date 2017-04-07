#include "stdafx.h"
#include "inputs.h"

// toLowercase
// converts a string to all lowercase
string Inputs::toLowercase(string strText)
{
	for (int i = 0; i < strText.length(); i++)
	{
		strText[i] = tolower(strText[i]);
	}

	return strText;
}

// getInput
// gets yes or no from the player
bool Inputs::getInput()
{
	bool valid = false;
	bool isYes = true;
	string input;

	do
	{
		cout << "Enter(y/n): ";
		cin >> input;

		input = toLowercase(input);

		if (input == "yes" || input == "y")
		{
			isYes = true;
			valid = true;
		}
		else if (input == "no" || input == "n")
		{
			isYes = false;
			valid = true;
		}
		else
		{
			cout << "Please enter yes or no.\n";
		}
	} while (!valid);

	return isYes;
}

// getWord()
// get input for adding a new querstion and answer node.
string Inputs::getActor()
{
	string data = "";
	do
	{
		getline(cin, data);

	} while (data == "" || data == " ");

	return data;
}