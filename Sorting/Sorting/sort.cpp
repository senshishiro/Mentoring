
#include "stdafx.h"
#include "sort.h"

//===================================================================
// Swap
void SortData::swap(vector<int> &data, int a, int b)
{
	int temp;

	temp = data[a];
	data[a] = data[b];
	data[b] = temp;
}

//===================================================================
// Print List
void SortData::printList(vector<int> data)
{
	int size = data.size();

	for (int i = 0; i < size; i++)
	{
		cout << data[i];

		if (i == size - 1)
		{
			cout << endl;
		}
		else
		{
			cout << ", ";
		}
	}
}

//===================================================================
// Bubble Sort
vector<int> SortData::bubbleSort(vector<int> data)
{
	bool sorted = true;
	int size = data.size();
	int count = 0;

	do
	{		
		sorted = true;
		count++;

		for (int i = 0; i < size - count; i++)
		{
			if (data[i] > data[i + 1])
			{
				swap(data, i, i + 1);
				sorted = false;
			}
		}
	} while (!sorted);	

	return data;
}

//===================================================================
// Selection Sort
vector<int> SortData::selectionSort(vector<int> data)
{
	int size = data.size()-1;

	for (int i = 0; i < size; i++)
	{
		int minPos = i;
		
		for (int j = i + 1; j < size; j++)
		{
			if (data[minPos] > data[j])
			{
				minPos = j;
				//cout << "new min: "<< data[minPos] << endl;
			}
		}
		//if the numbers are the same don't swap	
		if (data[minPos] != data[i])
		{
			swap(data, i, minPos);
			//printList(data);
		}	
	}
		return data;
}

//===================================================================
// Insertion Sort
vector<int> SortData::insertionSort(vector<int> data)
{
	int size = data.size() - 1;

	//starts checking from the second element
	for (int i = 1; i < size; i++)
	{
		//int key = data[i];

		//cout << "keys: " << i << endl;
		for (int j = i; j > 0; j--)
		{
			if (data[j-1] > data[j])
			{
				//cout << "keys: " << j-1 << " " << j << endl;
				//cout << data[j-1] << " " << data[j] << endl;
				swap(data, j-1, j);
				//printList(data);
			}
		}
	}

	return data;
}

//===================================================================
// Merge Sort

void SortData::mergeSort(vector<int> &data, int start, int end)
{
	//find the midpoint

	
	//check for base case
	if (start < end)
	{
		int mid = (start + end) / 2;
		//split the two halves
		//populate temp arrays

		//split amd sort the halves	
		mergeSort(data, start, mid);
		mergeSort(data, mid + 1, end);

		//merge
		merge(data, start, end, mid);
	}



	//print
	printList(data);
}

void SortData::merge(vector<int> &data, int start, int end, int mid)
{
	//create temp array
	vector<int> leftArr, rightArr, temp;
	cout << "check\n";
	for (int i = 0; i < mid-start+1; i++)
	{
		leftArr.push_back( data[start + i]);
	}

	for (int j = 0; j < end-mid; j++)
	{
		rightArr.push_back(data[mid + 1 + j]);
	}
	//loop through temp array
	//compare elements from two halves
	//add smallest element to temp array

	//counter for left half
	int x = 0;
	//counter for right half
	int y = 0;
	//counter for temp array
	int z = 0;

	int left = start;
	int right = mid;

/*
	for (int i = 0; i < end-start; i++)
	{
		if (left < mid && (right >= end || leftArr[left] <= rightArr[right]))
		{
			temp.push_back(leftArr[left]);
			left++;
		}
		else
		{
			temp.push_back(rightArr[right]);
			right++;
		}
		cout << i << endl;
	}
	*/

	while (x < mid && y < end)
	{
		cout << "check - inner loop\n";
		if (leftArr[x] <= rightArr[y])
		{
			//add
			temp.push_back(leftArr[x]);
			x++;
		}
		else
		{
			temp.push_back(rightArr[y]);
			y++;
		}
	}

	if (y > mid+1)
	{

	}

	if (temp.size() > 0)
	{
		for (int i = start; i < end; i++)
		{
			data[i] = temp[i];
		}
	}

}