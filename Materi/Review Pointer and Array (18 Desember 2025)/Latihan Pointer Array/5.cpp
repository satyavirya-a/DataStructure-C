#include <stdio.h>

int main() {
	
	
	int rows;
	int columns;
	
	printf("Input the rows and columns of the matrix : ");
	scanf("%d %d", &rows, &columns);
	
	int num[rows][columns];
	for (int i =0 ; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			printf("element - [%d],[%d] : ", i, j);
			scanf("%d", &num[i][j]);
		}
	}
	
	printf("The matrix is :\n\n");
	for (int i =0 ; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			printf("%d", num[i][j]);
			if (j < columns - 1) printf(" ");
		}
		printf("\n");
	}
	
	return 0;
}
