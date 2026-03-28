#include <stdio.h>

int main() {
	
	int n;
	
	printf("Input the number of elements to be stored in the array : ");
	scanf("%d", &n);
	
	printf("Input %d elements in the array : ", n);
	printf("\n");
	int num[n];
	for (int i =0 ; i < n; i++) {
		printf("element - %d : ", i);
		scanf("%d", &num[i]);
	}
	
	printf("The Even elements are :\n");
	for (int i =0 ; i < n; i++) {
		if (num[i] % 2 == 0) {
			printf("%d", num[i]);
			if (i < n - 1) printf(" ");
		}
	}
	printf("\n\n");
	printf("The Odd elements are :\n");
	for (int i =0 ; i < n; i++) {
		if (num[i] % 2 == 1) {
			printf("%d", num[i]);
			if (i < n - 1) printf(" ");
		}
	}
	
	return 0;
}
