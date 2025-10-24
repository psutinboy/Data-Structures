#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ArrList
{
	int *arr;        // could also use void pointers here to store generic data
	int N;           // N is the number of elements in the list
	int capacity;   // capacity is how many elements the list could hold
} ArrList;

/************/
// function protoyptes

// memory management
ArrList *newList(int initialCap);
void freeList(ArrList *list);
int expand(ArrList *list);
int shrink(ArrList *list);

//helper boolean functions
int isEmpty(ArrList *list);
int isFull(ArrList *list);
int isValidIndex(ArrList *list, int index);

// list operations
void insertAt(ArrList *list, int index, int data);
int  retrieveAt(ArrList *list, int index);
void replaceAt(ArrList *list, int index, int data);
int removeAt(ArrList *list, int index);
void swap(ArrList *list, int index1, int index2);
void reverse(ArrList *list);

// selection and bubble sort, they return the number of comparisons
int selectionSort(ArrList *list);
int bubbleSort(ArrList *list);

// basic searches
int linearU(ArrList *list, int data);
int linearO(ArrList *list, int data);
int binarySearch(ArrList *list, int data);

// print
void printList(ArrList *list);
/************/

// ADD new sort methods

int mergeComps = 0;
int quickComps = 0;

void qs(ArrList *list, int start, int end)
{
  //base case
  if(start >= end)
  {
    return;
  }

  int pivot = list->arr[start];

  int pos = start; //pos is searching for the final pivot index
  for(int i = start + 1; i <= end; i++)
  {
    quickComps++;
    if(list->arr[i] < pivot)
    {
      pos++;
      swap(list, i, pos);
    }
  }
  swap(list, start, pos);
  
  qs(list, start, pos - 1);
  qs(list, pos + 1, end);

}

int quickSort(ArrList *list)
{
	quickComps = 0;
	qs(list, 0, list->N - 1);
	return quickComps;
}

void ms(ArrList *list, int start, int end, int *aux) // start and end are inclusive bounds
{
  //base case
  if(start >= end)
  {
    return;
  }

  int mid = (start + end) / 2;

  //sort the two sub lists
  ms(list, start, mid, aux);
  ms(list, mid + 1, end, aux);

  int i;

  for(i = start; i <= end; i++)
  {
    aux[i] = list->arr[i];
  }

  int pos = start; //position in original list we are making
  int pos1 = start; //position in first sublist
  int pos2 = mid + 1; //position in second sublist

  while((pos1 <= mid) && (pos2 <= end))
  {
    mergeComps++;
    if(aux[pos1] <= aux[pos2])
    {
      list->arr[pos] = aux[pos1];
      pos1++;
    }
    else
    {
      list->arr[pos] = aux[pos2];
      pos2++;
    }
    pos++;
  }

  //copy rest of list 1 if there are any elements left
  while(pos1 <= mid)
  {
    list->arr[pos] = aux[pos1];
    pos1++;
    pos++;
  }
  
}

int mergeSort(ArrList *list)
{
	mergeComps = 0;
	// create auxillary space
	int *aux = malloc(list->N * sizeof(int));

	ms(list, 0, list->N - 1, aux);
	
	free(aux);
	return mergeComps;
}

int main()
{
	int n, i;
	srand(time(NULL));
	ArrList *myListS = newList(1);
	ArrList *myListB = newList(1);
	ArrList *myListM = newList(1);
	ArrList *myListQ = newList(1);

	printf("Enter an integer n: ");
	scanf("%d", &n);

	int max = 3 * n;

	for (i = 0; i < n; i++)
	{
		int temp = rand() % (max + 1);
		insertAt(myListS, 0, temp);
		insertAt(myListB, 0, temp);
		insertAt(myListM, 0, temp);
		insertAt(myListQ, 0, temp);
	}

	printList(myListS);

	printf("Selection sort comparisons: %d \n", selectionSort(myListS));
	printf("Bubble sort comparisons: %d \n", bubbleSort(myListB));
	printf("Merge sort comparisons: %d \n", mergeSort(myListM));
	printf("Quick sort comparisons: %d \n", quickSort(myListQ));
	
	printList(myListS);

	// check mergeSort and quickSort
	int mergeError = 0;
	int quickError = 0;
	for (i = 0; i < n; i++)
	{
		if (myListS->arr[i] != myListM->arr[i])
		{
			mergeError = 1;
		}
		if (myListS->arr[i] != myListQ->arr[i])
		{
			quickError = 1;
		}
	}
	if (mergeError)
		printf("Error in mergeSort \n");
	if (quickError)
		printf("Error in quickSort \n");

	return 0;
}

ArrList *newList(int initialCap)
{
	if (initialCap <= 0)
	{	printf("Invalid initial capacity \n");
		return NULL;
	}

	ArrList *new = malloc(sizeof(ArrList));
	if (!new)
	{
		printf("Memory allocation for array list failed! \n");
		return NULL;
	}


	new->arr = malloc(initialCap * sizeof(int));
	if (!new->arr)
	{
		printf("Memory allocation for array list failed! \n");
		free(new);
		return NULL;
	}

	new->N = 0;
	new->capacity = initialCap;
	return new;
}


void freeList(ArrList *list)
{
	if (list) // only free if poitner is not null
	{
		free(list->arr);
		free(list);
	}
}

int expand(ArrList *list) // simply doubles capacity
{
	int *newArr = realloc(list->arr, (list->capacity * 2) * sizeof(int));
	if (!newArr)
	{
		return 0; // failed to expand
	}

	list->arr = newArr;
	list->capacity *= 2;
	return 1;
}

int shrink(ArrList *list) // simply havles capacity
{
	if (list->capacity <= 1) // do not shrink if only one element in list
		return 0;

	int *newArr = realloc(list->arr, (list->capacity / 2) * sizeof(int));
	if (!newArr)
	{
		return 0; // failed to shrink
	}

	list->arr = newArr;
	list->capacity /= 2;
	return 1;
}

// technically these need null check
int isEmpty(ArrList *list)
{
	return (list->N == 0);
}

int isFull(ArrList *list)
{
	return (list->N == list->capacity);
}

int isValidIndex(ArrList *list, int index)
{
	return (index >= 0 && index < list->N);
}

void insertAt(ArrList *list, int index, int data)
{
	if (index < 0 || index > list->N)
	{
		printf("Invalid index to insert at. \n");
		return;
	}

	if (list->N == list->capacity)
	{
		if (!expand(list))
		{
			printf("List at capacity and failed to expand. \n");
			return;
		}
	}

	int i;

	for (i = list->N; i > index; i--)
	{
		list->arr[i] = list->arr[i - 1];
	}
	list->N++;
	list->arr[index] = data;
}



int retrieveAt(ArrList *list, int index)
{
	if (!isValidIndex(list, index))
	{
		printf("Error: index out of range \n");
		return -1;
	}

	return list->arr[index];
}

void replaceAt(ArrList *list, int index, int data)
{
	if (!isValidIndex(list, index))
	{
		printf("Error: index out of range \n");
		return;
	}

	list->arr[index] = data;
}

int removeAt(ArrList *list, int index)
{
	if (!isValidIndex(list, index))
	{
		printf("Error: index out of range \n");
		return -1;
	}

	int i;
	int dataRemoved = list->arr[index];
	for (i = index; i < list->N-  1; i++)
	{
		list->arr[i] = list->arr[i + 1];
	}
	list->N--;


	if (list->N > 0 && list->N < list->capacity / 2)
	{
		shrink(list); // ignore failure, not mission critical
	}

	return dataRemoved;
}

void swap(ArrList *list, int index1, int index2)
{
	if (!isValidIndex(list, index1) || !isValidIndex(list, index2)  )
	{
		printf("Error: index out of range \n");
		return;
	}

	int temp;
	temp = list->arr[index1];
	list->arr[index1] = list->arr[index2];
	list->arr[index2] = temp;
}


void reverse(ArrList *list)
{
	int i;
	for (i = 0; i < list-> N / 2; i++)
	{
		swap(list, i, list->N - 1 - i);
	}
}


int selectionSort(ArrList *list)
{
	int i, j, k, temp;
	int comps = 0;

	for(i = 0; i < list->N - 1; i++)
	{
		k = i;                       // k keeps tracks of the index of the minimum value
		for(j = i + 1; j < list->N; j++)  // Scan forward from i + 1 and find the minimum value
		{
			comps++;
			if (list->arr[j] < list->arr[k])
				k = j;                     // If found an index with smaller array value, record it
		}
		if (k > i)                   // Swap the array values in position k and i
		{
			temp = list->arr[k];
			list->arr[k] = list->arr[i];
			list->arr[i] = temp;
		}
	}
	return comps;
}

int bubbleSort(ArrList *list)
{
	int i, swapped, temp;
	int comps = 0;
	swapped = 1;

	while (swapped)
	{
		swapped = 0;
		for (i = 0; i < list->N - 1; i++)
		{
			comps++;
			if (list->arr[i] > list->arr[i + 1])
			{
				swapped = 1;
				temp = list->arr[i];
				list->arr[i] = list->arr[i+1];
				list->arr[i+1] = temp;
			}
		}
	}
	return comps;
}


// Linear search of unordered data
// returns n  if data not found
int linearU(ArrList *list, int data)
{
	int index = 0;

	while (index < list->N && list->arr[index] != data)
		index++;

	return index;
}

// beware data must be sorted first
int linearO(ArrList *list, int data)
{
	int index = 0;

	while (index < list->N && list->arr[index] < data)
		index++;

	return index;
}

// binary search of ordered data

int binarySearch(ArrList *list, int data)
{
	int low = 0, high = list->N - 1;
	int mid;
	int found = 0;

	while (low <= high)
	{

		mid = (low + high) / 2;
		if (list->arr[mid] > data)
		{
			high = mid - 1;
		}
		else if (list->arr[mid] < data)
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

void printList(ArrList *list)
{
	printf("***********\n");
	int i;
	for (i = 0; i < list->N; i++)
	{
		printf("%d \n", list->arr[i]);
	}
	printf("***********\n");
}