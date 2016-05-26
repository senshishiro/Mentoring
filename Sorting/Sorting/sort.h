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

	
	void printList(vector<int> data);
	vector<int> bubbleSort(vector<int> data);
	vector<int> selectionSort(vector<int> data);
	vector<int> insertionSort(vector<int> data);
	void mergeSort(vector<int> &data, int start, int end);

private:
	void swap(vector<int> &data, int a, int b);
	//void merge(vector<int> &data, int start, int end, int mid);
};


//Selection Sort

//Insertion Sort
//Bubble Sort