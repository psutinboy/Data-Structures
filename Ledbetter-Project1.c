

// Dynamic Array Stack (holds doubles)
// 
// RESIZING POLICY:
// - Initial capacity: 8 elements
// - Expansion: When push() is called and stack is at capacity, the array
//   is doubled in size using realloc() before adding the new element
// - Shrinking: Currently no shrinking is implemented (array maintains
//   its maximum reached capacity throughout the stack's lifetime)
// - Memory management: All memory is freed when destroyStack() is called


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
	if (!this) return;
	if (this->top + 1 == this->capacity) {
		if (!grow(this)) {
			printf("Memory allocation failed during push.\n");
			return;
		}
	}
	this->top++;
	this->data[this->top] = value;
}

double pop(ArrStack *this)
{
	if(!this || this->top == -1)
	{
		printf("Empty stack, pop failed!\n");
		return 0.0;
	}

	double value = this->data[this->top];
	this->top--;
	return value;
}

double peek(ArrStack *this)
{
	if(!this || this->top == -1)
	{
		printf("Empty stack, peek failed!\n");
		return 0.0;
	}

	return this->data[this->top];
}

void print(ArrStack *this)
{
	if(!this || this->top == -1)
	{
		printf("Empty stack, nothing to print\n");
		return;
	}

	printf("*****\n");
	for (int i = 0; i <= this->top; i++)
	{
		printf("%lf \n", this->data[i]);
	}
	printf("*****\n");
}

int main()
{
	//testing
ArrStack *myStack = newStack();
push(myStack, 3.4);
push(myStack, 6.7);
push(myStack, 6.7);
print(myStack);
printf("%lf\n", pop(myStack));
printf("%lf\n", pop(myStack));
printf("%lf\n", pop(myStack));
pop(myStack);
pop(myStack);
print(myStack);
push(myStack, 4.7);
push(myStack, 2.45);
push(myStack, 4.654);
peek(myStack);
printf("%lf\n", peek(myStack));
printf("%lf\n", peek(myStack));
printf("%lf\n", pop(myStack));
printf("%lf\n", peek(myStack));
printf("%lf\n", pop(myStack));
printf("%lf\n", peek(myStack));
printf("%lf\n", pop(myStack));
printf("%lf\n", peek(myStack));;
destroyStack(myStack);
}