// 1. Write a program to print the address of a variable.
#include <stdio.h>

int main() {
  int a = 5;
  int *p = &a;
  printf("%p\n", p);
  return 0;
}