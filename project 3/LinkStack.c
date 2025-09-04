// Demonstrates stack abstract data structure with underlying linked structure
// The nodes hold void pointers as data payload - any data can be stored
// Note: user is reponsible for memory management of void pointers!
// Code only handles the memory management of the linked structure


#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
	struct Node *next;
	void *data;
} Node;


typedef struct LinkStack {
	Node *top;
} LinkStack;

/*
// function prototypes
*/
LinkStack *newStack();
int isEmpty(LinkStack *);
void destroyStack(LinkStack *);
void push(LinkStack *, void *);
void *pop(LinkStack *);
void *peek(LinkStack *);
// end function prototpyes

//initialize stack
LinkStack *newStack()
{
	LinkStack *new = malloc(sizeof(LinkStack));
	if (new != NULL)
	{
		new->top = NULL; // signifies empty stack;
		return new;
	}
	else
	{
		printf("Memory allocation for stack failed!");
		return NULL;
	}
}


int isEmpty(LinkStack *this)
{
	return (this->top == NULL);
}

void destroyStack(LinkStack *this)
{
	while(!isEmpty(this))
	{
		pop(this);
	}
	free(this);
}

void push(LinkStack *this, void *x)
{
	Node *newNode = malloc(sizeof(Node));

	if (newNode == NULL)
	{
		printf("Memory allocation failed for a new node!");
		return;
	}
	newNode-> data = x;
	newNode->next = this->top;
	this->top = newNode;
}


void *pop(LinkStack *this)
{
	if(isEmpty(this))
	{
		printf("Empty stack, pop failed!\n");
		return NULL;
	}

	Node *toRemove = this->top;
	this->top = this->top->next;
	void* x = toRemove->data;
	free(toRemove);
	return x;
}


void *peek(LinkStack *this)
{
	if(isEmpty(this))
	{
		printf("Empty stack, pop failed!\n");
		return NULL;
	}

	void *x = this->top->data;
	return x;
}

void printIntStack(LinkStack *this)
{
	Node *iterator = this->top;

	while(iterator != NULL)
	{
		printf("%d \n", *((int*) iterator->data));
		iterator = iterator->next;
	}
}


int main()
{
	//testing
	LinkStack *myStack = newStack();
	int a = 5;
	int b = 7;
	int c = 9;
	int d = 1;
	push(myStack, &a);
	push(myStack, &b);
	push(myStack, &c);
	push(myStack, &d);

	printf("%d \n", *((int*) pop(myStack)));
	printf("%d \n", *((int*) pop(myStack)));
	printf("%d \n", *((int*) pop(myStack)));
	printf("%d \n", *((int*) pop(myStack)));
	pop(myStack);
	pop(myStack);

	char x = 'x';
	char y = 'y';
	char z = 'z';

	push(myStack, &x);
	push(myStack, &y);
	push(myStack, &z);
	printf("%c \n", *((char*) pop(myStack)));
	printf("%c \n", *((char*) pop(myStack)));
	printf("%c \n", *((char*) pop(myStack)));
	pop(myStack);
	pop(myStack);
	return 0;
}