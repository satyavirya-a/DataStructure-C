#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int n;
	int q;
	int idx;
	int pos;
	
	printf("Input the number of elements to be stored in the array : ");
	scanf("%d", &n);
	
	printf("Input %d elements in the array : ", n);
	printf("\n");
	int *num = (int*)malloc(n*sizeof(int));
	for (int i =0 ; i < n; i++) {
		printf("element - %d : ", i);
		scanf("%d", &num[i]);
	}
	
	printf("\nInput the value to be inserted : ");
	scanf("%d", &q);
	printf("Input the Position, where the value to be inserted : ");
	scanf("%d", &pos);
	
	printf("The current list of the array :\n");
	for (int i = 0; i < n; i++) {
		printf("%d", num[i]);
		if (i < n - 1) printf(" ");
	}
	
	n = n + 1;
	idx = pos - 1;
	//kalau dari awal nanti ketimpa, jadi harus dari akhir
	for (int i = n-1; i > idx; i--) {
		num[i]= num[i - 1];
	}
	num[idx] = q;
	
	printf("\n\nAfter Insert the element the new list is :\n");
	for (int i = 0; i < n; i++) {
		printf("%d", num[i]);
		if (i < n - 1) printf(" ");
	}
	
	printf("\n");
	
	
	return 0;
}
