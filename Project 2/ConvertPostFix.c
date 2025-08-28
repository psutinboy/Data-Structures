
// The purpose of this code is to convert an infix expression from user input to
// a postfix expression Supported arithmetic operations: +,-,*,/,^

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// stack function prototypes (see end of file)
// we need a stack of chars, not doubles as in the previous example
typedef struct ArrStack {
  char *stack;
  int top;
  int initialCap;
  int capacity;
} ArrStack;

ArrStack *newStack();
void destroyStack(ArrStack *this);
int isEmpty(ArrStack *this);
int isFull(ArrStack *this);
int expand(ArrStack *this);
int shrink(ArrStack *this);
void push(ArrStack *this, char data);
char pop(ArrStack *this);
char peek(ArrStack *this);
// end stack function prototypes

// prototype for main application
void getUserInput();
void convertToPostfix();
int isLetter(char);

// for simplicity, I made infix string, postfix string, and length of infix all
// global variables
char infix[100];   // 100 is an arbitrary limit. Infix expression is limited to
                   // 100 characters. In practice, not a serious concern.
int length;        // this is length of INFIX
char postfix[100]; // postfix will alwas be shorter than infix since parentheses
                   // are dropped. Surely 100 is large enough.

int main() {
  getUserInput();
  convertToPostfix();
  printf("The equivalent postfix expression is: %s", postfix);
  return 0;
}

void convertToPostfix() {
  // Missing code
}

int isLetter(char ch) // tells you if a character is a letter (varible) or not.
{
  if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
    return 1;
  } else {
    return 0;
  }
}

void getUserInput() {
  printf("Supported operations: +,*,-,/,^ \n");
  printf("Enter an infix expression:\n");
  fgets(infix, sizeof(infix), stdin); // Read string with spaces

  // Remove trailing newline character from fgets if present
  infix[strcspn(infix, "\n")] = '\0';

  length = strlen(infix); // Calculate length

  printf("You entered: \"%s\"\n", infix);
  printf("Length of the string: %d\n", length);
}

// initialize stack
ArrStack *newStack() {

  ArrStack *new = malloc(sizeof(ArrStack));
  new->initialCap = 8;
  new->capacity = new->initialCap;
  new->stack = malloc(new->initialCap * sizeof(char));

  if (new != NULL && new->stack != NULL) {
    new->top = -1; //-1 signifies empty stack
    return new;
  } else {
    printf("Memory allocation for stack failed!");
    return NULL;
  }
}

// destroy stack - free memory
void destroyStack(ArrStack *this) {
  free(this->stack);
  free(this);
}

int isEmpty(ArrStack *this) { return (this->top == -1); }

int isFull(ArrStack *this) { return (this->top == (this->capacity - 1)); }

// expand stack
int expand(ArrStack *this) {
  // double stack size
  char *newArr = realloc(this->stack, (this->capacity * 2) * sizeof(char));

  if (newArr != NULL) {
    this->stack = newArr;
    this->capacity *= 2;
    printf("expanded %d \n", this->capacity);
    return 0; // expand succesful

  } else {
    printf("Stack expand fail");
    return -1; // stack expansion fail
  }
}

int shrink(ArrStack *this) {
  // halve stack size
  char *newArr = realloc(this->stack, (this->capacity / 2) * sizeof(char));

  if (newArr != NULL) {
    this->stack = newArr;
    this->capacity /= 2;
    printf("shrunk %d \n", this->capacity);
    return 0; // expand succesful
  } else {
    printf("Stack shrink fail");
    return -1; // stack shrink fail
  }
}

void push(ArrStack *this, char data) {

  if (isFull(this)) {
    if (expand(this) == -1) {
      return;
    }
  }

  this->top++;
  this->stack[this->top] = data;
}

char pop(ArrStack *this) {
  if (isEmpty(this)) {
    printf("Empty stack, pop failed!\n");
    return '\0';
  }

  if ((this->top < (this->capacity / 2) &&
       (this->capacity / 2) >= this->initialCap)) {
    if (shrink(this) == -1) {
      return '\0';
    }
  }

  char data = this->stack[this->top];
  this->top--;
  return data;
}

char peek(ArrStack *this) {
  if (this->top == -1) {
    printf("Empty stack, peek failed!\n");
    return '\0';
  }

  char data = this->stack[this->top];
  return data;
}
