

// Demonstrates stack abstract data structure with underlying array 
// Array is fixed size (adjust MAX below)


#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct ArrStack {
	char stack[MAX]; // max stack size is 100;
	int top;
} ArrStack;

//initialize stack
ArrStack *newStack()
{
	ArrStack *new = malloc(sizeof(ArrStack));
	if (new != NULL)
	{
	new->top = -1; //-1 signifies empty stack
		return new;
	}
	else
	{
	    printf("Memory allocation for stack failed!");
	    return NULL;
	}
}

//destroy stack - free memory
void destroyStack(ArrStack *this)
{
	free(this);
}

int isEmpty(ArrStack *this)
{
	return (this->top == -1);
}

int isFull(ArrStack *this)
{
	return (this->top == (MAX - 1));
}


void push(ArrStack *this, char data)
{
	if(isFull(this))
	{
		printf("Stack full, push failed!");
		return;
	}

	this->top++;
	this->stack[this->top] = data;
}

char pop(ArrStack *this)
{
	if(isEmpty(this))
	{
		printf("Empty stack, pop failed!\n");
		return '\0';
	}

	char data = this->stack[this->top];
	this->top--;
	return data;
}

char peek(ArrStack *this)
{
	if(this->top == -1)
	{
		printf("Empty stack, peek failed!\n");
		return '\0';
	}

	char data = this->stack[this->top];
	return data;
}

void print(ArrStack *this)
{
	if(this->top == -1)
	{
		printf("Empty stack, nothing to print\n");
		return;
	}

	printf("*****\n");
	for (int i = 0; i <= this->top; i++)
	{
		printf("%c \n", this->stack[i]);
	}
	printf("*****\n");
}

int main()
{
	//testing
	ArrStack *myStack = newStack();

	push(myStack, 'a');
	push(myStack, 'b');
	push(myStack, 'c');
	printf("%d\n", myStack->top);
	print(myStack);
	printf("%c\n", pop(myStack));
	printf("%c\n", pop(myStack));
	printf("%c\n", pop(myStack));
	pop(myStack);
	pop(myStack);
	print(myStack);
	push(myStack, 'x');
	push(myStack, 'y');
	push(myStack, 'z');
	peek(myStack);
	printf("%c\n", peek(myStack));
	printf("%c\n", peek(myStack));
	printf("%c\n", pop(myStack));
	printf("%c\n", peek(myStack));
	printf("%c\n", pop(myStack));
	printf("%c\n", peek(myStack));
	printf("%c\n", pop(myStack));
	printf("%c\n", peek(myStack));;
	destroyStack(myStack);
	return 0;
}