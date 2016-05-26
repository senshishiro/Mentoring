// Sorting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sort.h"
#include <vector>


/*
void merge(vector<int> data, int start, int mid,int end)
{
	//create temp array
	//vector<int> leftArr, rightArr, temp;

	//loop through temp array
	//compare elements from two halves
	//add smallest element to temp array
	vector<int> leftArr, rightArr, temp;
	unsigned int left, right;
	left = 0;
	right = 0;
	mid = (end-start) / 2;
	//temp = data;
	cout << "merge\n";

	for (int i = 0; i < mid - start; i++)
	{
		leftArr.push_back(data[start + i]);
	}

	for (int j = 0; j < end - mid; j++)
	{
		rightArr.push_back(data[mid + 1 + j]);
	}

	
	for (int i = start; i < end; i++)
	{
		if (left< leftArr.size() && ( right >= rightArr.size()|| data[left] <= data[right]))
		{
			temp[i] = data[left];
			left++;
		}
		else
		{
			temp[i]= data[right];
			right++;
		}
		//cout << i << endl;
	}

	for (int j = 0; j < temp.size(); j++)
	{
		//data[j] = temp[j];
		cout << j << " : " << temp[j] << endl;
	}
}

void mergeSort(vector<int> data, int start, int end, vector<int> &temp)
{
	//find the midpoint
	
	unsigned int mid = (end + start) / 2;

	//check for base case
	if (end - start < 2)
	{
		cout << "base\n";
		return;
	}
		//int mid = (start + end) / 2;
		//split the two halves
		//populate temp arrays
		cout << "---------------------------\n";
		cout << "start: " << start << endl;
		cout << "mid: " << mid << endl;
		cout << "end: " << end << endl;
		cout << "---------------------------\n";
		//split amd sort the halves	
		cout << "spilt\n";
		mergeSort(data, start, mid, temp);
		mergeSort(data, mid, end,temp);
		
		//merge
		//merge(data, start, mid, end, temp);
		


	//print
}
*/


void merge(int data[])
{
	int start = 0;
	int end = sizeof(data) / sizeof(*data);
	int mid = (end - start) / 2;
	int left = 0;
	int right = 0;
	int counter = 0;
	int temp[end];
	
	for (int i = 0; i < end; i++)
	{

	}

	while (left < mid && right < end)
	{
		if (data[left] <= data[right])
		{
			data[counter] = data[left];
			left++;
		}
		else
		{
			data[counter] = data[right];
			right++;
		}

		counter++;
	}

	while (left < mid)
	{
		data[counter] = data[left];
		left++; 
		counter++;
	}

	while (right < end)
	{
		data[counter] = data[right];
		right++;
		counter++;
	}

	for (int j = 0; j < end; j++)
	{
		//data[j] = temp[j];
		cout << j << " : " << data[j] << endl;
	}
}
int main()
{


	SortData info;
	//vector<int> numbers = { 5, 3, 2, 1, 6, 7, 8, 9, 0, 12 };
	vector<int> numbers = { 5, 3};
	vector<int> bubbleSorted;
	vector<int> selectionSorted;
	vector<int> insertionSorted;
	//info.printList(numbers);

	bubbleSorted = info.bubbleSort(numbers);
	selectionSorted = info.selectionSort(numbers);
	insertionSorted = info.insertionSort(numbers);
	
	//vector<int> sourceArr = { 5,3,6,4};
	//vector<int> temp = sourceArr;

	int sourceArr[] = { 5,3,6,4 };
	int end, start, left, right, mid;

	start = 0;
	end = 4;
	mid = (start + end) / 2;
	merge(sourceArr);
	//mergeSort(sourceArr, start, end, temp);
	cout << "---------------------------\n";
	for (int j = start; j < end; j++)
	{
		cout << j << " : " << sourceArr[j] << endl;
	}
	//info.mergeSort(numbers, 0 , (numbers.size() - 1));
	//info.printList(insertionSorted);

    return 0;
}

