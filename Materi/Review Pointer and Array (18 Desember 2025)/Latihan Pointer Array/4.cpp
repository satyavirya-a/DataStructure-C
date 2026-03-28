#include <stdio.h>
#include <stdlib.h>


int main() {
	
	int n;
	
	printf("Input the size of array : ");
	scanf("%d", &n);
	
	printf("Input %d elements in the array : ", n);
	printf("\n");
	int *num = (int*)malloc(n*sizeof(int));
	for (int i =0 ; i < n; i++) {
		printf("element - %d : ", i);
		scanf("%d", &num[i]);
	}
	
	int max = 0;
	int second_max = 0;
	
	for (int i =0 ; i < n; i++) {
		if (num[i] > max) {
			max = num[i];
		}
		if (num[i] < max && num[i] > second_max) {
			second_max = num[i];
		}
	}
	
	printf("The Second Largest element in the array is : %d\n", second_max );
	
	
	
	return 0;
}
