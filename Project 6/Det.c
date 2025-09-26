// Area

#include <stdio.h>

#define n 4
double A[n][n] = {{1, 2, 4, 5}, {3, 5, 2, 1}, {7, 8, 9, 2}, {2, 4, 5, 6}};

double d() {
  double matrix[n][n];
  // Copy matrix to avoid modifying original
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] = A[i][j];
    }
  }

  double det = 1.0;

  // Gaussian elimination
  for (int i = 0; i < n; i++) {
    int pivot = i;
    for (int k = i + 1; k < n; k++) {
      if (matrix[k][i] > matrix[pivot][i]) {
        pivot = k;
      }
    }

    // Swap rows if needed
    if (pivot != i) {
      for (int j = 0; j < n; j++) {
        double temp = matrix[i][j];
        matrix[i][j] = matrix[pivot][j];
        matrix[pivot][j] = temp;
      }
      det = -det; // Row swap to change sign
    }

    det *= matrix[i][i];

    // Make zero below diagonal
    for (int k = i + 1; k < n; k++) {
      double factor = matrix[k][i] / matrix[i][i];
      for (int j = i; j < n; j++) {
        matrix[k][j] -= factor * matrix[i][j];
      }
    }
  }

  return det;
}

double det() { return d(); }

int main() {
  printf("Determinant: %.2f \n", det());
  printf("Time complexity: O(n^3)\n");

  return 0;
}