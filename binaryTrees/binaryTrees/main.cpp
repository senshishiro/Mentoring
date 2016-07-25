// binaryTrees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tree.h"
#include <vector>

int main()
{
	BinaryTree tree;

	//vector<int> testData = {5, 3, 10, 7, 8, 1, 6};
	vector<int> testData = {5, 6, 3, 4, 2, 1};
	for (int i = 0; i < testData.size(); i++)
	{
		cout << "-------------------------------\n";
		cout << "adding: " << testData[i] << endl;
		tree.addNode(testData[i]);
		cout << "-------------------------------\n";
	}
	

	tree.printTree(tree.root);
	cout << endl;
	tree.search(8);
	cout << endl;
	tree.removeNode(1);
	tree.printTree(tree.root);

	cout << endl;
	cout << "root: " << (tree.root)->data << endl;
    return 0;
}

