#include "stdafx.h"
#include "controller.h"

// drawLine
// draws line
void Controller::drawLine()
{
	cout << "-------------------------------------\n";
}

// checkDictionary
// check if word exists, then adds it to a list
void Controller::checkDictionary(string temp, vector<string> &list)
{
	if (dictionary.wordExist(temp))
	{
		list.push_back(temp);
	}
}

// printVariantMsg
// prints out the varaint message. always returns true.
bool Controller::printVariantMsg(string word, string root)
{
	cout << word << " is a variant of " << root << endl;
	return true;
}

// findSuggestions
// cycles through the world swapping, inserting, deleting, and replacing chars trying to find a word.
vector<string> Controller::findSuggestions(string word)
{
	vector<string> list;

	//create suggestions

	for (int i = 0; i < word.length(); i++)
	{
		vector<string> tempList;
		string replaceTemp;
		string swapTemp;
		string removeTemp;

		// swap chars in the string	
		// extra check prevents it swapping past the last char
		if (i < word.length() - 1)
		{
			swapTemp = word;
			swap(swapTemp[i], swapTemp[i + 1]);
			tempList.push_back(swapTemp);
		}

		//delete char
		removeTemp = word;
		removeTemp.erase(i, 1);
		tempList.push_back(removeTemp);
		
		//second loop cycles through alphabet
		for (char j = 'a'; j <= 'z'; j++)
		{
			string replaceTemp;
			string insertTemp;

			replaceTemp = word;
			insertTemp = word;

			// replace char
			replaceTemp.replace(i, 1, string(1,j) );
			tempList.push_back(replaceTemp);

			// insert char
			// assumes first char is correct, and starts inserting afterwards
			insertTemp.insert(i+1, string(1, j));
			tempList.push_back(insertTemp);
		}

		// runs through candidates to see if they exists in the dictionary
		for (int k = 0; k < tempList.size(); k++)
		{
			checkDictionary(tempList[k], list);
		}
		tempList.clear();
	}

	// print suggestion list
	if (list.size() > 0)
	{
		//sort and remove possible duplicates
		sort(list.begin(), list.end());
		list.erase(unique(list.begin(), list.end()), list.end());
		printList(list);
	}
	return list;
}

// findRootWord
// removes suffixes to check if the root word is correct
bool Controller::checkRootWord(string word)
{
	bool bVariant = false;
	int wordLength = word.size();
	//checking for -ing words

	if (wordLength > 5)
	{
		if (word.substr(wordLength - 3, 3) == "ing")
		{
			string replaceING, replaceING2;
			replaceING = word;
			replaceING.replace(wordLength - 3, 3, "e");

			//remove ing 
			if (dictionary.wordExist(word.substr(0, wordLength - 3)))
			{
				bVariant = printVariantMsg(word, word.substr(0, wordLength - 3));
			}
			// remove ing, replace with e - move moving
			else if (dictionary.wordExist(replaceING))
			{
				bVariant = printVariantMsg(word, replaceING);
			}
			// check for double constanents, then remove *ing - stop stopping
			else if (dictionary.wordExist(word.substr(0, wordLength - 4))
				&& (word[wordLength - 4] == word[wordLength - 5]))
			{
				bVariant = printVariantMsg(word, word.substr(0, word.size() - 4));
			}
		}
	}

	if (wordLength > 3)
	{
		//remove plural rules - s, es, ies, ves
		if (word.substr(wordLength - 1, 1) == "s")
		{
			string replaceIES, replaceVES;

			replaceIES = word;
			replaceVES = word;

			replaceIES.replace(wordLength - 3, 3, "y");
			replaceVES.replace(wordLength - 3, 3, "fe");

			//if s, remove s
			if (dictionary.wordExist(word.substr(0, wordLength - 1)))
			{
				bVariant = printVariantMsg(word, word.substr(0, wordLength - 1));
			}
			//if es, remove es - dish dishes
			else if (dictionary.wordExist(word.substr(0, wordLength - 2))
				&& word.substr(wordLength - 2, 2) == "es")
			{
				bVariant = printVariantMsg(word, word.substr(0, wordLength - 2));
			}
			//if ies, remove and replace with y - supplies supply
			else if (dictionary.wordExist(replaceIES)
				&& word.substr(wordLength - 3, 3) == "ies")
			{
				bVariant = printVariantMsg(word, replaceIES);
			}
			// if ves, replace with f or fe - knife knives
			else if (dictionary.wordExist(replaceVES)
				&& word.substr(wordLength - 3, 3) == "ves")
			{
				bVariant = printVariantMsg(word, replaceVES);
			}
		}

		//remove past tense rules
		if (word.substr(wordLength - 2, 2) == "ed")
		{
			string replaceIED;

			replaceIED = word;
			replaceIED.replace(wordLength - 3, 3, "y");

			//if ed, remove d - move moved
			if (dictionary.wordExist(word.substr(0, wordLength - 1))
				&& word[wordLength - 2] == 'e')
			{
				bVariant = printVariantMsg(word, word.substr(0, wordLength - 1));
			}
			//else if ed, remove ed - play played
			else if (dictionary.wordExist(word.substr(0, wordLength - 2)))
			{
				bVariant = printVariantMsg(word, word.substr(0, wordLength - 2));
			}
			//else if double constanent + ed, remove *ed - stop stopped
			else if (dictionary.wordExist(word.substr(0, wordLength - 3))
				&& word[wordLength - 3] == word[wordLength - 4])
			{
				bVariant = printVariantMsg(word, word.substr(0, wordLength - 3));
			}
			//else ied, remove ied and replace with y - supply supplied
			else if (dictionary.wordExist(replaceIED)
				&& word.substr(wordLength - 3, 3) == "ied")
			{
				bVariant = printVariantMsg(word, replaceIED);
			}
		}

		//remove - ly variations
		if (word.substr(wordLength - 2, 2) == "ly")
		{
			string replaceLY, replaceILY;

			replaceLY = word;
			replaceILY = word;

			replaceLY.replace(wordLength - 2, 2, "e");
			replaceILY.replace(wordLength - 3, 3, "y");

			// remove y - full fully 
			if (dictionary.wordExist(word.substr(0, wordLength - 1)))
			{
				bVariant = printVariantMsg(word, word.substr(0, wordLength - 1));
			}
			// remove ly - slow slowly
			else if (dictionary.wordExist(word.substr(0, wordLength - 2)))
			{
				bVariant = printVariantMsg(word, word.substr(0, wordLength - 2));
			}
			// remove ly replace with e - comfortable comfortably multiple multiply
			else if (dictionary.wordExist(replaceLY))
			{
				bVariant = printVariantMsg(word, replaceLY);
			}
			// remove ily replace with y - happy happily
			else if (dictionary.wordExist(replaceILY)
				&& word.substr(wordLength - 3, 3) == "ily")
			{
				bVariant = printVariantMsg(word, replaceILY);
			}
			// removing ally - heroic heroically
			// check for cally, remove ally
			else if (dictionary.wordExist(word.substr(0, wordLength - 4))
				&& word.substr(wordLength - 5, 5) == "cally")
			{
				bVariant = printVariantMsg(word, word.substr(0, wordLength - 4));
			}
		}
	}
	return bVariant;
}

// printList
// prints list of possible correct words
void Controller::printList(vector<string> list)
{
	cout << "Possible suggestions: \n";
	for (int i = 0; i < list.size(); i++)
	{
		cout << list[i] << endl;
	}
}

// spellCheck
// main spellCheck function
void Controller::spellCheck()
{
	string word;
	bool bExit = true;

	//header
	cout << "SpellChecker\n";
	drawLine();
	//load txt file of words
	dictionary.loadDict();

	do 
	{
		drawLine();
		//ask user for word
		cout << "Please enter a word to be checked: ";
		word = input.getWord();

		//check if word exists
		if (dictionary.wordExist(word))
		{
			cout << word << " is spelled correctly.\n";
		}
		//finding the root word
		else
		{
			//check if the root word is correct or misspelled
			if (!checkRootWord(word))
			{
				cout << word << " is not spelled correctly, or does not exist in dictionary.\n";
				findSuggestions(word);
			}
		}

		drawLine();
		cout << "Would you like to enter another word?\n";
		bExit = input.getInput();

	} while (bExit);
}



