

// Dynamic Array Stack (holds doubles)
// Resizing policy: start capacity=8; on push if full -> double with realloc


#include <stdio.h>
#include <stdlib.h>

typedef struct ArrStack {
	double *data;
	int top;
	int capacity;
} ArrStack;

//initialize stack
ArrStack *newStack()
{
	ArrStack *s = malloc(sizeof(ArrStack));
	if (s == NULL) return NULL;
	s-> capacity = 8;
	s-> top = -1;
	s-> data = malloc(sizeof(double) * s->capacity);
	
	if(s->data == NULL) {
	    free(s);
	    return NULL;
	}
	return s;
}

//destroy stack - free memory
void destroyStack(ArrStack *this)
{
	if(!this) return;
	free(this->data);
	free(this);
}

int isEmpty(ArrStack *this)
{
	return (this->top == -1);
}

static int grow(ArrStack *this) {
    int newCap = (this->capacity == 0) ? 8 : this->capacity * 2;
    double *p = realloc(this->data, newCap * sizeof(double));
    if (!p) {
        printf("Memory allocation failed during grow.\n");
        return 0;
    }
    this->data = p;
    this->capacity = newCap;
    return 1;
}

void push(ArrStack *this, double value)
{
	this->top++;
	this->stack[this->top] = data;
}

double pop(ArrStack *this)
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

double peek(ArrStack *this)
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