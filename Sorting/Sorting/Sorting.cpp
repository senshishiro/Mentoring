// Sorting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sort.h"
#include <vector>

int main()
{


	SortData info;
	//vector<int> numbers = { 5, 3, 2, 1, 6, 7, 8, 9, 0, 12 };
	vector<int> numbers = { 5, 3};
	vector<int> bubbleSorted;
	vector<int> selectionSorted;
	vector<int> insertionSorted;
	info.printList(numbers);

	bubbleSorted = info.bubbleSort(numbers);
	selectionSorted = info.selectionSort(numbers);
	insertionSorted = info.insertionSort(numbers);
	
	info.mergeSort(numbers, 0 , (numbers.size() - 1));
	//info.printList(insertionSorted);

    return 0;
}

