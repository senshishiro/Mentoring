#include "stdafx.h"
#include "qtree.h"


// Constructor
QTree::QTree()
{
	root = NULL;
	bModified = false;
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
void QTree::insertNode(Node * &n, vector<Qset> &questions, unsigned int &count)
{
	// base case - add answer node
	if (n == NULL && questions[count].type == "A")
	{
		n = createNode(n, questions[count].data, false);
		count++;		
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
	}
}


//---------------------------------------------------------
// treeTraversal functions
// Navigates the tree through y/n questions

// treeTraversal
// calls askQuestion
void QTree::askQuestion(Node * n, bool &bWin)
{
	treeTraversal(n, NULL, bWin);
}

// askQuestion
// traverses the tree based on yes no input
Node* QTree::treeTraversal(Node * n, Node * previous, bool &bWin)
{
	if (n->isQuestion == false)
	{
		cout << "Are you thinking of: "<< n->data << "?\n";

		if (Inputs::getInput())
		{
			bWin = false;
		}
		else
		{	
			bWin = true;
			lastAnswer = n;
			previousToLastAnswer = previous;		
		}
		return n;
	}
	else
	{
		cout << "Q: " << n->data << endl;

		if (Inputs::getInput())
		{
			treeTraversal(n->right, n, bWin);
		}
		else
		{
			treeTraversal(n->left, n, bWin);
		}
	}
}


// addNewAnswer()
// ask the player for a answer and question. Updates the tree and text file
void QTree::addNewAnswer(NewAnswer answerData, Node * compAnswer, Node * previous)
{
	Node * question;
	Node * answer;
		
	// create answer node
	answer = createNode(NULL, answerData.obj, false);

	// create question node
	question = createNode(NULL, answerData.question, true);

	// determine if it goes left or right
	if (answerData.leftRight)
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
}


bool QTree::isModified()
{
	return bModified;
}

void  QTree::updateModified(bool value)
{
	bModified = value;
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