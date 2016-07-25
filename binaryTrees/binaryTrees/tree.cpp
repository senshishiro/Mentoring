#include "stdafx.h"
#include "tree.h"





BinaryTree::BinaryTree()
{
	root = NULL;
}


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
			return searchNode(n->left, value);
		}	
	}
	else if(n->data < value)
	{
		//NULL check
		if (n->right == NULL)
			return false;
		else
			return searchNode(n->right, value);
	}

	return false;
}

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
void BinaryTree::addNode(int value)
{
	insertNode(root, value);
}

Node * BinaryTree::insertNode(Node * n, int value)
{
	if (n == NULL)
	{
		cout << "node added: " << value << endl;
		//Update heights

		return createNode(n, value);
	}
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


		rebalance(n);

		return n;
	}

}


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

void BinaryTree::removeNode(int value)
{
	deleteNode(root, value);
}
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

			if (n->left == NULL)
			{
				n = n->right;
			}
			else
			{
				n = n->left;
			}

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


//rebalance
//max

int BinaryTree::max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

//height
int BinaryTree::height(Node * n)
{
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

void BinaryTree::rebalance(Node * n)
{
	int balance;
	balance = (height(n->left) - height(n->right));

	if (balance > 1)
	{
		cout << "right unbalanced: " << balance << endl;
		if (height(n->left->left) >= height(n->left->right))
		{
			n = rotateRight(n);
		}		
		else
		{
			n = rotateLeftRight(n);
		}
	}
	else if (balance < -1)
	{
		cout << "left unbalanced: " << balance << endl;

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
	pivot->parent = n->parent;
	
	n->left = pivot->right;

	//update parent 
	if (n->left != NULL)
	{
		(n->left)->parent = n;
	}

	pivot->right = n;
	n->parent = pivot;

	//reattach n's parent with pivot
	if (pivot->parent != NULL)
	{
		if (pivot->parent->left == n)
			pivot->parent->left == pivot;
		else
			pivot->parent->right == pivot;
	}

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
	pivot->parent = n->parent;

	n->right = pivot->left;

	//update parent 
	if (n->right != NULL)
	{
		(n->right)->parent = n;
	}

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

	if (n == root)
	{
		root = pivot;
	}

	//recalculate height after rotation
	pivot->height = height(pivot);
	n->height = height(n);

	return pivot;
}
//rotate right first then left
Node * BinaryTree::rotateRightLeft(Node * n)
{
	n->right = rotateRight(n->right);
	return rotateLeft(n);
}

Node * BinaryTree::rotateLeftRight(Node * n)
{
	n->left = rotateLeft(n->left);
	return rotateRight(n);
}

void BinaryTree::printTree(Node * node)
{
	if (node == NULL)
		return;

	printTree(node->left);
	cout << node->data << "(" << node->height << ") ";
	printTree(node->right);
}

