
#include <stdio.h>
#include <stdlib.h>
// the purpose of this code sample is to demonstrate the linked list structure...
// for code simplicity, I have not placed the malloc statements in try-catch blocks
// best practice for production code would be to include the malloc statements in try-catch blocks.

typedef struct ListNode ListNode;
typedef struct LinkedList LinkedList;

typedef struct ListNode
{
	int data;         //could use void pointer here to handle generic data
	ListNode* prev;
	ListNode* next;
} ListNode;

typedef struct LinkedList
{
	int N;
	ListNode* start;
	ListNode* end;
	// start and end never change.
	// They are dummy nodes.
} LinkedList;

/************/
// function protoyptes
//constructors
ListNode* initNode(int dataValue);
LinkedList* newList();
void freeList(LinkedList *list);
//helper boolean functions
int isEmpty(LinkedList *list);
int isValidIndex(LinkedList *list, int index);
// list operations
ListNode *getNode(LinkedList *list, int index);
void insertAt(LinkedList *list, int index, int data);
int  retrieveAt(LinkedList *list, int index);
void replaceAt(LinkedList *list, int index, int data);
int removeAt(LinkedList *list, int index);
void reverse(LinkedList *list);

// sort
void selectionSort(LinkedList *list);
void ms(LinkedList *list, int start, int end);
void mergeSort(LinkedList *list);
void move(ListNode *nodeToMove, ListNode *newLocation);

//print
void printList(LinkedList *list);

// constructors
ListNode* initNode(int dataValue)
{
	ListNode* node = malloc(sizeof(ListNode));
	node->data = dataValue;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

LinkedList* newList()
{
	LinkedList* list = malloc(sizeof(LinkedList));
	list->N = 0;
	list->start = initNode(0);
	list->end = initNode(0);
	list->start->next = list->end;
	list->end->prev = list->start;
	return list;
}

void freeList(LinkedList *list)
{
	while (!isEmpty)
		removeAt(list, 0);
	free(list->start);
	free(list->end);
	free(list);
}

// boolean helpers
int isEmpty(LinkedList *list)
{
	return (list->N == 0);
}

int isValidIndex(LinkedList *list, int index)
{
	return (index >= 0 && index < list->N);
}

// calling getNode with index -1 gives the start dummy node
// also index N gives end dummy ndoe
ListNode *getNode(LinkedList *list, int index) // O(n)
{
	if (index < -1 || index > list->N)
		return NULL;

	//missing code
	ListNode *node = list->start;
	for(int i = -1; i < index; i++)
	{
		node = node->next;
	}
	return node;
}

// list operations
void insertAt(LinkedList *list, int index, int data) //O(n)
{
	if (index < 0 || index > list->N)
	{
		printf("Invalid index to insert at. \n");
		return;
	}

	// missing code
	ListNode *node = initNode(data);

	ListNode *prevNode = getNode(list, index - 1);

	node->next = prevNode->next;
	node->prev = prevNode;

	prevNode->next = node;
	node->next->prev = node;

	list->N++;
}


int retrieveAt(LinkedList *list, int index) //O(n)
{
	if (!isValidIndex(list, index))
	{
		printf("Error: index out of range \n");
		return -1;
	}

	return getNode(list, index)->data;
}

void replaceAt(LinkedList *list, int index, int dataValue) //O(n)
{
	if (!isValidIndex(list, index))
	{
		printf("Error: index out of range \n");
	}

	getNode(list, index)->data = dataValue;
}

int removeAt(LinkedList *list, int index) //O(n)
{
	if (!isValidIndex(list, index))
	{
		printf("Error: index out of range \n");
		return -1;
	}

	ListNode *priorNode = getNode(list, index - 1);
	int result = priorNode->next->data;
	
	priorNode->next = priorNode->next->next;
	free(priorNode->next->prev);
	priorNode->next->prev = priorNode;

	list->N--;

	return result;
}

void reverse(LinkedList *list)
{
	// missing code
	ListNode *iterator = list->start;

	ListNode *temp;
	for(int i = -1; i <= list->N; i++)
	{
		iterator = iterator->next;
		temp = iterator->next;
		iterator->next = iterator->prev;

		iterator->prev = temp;
	}
	temp = list->start;
	list->start = list->end;
	list->end = temp;
}



// what's wrong with the code below?
void selectionSort(LinkedList *list) //O(n^2)
{
	int i, j, k, temp;

	ListNode *iNode, *jNode, *kNode;

	iNode = list->start->next;
	for(i = 0; i < list->N - 1; i++) //O(n)
	{
		k = i;                       // k keeps tracks of the index of the minimum value
		kNode = iNode;

		jNode = iNode->next;
		for(j = i + 1; j < list->N; j++)  // Scan forward from i + 1 and find the minimum value          O(n)
		{
			if (jNode->data < kNode->data) //O(1)
			{
				k = j;                     // If found an index with smaller array value, record it
				kNode = jNode;
			}
			jNode = jNode->next;
		}
		if (k > i)                   // Swap the array values in position k and i
		{
			temp = kNode->data;
			kNode->data = iNode->data;
			iNode->data = temp;
		}
		iNode = iNode->next;
	}
}


void move(ListNode *nodeToMove, ListNode *newLocation)
{
	// missing code
	// skips nodeToMove
	nodeToMove->prev->next = nodeToMove->next;
	nodeToMove->next->prev = nodeToMove->prev;

	newLocation->prev = nodeToMove->prev;
	nodeToMove->next = newLocation;

	nodeToMove->prev->next = nodeToMove;
	newLocation->prev = nodeToMove;
}

// has ms return a reference tot he beginning of the sorted list
//void ms(LinkedList *list, int start, int end)
ListNode *ms(LinkedList *list, int start, int end)
{
	if (start >= end)
		return;
	// missing code
	int mid = (start + end) / 2;

	ListNode *start1 = ms(list, start, mid);
	ListNode *start2 = ms(list, mid + 1, end);

	//ms(list, start, mid);
	//ms(list, mid + 1, end);

	// Merge step
	int size1 = mid - start - 1;
	int size2 = end - mid;

	ListNode *node1 = getNode(list, start);
	ListNode *node2 = getNode(list, mid + 1);

	while(size1 >= 1 && size2 > 1)
	{
		if(node1->data > node2->data)
		{
			node2 = node2->next; // advance node2
			move(node2->prev, node1);
			size2--;
		}
		else
		{
			node1 = node1->next; // advance node1
			size1--;
		}
	}
	//return reference
	return start1;
}


void mergeSort(LinkedList *list)
{
	ms(list, 0, list->N-1);
}



void printList(LinkedList *list)
{
	printf("***********\n");
	ListNode *iterator = list->start;

	for (int i = 0; i < list->N; i++)
	{
		iterator = iterator->next;
		printf("%d \n", iterator->data);
	}
	printf("***********\n");
}


int main()
{
	LinkedList *my = newList();
	insertAt(my, 0, 1);
	insertAt(my, 0, 2);
	insertAt(my, 0, 3);
	insertAt(my, 0, 4);
	insertAt(my, 0, 5);
	//insertAt(my, 1, 5);
	printList(my);

	move(getNode(my, 0), getNode(my, 3));
	printList(my);

	/*
	insertAt(my, my->N, 6);
	printList(my);
	insertAt(my, 4, 7);
	printList(my);
	removeAt(my, 3);
	
	
	printf("%d\n", retrieveAt(my, 0));
	printf("%d\n", retrieveAt(my, -1));
	printf("%d\n", retrieveAt(my, my->N));
	printf("%d\n", retrieveAt(my, my->N - 1));
	printf("%d\n", retrieveAt(my, 4));
	replaceAt(my, 4, 1000);
	printList(my);
	removeAt(my, 0);
	removeAt(my, 3);
	printList(my);
	mergeSort(my);
	printList(my);
	freeList(my);
*/
	return 0;
}