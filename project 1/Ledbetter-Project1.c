
// Dynamic Array Stack (holds doubles)
// Resizing policy: start capacity=8; on push if full -> double capacity with
// realloc The array is expanded when push() is called and the stack is at full
// capacity. The capacity is doubled each time using realloc() to maintain
// amortized O(1) push operations. No shrinking is implemented - the array
// maintains its maximum size reached.

#include <stdio.h>
#include <stdlib.h>

typedef struct ArrStack {
  double *data;
  int top;
  int capacity;
} ArrStack;

// initialize stack
ArrStack *newStack() {
  ArrStack *s = malloc(sizeof(ArrStack));
  if (s == NULL)
    return NULL;
  s->capacity = 8;
  s->top = -1;
  s->data = malloc(sizeof(double) * s->capacity);

  if (s->data == NULL) {
    free(s);
    return NULL;
  }
  return s;
}

// destroy stack - free memory
void destroyStack(ArrStack *this) {
  if (!this)
    return;
  free(this->data);
  free(this);
}

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
  if (this->top + 1 >= this->capacity) {
    if (!grow(this)) {
      printf("Push failed: could not expand stack\n");
      return;
    }
  }
  this->top++;
  this->data[this->top] = value;
}

double pop(ArrStack *this) {
  if (isEmpty(this)) {
    printf("Empty stack, pop failed!\n");
    return 0.0;
  }

  double data = this->data[this->top];
  this->top--;
  return data;
}

double peek(ArrStack *this) {
  if (this->top == -1) {
    printf("Empty stack, peek failed!\n");
    return 0.0;
  }

  double data = this->data[this->top];
  return data;
}

void print(ArrStack *this) {
  if (this->top == -1) {
    printf("Empty stack, nothing to print\n");
    return;
  }

  printf("*****\n");
  for (int i = 0; i <= this->top; i++) {
    printf("%f \n", this->data[i]);
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
  destroyStack(myStack);
  return 0;
}