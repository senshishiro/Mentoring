#include "stdafx.h"
#include "qtree.h"


// Constructor
QTree::QTree()
{
	root = NULL;
	bModified = false;
}

// convertQuestionText
// read questions from text file. store data into the a vector.
vector<Qset> QTree::convertQuestionText()
{
	//ifstream questions("bigquestion.txt");
	ifstream questions("question.txt");
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
void QTree::importQuestions()
{
	cout << "Loading Questions...";
	vector<Qset> questions = convertQuestionText();

	// count is used to advance the questions in the vector
	unsigned int count = 0;

	cout << "Done. " << questions.size() << " questions loaded.\n" << "Building Tree...";

	// build question tree
	insertNode(root, questions, count);

	cout << "Done. Nodes created : " << count << "\n";
}

// createNode
Node * QTree::createNode(Node * n, string data, bool type)
{
	n = new Node;
	n->isQuestion = type;
	n->data = data;
	n->right = NULL;
	n->left = NULL;
	//cout << data << endl;
	return n;
}

// insertNode
// creates node based on if it's a question or answer.
Node* QTree::insertNode(Node * &n, vector<Qset> &questions, unsigned int &count)
{
	// base case - add answer node
	if (n == NULL && questions[count].type == "A")
	{
		n = createNode(n, questions[count].data, false);
		count++;
		return n;			
	}
	// add question node
	else if (n == NULL && questions[count].type == "Q")
	{
		n = createNode(n, questions[count].data, true);
		count++;

		if (root == NULL)
		{
			root = n;
		}

		insertNode(n->right, questions, count);
		insertNode(n->left, questions, count);
	}
	else
	{
		cerr << "Nothing to Add.\n";
		return n;
	}
}


//---------------------------------------------------------
// treeTraversal functions
// Navigates the tree through y/n questions

// treeTraversal
// calls askQuestion
void QTree::treeTraversal(Node * n)
{
	askQuestion(n, NULL);
}

// askQuestion
// traverses the tree based on yes no input
Node* QTree::askQuestion(Node * n, Node * previous)
{
	if (n->isQuestion == false)
	{
		cout << "Are you thinking of: "<< n->data << "?\n";

		if (getInput())
		{
			cout << "Computer Wins!\n";
		}
		else
		{
			cout << "You Win!\n";

			// ask player if they want to add a new answer/question
			cout << "Would you like to add your object to list?\n";

			if (getInput())
			{
				addNewAnswer(n, previous);
				bModified = true;
			}
		}
		return n;
	}
	else
	{
		cout << "Q: " << n->data << endl;

		if (getInput())
		{
			askQuestion(n->right, n);
		}
		else
		{
			askQuestion(n->left, n);
		}
	}
}


// addNewAnswer()
// ask the player for a answer and question. Updates the tree and text file
void QTree::addNewAnswer(Node * compAnswer, Node * previous)
{
	string newAnswer;
	string newQuestion;
	bool yesno;
	bool verify = false;

	Node * question;
	Node * answer;
	
	do 
	{
		// get new answer from player
		cout << "What were you thinking of?\n";
		cout << "Answer:";
		newAnswer = getData();

		// get new question from player
		cout << "Please enter a yes no question that differentiates your object from the computer's object?\n";
		cout << "Question:";
		newQuestion = getData();

		// get new question from player
		cout << "What is the answer to the your question a yes or no?\n";
		yesno = getInput();

		// verify
		cout << "---------------------------------------------\n";
		cout << "Computer's answer: " << compAnswer->data << endl;
		cout << "Object: " << newAnswer << endl;
		cout << "Question: " << newQuestion << endl;
		cout << "Answer: ";

		if (yesno)
		{
			cout << "yes\n";
		}
		else
		{
			cout << "no\n";
		}

		cout << "Does this info look correct?\n";
		verify = getInput();

		if (!verify)
		{
			newAnswer = "";
			newQuestion = "";
			yesno = false;
		}
	
	} while (!verify);



	// create answer node
	answer = createNode(NULL, newAnswer, false);

	// create question node
	question = createNode(NULL, newQuestion, true);

	if (yesno)
	{
		question->left = compAnswer;
		question->right = answer;
	}
	else
	{
		question->right = compAnswer;
		question->left= answer;
	}


	// swap compAnswer with new question
	if ((previous->left)->data == compAnswer->data)
	{
		previous->left = question;
	}
	else
	{
		previous->right = question;
	}

	cout << "Thank You! Your question and answer has been added.\n";
}


//----------------------------------------------------------------
// input functions

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

// getData()
// get input for adding a new querstion and answer node.
string QTree::getData()
{
	string data = "";
	do 
	{
		getline(cin, data);

	} while (data == "" || data == " ");
	
	return data;
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
	cout << "Would you like to play again?\n";
	return getInput();
}

//-----------------------------------------------
// updateTxt()
// Dumps all of the trees contents into a text file

void QTree::updateTxt()
{
	fstream txtFile("question.txt");

	if (txtFile.is_open())
	{
		printToTxt(txtFile, root);
		txtFile.close();
		//cout << "text file updated\n";
	}
	else
	{
		cerr << "Cannot access file. Unable to save updates from this session!\n";
	}
}

void QTree::printToTxt(fstream &stream, Node * node)
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

/*
//------------------------------------------------------------
// treeSize()
// recursive function to count the number of nodes in a tree
void QTree::treeSize()
{
	unsigned int count = 0;
	count = treeNodes(root);

	cout << "Nodes: " << count << endl;
}

unsigned int QTree::treeNodes(Node * n)
{
	if (n == NULL)
	{
		return 0;
	}
	return 1 + treeNodes(n->right) + treeNodes(n->left);
}

//------------------------------------------------------------
// printTree()
// ouputs contents of the tree
void QTree::printTree(Node * node)
{
	if (node == NULL)
		return;

	cout << node->data << endl;
	printTree(node->right);
	printTree(node->left);	
}*/