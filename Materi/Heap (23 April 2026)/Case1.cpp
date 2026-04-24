#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HEAP_SIZE 100 

typedef struct Data {
	char name[100];
	int poligon;
}Data;

typedef struct MaxHeap {
	int size;
	Data* elements;
}MaxHeap;

MaxHeap* create(int capacity) {
	MaxHeap* h = (MaxHeap*)malloc(sizeof(MaxHeap));
	h->size = 0;
	h->elements = (Data*)malloc(capacity*sizeof(Data));
	
	return h;
}

void swap(Data *a, Data *b ) {
	Data temp = *a;
	*a = *b;
	*b = temp;
}



void insert(MaxHeap* heap, Data source) {
	if(heap->size > MAX_HEAP_SIZE) {
		printf("Heap overflow\n");
		return;
	}
	
	int i = heap->size++; //jadi kalau i nya dipanggil, size sekarang dipake trus di increment
	heap->elements[i] = source;
	
	while (i != 0 && heap->elements[i].poligon > heap->elements[(i-1)/2].poligon) {
		swap(&heap->elements[i], &heap->elements[(i-1)/2]);
		
		i = (i - 1)/2;
	}
}

void heapify(MaxHeap* heap, int idx) {
	//definisiin dulu variabel nya
	int smallestIdx = idx;
	int leftChildIdx = idx*2 + 1;
	int rightChildIdx = idx*2 + 2;
	
	if (leftChildIdx < heap->size && heap->elements[leftChildIdx].poligon > heap->elements[smallestIdx].poligon) {
		smallestIdx = leftChildIdx;
	}
	
	if (rightChildIdx < heap->size && heap->elements[rightChildIdx].poligon > heap->elements[smallestIdx].poligon) {
		smallestIdx = rightChildIdx;
	}
	
	if (smallestIdx != idx) {
		swap(&heap->elements[idx], &heap->elements[smallestIdx]);
		heapify(heap, smallestIdx);
	}
}

Data deleteMax(MaxHeap* heap) {
	Data b = {0};
	if (heap->size == 0) {
		printf("Tidak ada yang bisa di delete\n");
		return b;
	}
	
	else if (heap->size == 1) {
		Data temp = heap->elements[0];
		heap->size--;
		return temp;
	}
	
	Data temp = heap->elements[0];
	heap->elements[0] = heap->elements[heap->size-1];
	heap->size--;
	heapify(heap, 0);
	return temp;
	
}

void display(MaxHeap* heap) {
	for (int i = 0; i < heap->size; i++) {
		printf("%s", heap->elements[i].name);
		if (i < heap->size - 1) printf(" ");
	}
	printf("\n");
}

int main() {
	
	int n, q;
	
	scanf("%d", &n);
	
	char line[100];
	
	scanf("%s", line);
	scanf("%d", &q);
	
	char name[100];
	int key;
	char* data = strtok(line, ",");
	int i = 0;
	
	MaxHeap* heap = create(MAX_HEAP_SIZE);
	while (data != NULL && i < n) {
//		printf("%s\n", data);
		Data temp;
		sscanf(data,"%[^-]-%d", temp.name, &temp.poligon);
		printf("%s %d\n", temp.name, temp.poligon);
		insert(heap, temp);
		i++;
		data = strtok(NULL, ",");
	}
	
	printf("[INIT QUEUE] ");
	display(heap);
	
	for (int i = 0; i < q; i++) {
		Data temp = deleteMax(heap);
		printf("[RENDERED] %s with %d polygons.\n", temp.name, temp.poligon);
	}
	
	printf("[REMAINING] ");
	display(heap);
	
	return 0;
}
