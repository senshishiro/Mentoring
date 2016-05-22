#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;



//sort
class SortData
{
public:
	//int data[];

	void swap(vector<int> &data, int a, int b);

	vector<int> bubbleSort(vector<int> data);
	vector<int> selectionSort(vector<int> data);
	vector<int> insertionSort(vector<int> data);
	void printList(vector<int> data);
};


//Selection Sort

//Insertion Sort
//Bubble Sort