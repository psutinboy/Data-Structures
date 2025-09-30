#include <stdio.h>

#define n 4
double A[n][n] = {{0, 2, 4, 5}, {3, 5, 2, 1}, {7, 8, 9, 2}, {2, 4, 5, 6}};

double det() {
  int i, j, k;
  double pivot, kill;
  double result;

  for (i = 0; i < n - 1; i++) {
    // scan forward from row i and kill entries below diagonal
    for (j = i + 1; j < n; j++) {
      // implement row op on row j
      if (A[i][i] == 0) {
        // swap rows i and j if there is a zero in the diagonal
        for (k = 0; k < n; k++) {
          double temp = A[i][k];
          A[i][k] = A[j][k];
          A[j][k] = temp;
        }
      }
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
