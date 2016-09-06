#include "stdafx.h"
#include "tree.h"

//Binary Tree Constructor
BinaryTree::BinaryTree()
{
	root = NULL;
}

//----------------------------------------------------
//Binary Tree Search Functions

// Search
// Prints out message depending SearchNode() results
void BinaryTree::search(int value)
{
	if (searchNode(root, value) == false)
	{
		cout << "Value does not exists in tree";		
	}
	else
	{
		cout << value << " exists in tree\n";
	}
}

// Search Node
// Recursively search throus the tree looking for value
bool BinaryTree::searchNode(Node * n, int value)
{
	//base case
	if (n->data == value)
	{
		return true;
	}
	else if (n->data > value)
	{
		//NULL check
		if (n->left == NULL)
			return false;
		else
		{
			//search left subtree
			return searchNode(n->left, value);
		}	
	}
	else if(n->data < value)
	{
		//NULL check
		if (n->right == NULL)
		{
			return false;
		}
		else
		{
			//search right subtree
			return searchNode(n->right, value);
		}
	}
	return false;
}

//----------------------------------------------------
// Insertion functions

// addNode
// Helper function that calls Insert Node
void BinaryTree::addNode(int value)
{
	insertNode(root, value);
}

// createNode
// Helper function that initializes and creates a new node
Node * BinaryTree::createNode(Node * temp, int value)
{
	temp = new Node;
	temp->data = value;
	temp->left = NULL;
	temp->right = NULL;
	temp->height = 0;

	if (root == NULL)
	{
		temp->parent = NULL;
		root = temp;
	}

	return temp;
}

//insertNode
// Adds node after recursively finding a leaf
Node * BinaryTree::insertNode(Node * n, int value)
{
	//Create Node
	if (n == NULL)
	{
		//cout << "node added: " << value << endl;
		return createNode(n, value);
	}
	//Overwrite valuse if it already exists
	else if (n->data == value)
	{
		n->data = value;
	}
	else
	{
		//Insert to left if value is less than current node, and update parent
		if (n->data > value)
		{
			n->left = insertNode(n->left, value);
			(n->left)->parent = n;
		}
		//Insert to right if value is less than current node, and update parent
		else
		{
			n->right = insertNode(n->right, value);
			(n->right)->parent = n;
		}
		//Update heights
		n->height = height(n);
		//cout << "balanced: " << (height(n->right) - height(n->left)) <<endl;

		//Rebalance after adding
		rebalance(n);

		return n;
	}
}

//----------------------------------------------------
//Delete Functions

// remove Node
// Helper functions that calls deleteNode
void BinaryTree::removeNode(int value)
{
	deleteNode(root, value);
}


//successorNode
// Finds the next larget node
Node * BinaryTree::successorNode(Node * n)
{
	Node * temp = n->right;
	//find the smallest node in the right subtree
	if (n->right != NULL)
	{
		while (temp->left)
		{
			temp = temp->left;
		}
	}
	return temp;
}

//deleteNode
// Recursively searches the tree for node, then deletes based on the number of children
Node* BinaryTree::deleteNode(Node * n, int value)
{
	//base case
	if (n == NULL)
	{
		return n;
	}
	//Check left subtree
	else if (value < n->data)
	{	
		n->left = deleteNode(n->left, value);
	}
	//Check right subtree
	else if (value > n->data)
	{
		n->right = deleteNode(n->right, value);
	}
	//deletion
	else
	{
		//leaf
		if (n->left == NULL && n->right == NULL)
		{
			cout << "deleting: " << n->data << endl;
			delete n;
			n = NULL;		
		}
		//single child
		else if (n->left == NULL || n->right == NULL)
		{
			// TODO: Might be able to condense code here
			Node* temp = n;
			// checks which node is null, then overwrite n with child
			if (n->left == NULL)
			{
				n = n->right;
			}
			else
			{
				n = n->left;
			}
			
			//Update root and parent
			if (temp == root)
			{
				n->parent = NULL;
				root = n;
			}
			else
			{
				n->parent = temp->parent;
			}
				
			delete temp;
		}
		//double child
		else
		{
			//Find successor
			Node * succesor = successorNode(n);
			//replace the data that's about to be deleted with successor
			n->data = succesor->data;
			// delete the duplicate
			n->right = deleteNode(n->right, n->data);
		}
	}

	//Update heights
	if (n != NULL)
	{
		n->height = height(n);
		rebalance(n);
	}
	return n;
}

//----------------------------------------------------
//rebalance functions

//max
// Finds the max between two values
int BinaryTree::max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

//height
// Calculates the node's height recursively
int BinaryTree::height(Node * n)
{
	// leaf
	if (n == NULL)
	{
		return -1;
	}
	else
	{
		return (1 + max(height(n->right), height(n->left)));
	}
}

//rebalance
// checks the difference between the height of the subtrees. Determines if left or right heavy. 
// rebalances with single or double rotations
void BinaryTree::rebalance(Node * n)
{
	int balance;
	//calculate the difference between the two subtrees
	balance = (height(n->left) - height(n->right));

	//left heavy
	if (balance > 1)
	{
		//cout << "left unbalanced: " << balance << endl;
		//checks the height of the left vs right subtrees to see if it needs to be rotated once or twice
		if (height(n->left->left) >= height(n->left->right))
		{
			n = rotateRight(n);
		}		
		else
		{
			n = rotateLeftRight(n);
		}
	}
	//right heavy
	else if (balance < -1)
	{
		//cout << "right unbalanced: " << balance << endl;
	//checks the height of the right vs left subtrees to see if it needs to be rotated once or twice
		if (height(n->right->right) >= height(n->right->left))
		{
			n = rotateLeft(n);
		}
		else
		{
			n = rotateRightLeft(n);
		}		
	}
}

//rightRotation
Node * BinaryTree::rotateRight(Node * n)
{
	Node * pivot = n->left;
	
	//update parent of pivot
	pivot->parent = n->parent;

	n->left = pivot->right;

	//update parent of n->left
	if (n->left != NULL)
	{
		(n->left)->parent = n;
	}

	//make n child of pivot
	pivot->right = n;
	n->parent = pivot;

	//reattach n's parent with pivot
	if (pivot->parent != NULL)
	{
		if (pivot->parent->left == n)
		{
			pivot->parent->left == pivot;
		}
		else
		{
			pivot->parent->right == pivot;
		}
	}
	
	//update root
	if (n == root)
	{
		root = pivot;
	}

	//recalculate height after rotation
	pivot->height = height(pivot);
	n->height = height(n);

	return pivot;
}

//left Rotation
Node * BinaryTree::rotateLeft(Node * n)
{
	Node * pivot = n->right;
	//update parent of pivot
	pivot->parent = n->parent;
	
	//updated n-> right to point to pivot->left
	n->right = pivot->left;
	//update parent 
	if (n->right != NULL)
	{
		(n->right)->parent = n;
	}
	
	//make n child of pivot
	pivot->left = n;
	n->parent = pivot;

	//reattach n's parent with pivot
	if (pivot->parent != NULL)
	{
		if (pivot->parent->right == n)
			pivot->parent->right == pivot;
		else
			pivot->parent->left == pivot;
	}

	//update root
	if (n == root)
	{
		root = pivot;
	}

	//recalculate height after rotation
	pivot->height = height(pivot);
	n->height = height(n);

	return pivot;
}

//rotateRightLeft
//rotate right first then left
Node * BinaryTree::rotateRightLeft(Node * n)
{
	n->right = rotateRight(n->right);
	return rotateLeft(n);
}

//rotateLeftRight
//rotate left first then right
Node * BinaryTree::rotateLeftRight(Node * n)
{
	n->left = rotateLeft(n->left);
	return rotateRight(n);
}

//--------------------------------------------------
//printTree
// recurively prints the tree. 
void BinaryTree::printTree(Node * node)
{
	if (node == NULL)
		return;

	printTree(node->left);
	cout << node->data << "(" << node->height << ") ";
	printTree(node->right);
}

