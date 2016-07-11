#include "stdafx.h"
#include "tree.h"

BinaryTree::BinaryTree()
{
	root = NULL;
}


void BinaryTree::search(int value)
{

	if (searchNode(root, value) != NULL)
	{
		cout << value << " exists in tree\n";
	}
	else
	{
		cout << "Value does not exists in tree";
	}
}

Node * BinaryTree::searchNode(Node * n, int value)
{
	if (n->data == value)
	{
		return n;
	}
	else if (n->data > value)
	{
		searchNode(n->left, value);
	}
	else
	{
		searchNode(n->right, value);
	}
}

Node * BinaryTree::createNode(Node * temp, int value)
{
	temp = new Node;
	temp->data = value;
	temp->left = NULL;
	temp->right = NULL;

	if (root == NULL)
	{
		temp->parent = NULL;
		root = temp;
	}

	return temp;
}
void BinaryTree::addNode(int value)
{
	insertNode(root, value);

}

Node * BinaryTree::insertNode(Node * temp, int value)
{
	if (temp == NULL)
	{
		cout << "node added: " << value << endl;
		return createNode(temp, value);
	}
	else if (temp->data == value)
	{
		temp->data = value;
	}
	else
	{
		//Node * child;
		if (temp->data > value)
		{
			//insertNode(temp->left, value);
			temp->left = insertNode(temp->left, value);
			cout << "left\n";
			cout << "inserting: " << (temp->left)->data << endl;
			cout << "parent: " << temp->data << endl;
			(temp->left)->parent = temp;
		}
		else
		{
			//insertNode(temp->right, value);
			temp->right = insertNode(temp->right, value);
			cout << "right\n";
			cout << "inserting: " << (temp->right)->data << endl;
			cout << "parent: " << temp->data << endl;
			(temp->right)->parent = temp;
		}

		return temp;
	}

	
}

void BinaryTree::deleteNode(int value)
{
	//find node
	Node* n;
	n = searchNode(root, value);

	cout << n->data << endl;
	cout << (n->parent)->right << endl;
	//delete leaf
	
	if (n->left == NULL && n->right == NULL)
	{
		if ((n->parent)->left == n)
		{
			(n->parent)->left = NULL;
		}
		else
		{
			(n->parent)->right = NULL;
		}

		delete n;
	}
}

void BinaryTree::printTree(Node * node)
{
	if (node == NULL)
		return;

	printTree(node->left);
	cout << node->data << " ";
	printTree(node->right);
}

