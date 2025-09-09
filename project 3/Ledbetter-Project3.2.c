#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *next;
  void *data;
} Node;

typedef struct LinkQueue {
  Node *head;
  Node *tail;
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
  LinkQueue *q = malloc(sizeof(LinkQueue));
  if (q == NULL) {
    printf("Memory allocation for queue failed!");
    return NULL;
  }

  Node *dummy = malloc(sizeof(Node));
  if (dummy == NULL) {
    printf("Memory allocation for dummy node failed!\n");
    free(q);
    return NULL;
  }

  dummy->next = NULL;
  dummy->data = NULL;

  q->head = dummy;
  q->tail = dummy;
  return q;
}

int isEmpty(LinkQueue *this) { return (this->head->next == NULL); }

void destroyQueue(LinkQueue *this) {
  while (!isEmpty(this)) {
    dequeue(this);
  }
  free(this->head);
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

  this->tail->next = newNode;
  this->tail = newNode;
}

void *dequeue(LinkQueue *this) {
  if (isEmpty(this)) {
    printf("Empty queue, dequeue failed!\n");
    return NULL;
  }

  Node *first = this->head->next;
  this->head->next = first->next;
  if (this->tail == first) {
    this->tail = this->head;
  }
  void *x = first->data;
  free(first);
  return x;
}

void *peek(LinkQueue *this) {
  if (isEmpty(this)) {
    printf("Empty Queue, pop failed!\n");
    return NULL;
  }

  return this->head->next->data;
}

void printIntQueue(LinkQueue *this) {
  Node *iterator = this->head->next;

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
  printf("%p", myQueue);
  dequeue(myQueue);
  dequeue(myQueue);
  destroyQueue(myQueue);
  return 0;
}