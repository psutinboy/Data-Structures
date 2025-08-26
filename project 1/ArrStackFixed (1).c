

// Dynamic Array Stack (holds doubles)
// Resizing policy: start capacity=8; on push if full -> double with realloc

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct ArrStack {
  char stack[MAX]; // max stack size is 100;
  int top;
} ArrStack;

// initialize stack
ArrStack *newStack() {
  ArrStack *new = malloc(sizeof(ArrStack));
  if (new != NULL) {
    new->top = -1; //-1 signifies empty stack
    return new;
  } else {
    printf("Memory allocation for stack failed!");
    return NULL;
  }
}

// destroy stack - free memory
void destroyStack(ArrStack *this) { free(this); }

int isEmpty(ArrStack *this) { return (this->top == -1); }

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

void push(ArrStack *this, double value) {
  this->top++;
  this->data[this->top] = value;
}

char pop(ArrStack *this) {
  if (!this || this->top == -1) {
    printf("Empty stack, pop failed!\n");
    return 0.0;
  }

  double value = this->data[this->top];
  this->top--;
  return value;
}

char peek(ArrStack *this) {
  if (!this || this->top == -1) {
    printf("Empty stack, peek failed!\n");
    return 0.0;
  }

  return this->data[this->top];
}

void print(ArrStack *this) {
  if (!this || this->top == -1) {
    printf("Empty stack, nothing to print\n");
    return;
  }

  printf("*****\n");
  for (int i = 0; i <= this->top; i++) {
    printf("%lf \n", this->data[i]);
  }
  printf("*****\n");
}

int main() {
  // testing
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
  printf("%lf\n", peek(myStack));
  ;
  destroyStack(myStack);
}