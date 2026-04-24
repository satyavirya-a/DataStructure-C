#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_HEAP_SIZE 100

typedef struct MinMaxHeap {
    int size;
    int *elements;
} MinMaxHeap;


//even level itu min
//

//upheap
//void bubbleUp(MinMaxHeap* heap, int idx) {
	//ini fungsi untuk rekursi ke atas
	
//	if (idx == 0) return;
	
	//level min
//	if (isEvenLevel(idx)) {
//		if (heap->elements[idx] > heap->elements[parent(idx)]) {
//			swap(&heap->elements[])
//		}
//	}
	
	
	//level max
	
//}

//int findMIn(MinMaxHeap* heap) {
	//kalau size 0 ya return INT_MAX aja
	//return index 0
//}

//int findMax(MinMaxHeap* heap) {
	//kalau 0 return INT_MIN
//	kalau size 1 ya return idx 0
// 	kalau size 2 ya return idx 1
// 	return ternary 1 > 2 ? 1 : 2
//}

//void bubbleDown(MinMaxHeap* heap, int key) {
	//simpan n itu size
	
	//untuk even level -> level MIN
		//min idx itu 
		//left child
		//right child
		
		//kalau idx left < n && val left c < val minIdx
			//ganti min idx dengan left
			
		//begitu dengan right
		
		
		//for loop untuk grand child ??
		
		//nah kalau ada yang ke swab (minIdx != i awal)
			//swap(val idx i dan val minIdx)
			//kalau minIdx nya > idx right
				//simpan idx parent
				//kalau val di minIdx > heap element di parent
					//swap val min idx dengan parent nya
				//rekursi bubble down key = minIdx yang baru
				
	//untuk level Max
	
//}



MinMaxHeap* createMinMaxHeap(int capacity) {
    MinMaxHeap* heap = (MinMaxHeap*)malloc(sizeof(MinMaxHeap));
    heap->size = 0;
    heap->elements = (int*)malloc(capacity * sizeof(int));
    return heap;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i) {
    return (i - 1) / 2;
}

int leftChild(int i) {
    return 2 * i + 1;
}

int rightChild(int i) {
    return 2 * i + 2;
}

int isEvenLevel(int i) {
    int level = 0;
    while (i > 0) {
        i = parent(i);
        level++;
    }
    return level % 2 == 0;
}
// UpHeap
void bubbleUp(MinMaxHeap* heap, int i) {
    if (i == 0) return;

    //Level MIN 
    if (isEvenLevel(i)) {
        // Cek Parent
        if (heap->elements[i] > heap->elements[parent(i)]) {
            swap(&heap->elements[i], &heap->elements[parent(i)]);
            bubbleUp(heap, parent(i));
        }
        // Cek GrandParent
        else {
            if (parent(parent(i)) >= 0 && heap->elements[i] < heap->elements[parent(parent(i))]) {
                swap(&heap->elements[i], &heap->elements[parent(parent(i))]);
                bubbleUp(heap, parent(parent(i)));
            }
        }
    }
      
    // Level MAX
    else {
        if (heap->elements[i] < heap->elements[parent(i)]) {
            swap(&heap->elements[i], &heap->elements[parent(i)]);
            bubbleUp(heap, parent(i));
        } else {
            if (parent(parent(i)) >= 0 && heap->elements[i] > heap->elements[parent(parent(i))]) {
                swap(&heap->elements[i], &heap->elements[parent(parent(i))]);
                bubbleUp(heap, parent(parent(i)));
            }
        }
    }
}

void bubbleDown(MinMaxHeap* heap, int i) {
    int n = heap->size;

    if (isEvenLevel(i)) {
        int minIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < n && heap->elements[left] < heap->elements[minIndex]) {
            minIndex = left;
        }
        if (right < n && heap->elements[right] < heap->elements[minIndex]) {
            minIndex = right;
        }

        for (int j = 2; j <= 4; j++) {
            int grandChild = leftChild(leftChild(i)) + j - 2;
            if (grandChild < n && heap->elements[grandChild] < heap->elements[minIndex]) {
                minIndex = grandChild;
            }
        }

        if (minIndex != i) {
            swap(&heap->elements[i], &heap->elements[minIndex]);
            if (minIndex > right) {
                int parentIdx = parent(minIndex);
                if (heap->elements[minIndex] > heap->elements[parentIdx]) {
                    swap(&heap->elements[minIndex], &heap->elements[parentIdx]);
                }
                bubbleDown(heap, minIndex);
            }
        }
    } else {
        int maxIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < n && heap->elements[left] > heap->elements[maxIndex]) {
            maxIndex = left;
        }
        if (right < n && heap->elements[right] > heap->elements[maxIndex]) {
            maxIndex = right;
        }

        for (int j = 2; j <= 4; j++) {
            int grandChild = leftChild(leftChild(i)) + j - 2;
            if (grandChild < n && heap->elements[grandChild] > heap->elements[maxIndex]) {
                maxIndex = grandChild;
            }
        }

        if (maxIndex != i) {
            swap(&heap->elements[i], &heap->elements[maxIndex]);
            if (maxIndex > right) {
                int parentIdx = parent(maxIndex);
                if (heap->elements[maxIndex] < heap->elements[parentIdx]) {
                    swap(&heap->elements[maxIndex], &heap->elements[parentIdx]);
                }
                bubbleDown(heap, maxIndex);
            }
        }
    }
}

void insert(MinMaxHeap* heap, int key) {
    if (heap->size == MAX_HEAP_SIZE) {
        printf("Heap overflow\n");
        return;
    }

    heap->elements[heap->size] = key;
    heap->size++;
    bubbleUp(heap, heap->size - 1);
}

int findMin(MinMaxHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return INT_MAX;
    }
    return heap->elements[0];
}

int findMax(MinMaxHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return INT_MIN;
    }
    if (heap->size == 1) {
        return heap->elements[0];
    }
    if (heap->size == 2) {
        return heap->elements[1];
    }
    return heap->elements[1] > heap->elements[2] ? heap->elements[1] : heap->elements[2];
}

void deleteMin(MinMaxHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return;
    }

    if (heap->size == 1) {
        heap->size--;
        return;
    }

    heap->elements[0] = heap->elements[heap->size - 1];
    heap->size--;
    bubbleDown(heap, 0);
}

void deleteMax(MinMaxHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return;
    }

    if (heap->size == 1) {
        heap->size--;
        return;
    }

    int maxIndex = heap->size == 2 ? 1 : (heap->elements[1] > heap->elements[2] ? 1 : 2);

    heap->elements[maxIndex] = heap->elements[heap->size - 1];
    heap->size--;
    bubbleDown(heap, maxIndex);
}

void displayHeap(MinMaxHeap* heap) {
    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->elements[i]);
    printf("\n");
}

int main() {
    MinMaxHeap* heap = createMinMaxHeap(MAX_HEAP_SIZE);

    insert(heap, 3);
    insert(heap, 2);
    insert(heap, 15);
    insert(heap, 5);
    insert(heap, 4);
    insert(heap, 45);

    printf("Heap elements: ");
    displayHeap(heap);

    printf("Min element: %d\n", findMin(heap));
    printf("Max element: %d\n", findMax(heap));

    deleteMin(heap);
    printf("Heap elements after deleting min: ");
    displayHeap(heap);
    printf("Min element after deletion: %d\n", findMin(heap));

    deleteMax(heap);
    printf("Heap elements after deleting max: ");
    displayHeap(heap);
    printf("Max element after deletion: %d\n", findMax(heap));

    free(heap->elements);
    free(heap);

    return 0;
}



