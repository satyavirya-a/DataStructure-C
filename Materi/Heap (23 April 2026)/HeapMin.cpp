// INI MIN HEAP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEAP_SIZE 100

typedef struct MinHeap {
	int size;
	int* elements;
}MinHeap;

MinHeap* create(int capacity) {
	MinHeap* h = (MinHeap*)malloc(sizeof(MinHeap));
	h->size = 0;
	h->elements = (int*)malloc(capacity * sizeof(int));
	
	return h;
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void insert(MinHeap* minHeap, int key) {
	if (minHeap->size == MAX_HEAP_SIZE) {
		printf("heap overflow\n")
		return;
	}
	
	int i = minHeap->size++; //kalau dia ++ size itu index 0 nya kosong, kalau size++, index 0 nya nilai min nya
	minHeap->elements[i] = key; //ini insert nya di index terakhir + 1
	
	//i bukan root	//kalau parent lebih besar dari element yang baru dimasukin
	while (i != 0 && minHeap->elements[(i - 1)/2] > minHeap->elements[i]) {
		swap(&minHeap->elements[i], &minHeap->elements[(i - 1)/2]);
		
		i = (i - 1)/2; //pindah ke parent di iterasi while nya
	}
}


int findMin(MinHeap* minHeap) {
	if (minHeap->size == 0) {
		printf("Heap is empty");
		return -1; // bisa juga pakai MAX_INT
	}
	return minHeap->elements[0];
}

int findMax(MinHeap* minHeap) {
	if (minHeap->size == 0) {
		printf("Heap is empty")
		return -1; // bisa juga pakai MIN_INT
	}
	
	int max = minHeap->elements[0];
	for (i = 1; i < minHeap->size; i++) {
		if (minHeap->elements[i] > max) {
			max = minHeap->elements[i];
		}
	}
	
	return max;
}

void heapify(MinHeap* minHeap, int idx) {
	int smallest = idx;
	int left = 2* idx + 1;
	int right = 2* idx + 2;
	
	if (left < minHeap->size && minHeap->elements[left] < minHeap->elements[smallest]) {
		smallest = left;
	}
	
	if (right < minHeap->size && minHeap->elements[right] < minHeap->elements[smallest]) {
		smallest = right;
	}
	
	if (smallest != idx) {
		swap(&inHeap->elements[smallest], &minHeap->elements[idx]);
		heapify(minHeap, smallest);
	}
}

void deleteMin(MinHeap* minHeap, int key) {
	if (minHeap->size == 0) {
		return;
	}
	
	if (minHeap->size== 1) {
		minHeap->size--;
	}
	
	minHeap->elements[0] = minHeap->elements[minHeap->size - 1];	
	minHeap->size--;
	heapify(minHeap, 0);
	
}

