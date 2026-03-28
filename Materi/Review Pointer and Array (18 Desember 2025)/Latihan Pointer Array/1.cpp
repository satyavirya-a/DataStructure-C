#include <stdio.h>

int main() {
	
	
	int n;
	
	printf("Input the number of elements to be stored in the array : ");
	scanf("%d", &n);
	
	printf("Input %d elements in the array : ", n);
	int num[n];
	printf("\n");
	for (int i =0 ; i < n; i++) {
		printf("element - %d : ", i);
		scanf("%d", &num[i]);
	}
	
	printf("The values store into array are :\n");
	for (int i = 0; i < n; i++) {
		printf("%d", num[i]);
		if (i < n -1) printf(" ");
	}
	
	printf("\n\n");
	printf("The values store into the array in reverse are :\n");
	for (int i = 0; i < n; i++) {
		printf("%d", num[n - 1 - i]);
		if (i < n-1) printf(" ");
	}
	
	printf("\n");
	return 0;
}
