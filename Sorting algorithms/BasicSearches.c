#include <stdio.h>

#define n 12

int arrU[n] = {83, 47, 12, 67, 95, 23, 76, 34, 59, 88, 41, 67};
int arrO[n] = {12, 23, 34, 41, 47, 59, 67, 67, 76, 83, 88, 95};


// Linear search of unordered data
// returns n  if data not found
int linearU(int data)
{
	int index = 0;

	while (index < n && arrU[index] != data)
		index++;

	return index;
}

// linear search of ordered data
// please note that if data is not found, index is where it should be inserted so as to maintain order of list
int linearO(int data)
{
	int index = 0;

	while (index < n && arrO[index] < data)
		index++;

	return index;
}

// binary search of ordered data

int binarySearch(int data)
{
	int low = 0, high = n - 1;
	int mid;
	int found = 0;

	while (low <= high)
	{

		mid = (low + high) / 2;
		if (arrO[mid] > data)
		{
			high = mid - 1;
		}
		else if (arrO[mid] < data)
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

int binarySearchR(int data, int low, int high)
{
	int mid;
	int found = 0;

	if (low > high)
		return -1;

	mid = (low + high) / 2;
	if (arrO[mid] > data)
	{
		binarySearchR(data, low, mid-1);
	}
	else if (arrO[mid] < data)
	{
		binarySearchR(data, mid+1, high);
	}
	else
	{
		return mid;
	}
}

int main()
{
	int data = 41;
	printf("Data %d is at index %d in unordered data \n", data, linearU(data));
	printf("Data %d is at index %d in ordered data \n", data, linearO(data));
	printf("Data %d is at index %d in ordered data \n", data, binarySearch(data));
	printf("Data %d is at index %d in ordered data \n", data, binarySearchR(data, 0, n-1));
	return 0;
}