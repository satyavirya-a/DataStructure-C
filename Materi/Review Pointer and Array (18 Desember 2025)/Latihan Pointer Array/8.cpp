#include <stdio.h>

int main() {
	
	
	int n;
	
	printf("Input the size of array : ");
	scanf("%d", &n);
	
	int num[n];
	int sum = 0;
	printf("Input %d elements in the array :\n");
	for (int i =0 ; i < n; i++) {
		printf("element - %d : ", i);
		scanf("%d", &num[i]);
		sum += num[i];
	}
	
	printf("The given array is : ");
	for (int i =0 ; i < n; i++) {
		printf("%d", num[i]);
		if (i < n - 1) printf(" ");
	}
	
	int proyeksi = (n+1)*(n+2)/2;
	printf("\nThe missing number is : %d\n", proyeksi - sum );
	
	return 0;
}
