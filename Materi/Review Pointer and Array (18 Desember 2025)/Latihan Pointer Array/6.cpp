#include <stdio.h>

int main() {
	
	int n;
	
	printf("Input the size of the square matrix (less than 5): ");
	scanf("%d", &n);
	
	int matrix1[n][n];
	int matrix2[n][n];
	printf("Input elements in the first matrix :\n");
	for (int i =0 ; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("element - [%d],[%d] : ", i, j);
			scanf("%d", &matrix1[i][j]);
		}
	}
	printf("Input elements in the second matrix :\n");
	for (int i =0 ; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("element - [%d],[%d] : ", i, j);
			scanf("%d", &matrix2[i][j]);
		}
	}
	
	printf("The First matrix is :\n");
	for (int i =0 ; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d", matrix1[i][j]);
			if (j < n - 1) printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	
	printf("The Second matrix is :\n");
	for (int i =0 ; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d", matrix2[i][j]);
			if (j < n - 1) printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	
	printf("The Addition of two matrix is :\n");
	for (int i =0 ; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d", matrix1[i][j] + matrix2[i][j]);
			if (j < n - 1) printf(" ");
		}
		printf("\n");
	}
	
	return 0;
}
