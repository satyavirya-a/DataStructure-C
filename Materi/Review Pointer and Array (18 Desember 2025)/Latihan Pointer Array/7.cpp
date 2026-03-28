#include <stdio.h>


int main() {
	
	int n;
	
	printf("Input the size of the square matrix (less than 5): ");
	scanf("%d", &n);
	
	int matrix[n][n];
	printf("Input elements in the first matrix :\n");
	for (int i =0 ; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("element - [%d],[%d] : ", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}
	
	printf("The First matrix is :\n");
	printf("The matrix is :\n");
	for (int i =0 ; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d", matrix[i][j]);
			if (j < n - 1) printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	
	printf("The sum or rows and coloums of the matrix is :\n");
	for (int i = 0; i < n; i++) {
		int sumRows = 0;
		for (int j = 0; j < n; j++) {
			printf("%d", matrix[i][j]);
			if (j < n - 1) printf(" ");
			sumRows += matrix[i][j];
		}
		printf("\t%d\n", sumRows);
	}
	
	printf("\n");
	int sumCols[n] = {0};
	for (int i = 0; i < n; i++) {
		for (int j =0 ; j < n; j++) {
			for (int k =0; k < n; k++) {
				if (j == k) {
					sumCols[k] += matrix[i][j];
				}
			}
		}
	}
	
	for (int i =0; i < n; i++) {
		printf("%d", sumCols[i]);
		if (i < n - 1) printf(" ");
	}
	printf("\n");
	
	return 0;
}
