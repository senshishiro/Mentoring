#include "stdafx.h"
#include "qtree.h"




// Constructor
QTree::QTree()
{
	root = NULL;
}

// convertQuestionText
// read questions from text file. store data into the a vector.
vector<Qset> QTree::convertQuestionText()
{
	ifstream questions("bigquestion.txt");
	string line;
	vector <Qset> qStorage;
	Qset dataSet;

	if (questions.is_open())
	{
		while (getline(questions, line))
		{
			if (line.at(0) == 'A' || line.at(0) == 'Q')
			{
				dataSet.type = line.at(0);
			}
			else
			{
				dataSet.data = line;
			}

			if (dataSet.type != "" && dataSet.data != "")
			{
				qStorage.push_back(dataSet);
				dataSet.type = "";
				dataSet.data = "";
			}
		}
		questions.close();
	}
	else
	{
		cout << "unable to read file\n";
	}

	return qStorage;
}

// importQuestions
// populate tree with questions from vector
void QTree::importQuestions()
{
	cout << "Loading Questions...";
	vector<Qset> questions = convertQuestionText();
	// count is used to advance the questions in the vector
	int count = 0;

	// build question tree
	insertNode(root, questions, count);
	cout << "Done.\n";
}

// createNode
Node * QTree::createNode(Node * n, string data, bool type)
{
	n = new Node;
	n->isQuestion = type;
	n->data = data;
	n->right = NULL;
	n->left = NULL;
	return n;
}

// insertNode
// creates node based on if it's a question or answer.
Node* QTree::insertNode(Node * &n, vector<Qset> questions, int &count)
{
	// base case
	if (n == NULL && questions[count].type == "A")
	{
		n = createNode(n, questions[count].data, false);
		count++;

		return n;			
	}
	// question add
	else if (n == NULL && questions[count].type == "Q")
	{
		n = createNode(n, questions[count].data, true);

		if (root == NULL)
		{
			//cout << "root set";
			root = n;
		}

		count++;
		insertNode(n->right, questions, count);
		insertNode(n->left, questions, count);
	}
	else
	{
		cerr << "Nothing to Add.\n";
		return n;
	}
}

// toLowercase
// converts a string to all lowercase
string QTree::toLowercase(string strText)
{
	for (int i = 0; i < strText.length(); i++)
	{
		strText[i] = tolower(strText[i]);
	}

	return strText;
}

// getInput
// gets yes or no from the player
bool QTree::getInput()
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

//Asks player if they want to exit
bool QTree::playAgain()
{
	string strInput = "";
	bool x = true;

	while (x)
	{
		//ui.drawLine();
		//ui.draw(ui.game_playAgain);
		getline(cin, strInput);
		strInput = toLowercase(strInput);

		if (strInput == "n")
		{
			return true;
		}
		else if (strInput == "y")
		{
			//ui.drawLine();
			return false;
		}
		else
		{
			cout << "Please enter y/n.\n";
		}
	};

	return true;
}

// treeTraversal
// calls askQuestion
void QTree::treeTraversal(Node * n)
{
	askQuestion(n);
}

// askQuestion
// traverses the tree based on yes no input
Node* QTree::askQuestion(Node * n)
{
	if (n->isQuestion == false)
	{
		cout << "A: "<< n->data << endl;
		return n;
	}
	else
	{
		cout << "Q: " << n->data << endl;

		if (getInput())
		{
			askQuestion(n->right);
		}
		else
		{
			askQuestion(n->left);
		}
	}
}

/*
void QTree::printTree(Node * node)
{
	if (node == NULL)
		return;

	cout << node->data << endl;
	printTree(node->right);
	printTree(node->left);	
}*/