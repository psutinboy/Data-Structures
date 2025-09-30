// Area

#include <stdio.h>

#define n 4
double A[n][n] = {{1, 2, 4, 5}, {3, 5, 2, 1}, {7, 8, 9, 2}, {2, 4, 5, 6}};

// need to add code to make sure pivot is not zero and swap rows if needed

double det() {
  int i, j, k;
  double pivot, kill;
  double result;

  for (i = 0; i < n - 1; i++) {
    // scan forward from row i and kill entries below diagonal
    for (j = i + 1; j < n; j++) {
      // implement row op on row j
      pivot = A[i][i];
      // figure out what to multiply row j by
      kill = A[j][i] / pivot;
      // row op
      for (k = 0; k < n; k++) {
        A[j][k] = A[j][k] - kill * A[i][k];
      }
    }
  }
  // matrix is now upper triangular
  result = 1;
  for (i = 0; i < n; i++) {
    result *= A[i][i];
  }
  return result;
}

int main() {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf("%lf ", A[i][j]);
    }
    printf("\n");
  }
  printf("%lf \n", det());
  return 0;
}
