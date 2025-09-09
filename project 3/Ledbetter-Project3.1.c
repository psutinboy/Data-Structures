#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *next;
  void *data;
} Node;

typedef struct LinkQueue {
  Node *front;
  Node *back;
} LinkQueue;

/*
// function prototypes
*/
LinkQueue *newQueue();
int isEmpty(LinkQueue *);
void destroyQueue(LinkQueue *);
void enqueue(LinkQueue *, void *);
void *dequeue(LinkQueue *);
void *peek(LinkQueue *);
// end function prototpyes

// initialize stack
LinkQueue *newQueue() {
  LinkQueue *new = malloc(sizeof(LinkQueue));
  if (new != NULL) {
    new->front = NULL; // signifies empty queue;
    new->back = NULL;  // signifies empty queue;
    return new;
  } else {
    printf("Memory allocation for queue failed!");
    return NULL;
  }
}

int isEmpty(LinkQueue *this) { return (this->front == NULL); }

void destroyQueue(LinkQueue *this) {
  while (!isEmpty(this)) {
    dequeue(this);
  }
  free(this);
}

void enqueue(LinkQueue *this, void *x) {
  Node *newNode = malloc(sizeof(Node));

  if (newNode == NULL) {
    printf("Memory allocation failed for a new node!");
    return;
  }
  newNode->data = x;
  newNode->next = NULL;
  if (this->front == NULL) {
    this->front = newNode;
    this->back = newNode;
  } else {
    this->back->next = newNode;
    this->back = newNode;
  }
}

void *dequeue(LinkQueue *this) {
  if (isEmpty(this)) {
    printf("Empty queue, dequeue failed!\n");
    return NULL;
  }

  Node *toRemove = this->front;
  this->front = this->front->next;
  if (this->front == NULL) {
    this->back = NULL;
  }
  void *x = toRemove->data;
  free(toRemove);
  return x;
}

void *peek(LinkQueue *this) {
  if (isEmpty(this)) {
    printf("Empty queue, peek failed!\n");
    return NULL;
  }

  void *x = this->front->data;
  return x;
}

void printIntQueue(LinkQueue *this) {
  Node *iterator = this->front;

  while (iterator != NULL) {
    printf("%d \n", *((int *)iterator->data));
    iterator = iterator->next;
  }
}

int main() {
  // testing
  LinkQueue *myQueue = newQueue();
  int a = 5;
  int b = 7;
  int c = 9;
  int d = 1;
  enqueue(myQueue, &a);
  enqueue(myQueue, &b);
  enqueue(myQueue, &c);
  enqueue(myQueue, &d);
  printIntQueue(myQueue);
  printf("%d \n", *((int *)dequeue(myQueue)));
  printf("%d \n", *((int *)dequeue(myQueue)));
  printf("%d \n", *((int *)dequeue(myQueue)));
  printIntQueue(myQueue);
  printf("%d \n", *((int *)dequeue(myQueue)));
  dequeue(myQueue);
  dequeue(myQueue);
  char x = 'x';
  char y = 'y';
  char z = 'z';
  enqueue(myQueue, &x);
  enqueue(myQueue, &y);
  enqueue(myQueue, &z);
  printf("%c \n", *((char *)dequeue(myQueue)));
  printf("%c \n", *((char *)dequeue(myQueue)));
  printf("%c \n", *((char *)dequeue(myQueue)));
  printf("%p", myQueue->front);
  dequeue(myQueue);
  dequeue(myQueue);
  destroyQueue(myQueue);
  return 0;
}