#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_HEAP_SIZE 100

typedef struct MinMaxHeap {
    int size;
    int *elements;
} MinMaxHeap;

MinMaxHeap* createMinMaxHeap(int capacity) {
    MinMaxHeap* heap = (MinMaxHeap*) malloc(sizeof(MinMaxHeap));
    heap->size = 0;
    heap->elements = (int*) malloc(capacity * sizeof(int));
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

int isMinLevel(int i) {
    int level = 0;
    int temp = i;
    while (temp > 0) {
        temp = parent(temp);
        level++;
    }
    return (level % 2 == 0);
}

void bubbleUpMin(MinMaxHeap* heap, int i) {
    int grandparent;
    while (i > 0) {
        grandparent = parent(parent(i));
        if (grandparent >= 0 && heap->elements[i] < heap->elements[grandparent]) {
            swap(&heap->elements[i], &heap->elements[grandparent]);
            i = grandparent;
        } else {
            break;
        }
    }
}

void bubbleUpMax(MinMaxHeap* heap, int i) {
    int grandparent;
    while (i > 0) {
        grandparent = parent(parent(i));
        if (grandparent >= 0 && heap->elements[i] > heap->elements[grandparent]) {
            swap(&heap->elements[i], &heap->elements[grandparent]);
            i = grandparent;
        } else {
            break;
        }
    }
}

void bubbleUp(MinMaxHeap* heap, int i) {
    if (i == 0) return;
    
    int p = parent(i);
    
    if (isMinLevel(i)) {
        // Current node is at MIN level
        if (heap->elements[i] > heap->elements[p]) {
            // Swap with parent (MAX level)
            swap(&heap->elements[i], &heap->elements[p]);
            bubbleUpMax(heap, p);
        } else {
            bubbleUpMin(heap, i);
        }
    } else {
        // Current node is at MAX level
        if (heap->elements[i] < heap->elements[p]) {
            // Swap with parent (MIN level)
            swap(&heap->elements[i], &heap->elements[p]);
            bubbleUpMin(heap, p);
        } else {
            bubbleUpMax(heap, i);
        }
    }
}

int findMinDescendant(MinMaxHeap* heap, int i) {
    int n = heap->size;
    int minIdx = i;
    int left = leftChild(i);
    int right = rightChild(i);
    
    // Check children
    if (left < n && heap->elements[left] < heap->elements[minIdx])
        minIdx = left;
    if (right < n && heap->elements[right] < heap->elements[minIdx])
        minIdx = right;
    
    // Check grandchildren
    if (left < n) {
        int ll = leftChild(left);
        int lr = rightChild(left);
        if (ll < n && heap->elements[ll] < heap->elements[minIdx])
            minIdx = ll;
        if (lr < n && heap->elements[lr] < heap->elements[minIdx])
            minIdx = lr;
    }
    
    if (right < n) {
        int rl = leftChild(right);
        int rr = rightChild(right);
        if (rl < n && heap->elements[rl] < heap->elements[minIdx])
            minIdx = rl;
        if (rr < n && heap->elements[rr] < heap->elements[minIdx])
            minIdx = rr;
    }
    
    return minIdx;
}

int findMaxDescendant(MinMaxHeap* heap, int i) {
    int n = heap->size;
    int maxIdx = i;
    int left = leftChild(i);
    int right = rightChild(i);
    
    // Check children
    if (left < n && heap->elements[left] > heap->elements[maxIdx])
        maxIdx = left;
    if (right < n && heap->elements[right] > heap->elements[maxIdx])
        maxIdx = right;
    
    // Check grandchildren
    if (left < n) {
        int ll = leftChild(left);
        int lr = rightChild(left);
        if (ll < n && heap->elements[ll] > heap->elements[maxIdx])
            maxIdx = ll;
        if (lr < n && heap->elements[lr] > heap->elements[maxIdx])
            maxIdx = lr;
    }
    
    if (right < n) {
        int rl = leftChild(right);
        int rr = rightChild(right);
        if (rl < n && heap->elements[rl] > heap->elements[maxIdx])
            maxIdx = rl;
        if (rr < n && heap->elements[rr] > heap->elements[maxIdx])
            maxIdx = rr;
    }
    
    return maxIdx;
}

void bubbleDown(MinMaxHeap* heap, int i) {
    if (heap->size <= i) return;
    
    if (isMinLevel(i)) {
        // MIN level: find minimum among descendants
        int m = findMinDescendant(heap, i);
        if (m != i) {
            swap(&heap->elements[i], &heap->elements[m]);
            
            // If m is a grandchild, check with its parent
            if (parent(m) != i) {
                int p = parent(m);
                if (heap->elements[m] > heap->elements[p]) {
                    swap(&heap->elements[m], &heap->elements[p]);
                }
            }
            bubbleDown(heap, m);
        }
    } else {
        // MAX level: find maximum among descendants
        int m = findMaxDescendant(heap, i);
        if (m != i) {
            swap(&heap->elements[i], &heap->elements[m]);
            
            // If m is a grandchild, check with its parent
            if (parent(m) != i) {
                int p = parent(m);
                if (heap->elements[m] < heap->elements[p]) {
                    swap(&heap->elements[m], &heap->elements[p]);
                }
            }
            bubbleDown(heap, m);
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
    if (heap->size == 1) return heap->elements[0];
    if (heap->size == 2) return heap->elements[1];
    
    int max = heap->elements[1];
    if (heap->elements[2] > max) max = heap->elements[2];
    return max;
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
    
    int maxIdx;
    if (heap->size == 2) {
        maxIdx = 1;
    } else {
        maxIdx = (heap->elements[1] > heap->elements[2]) ? 1 : 2;
    }
    
    heap->elements[maxIdx] = heap->elements[heap->size - 1];
    heap->size--;
    if (maxIdx < heap->size) {
        bubbleDown(heap, maxIdx);
    }
}

void displayHeap(MinMaxHeap* heap) {
    printf("Heap array: ");
    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->elements[i]);
    printf("\n");
}

void displayHeapLevels(MinMaxHeap* heap) {
    if (heap->size == 0) return;
    
    int level = 0;
    int count = 0;
    int levelSize = 1;
    
    while (count < heap->size) {
        printf("Level %d (%s): ", level, (level % 2 == 0) ? "MIN" : "MAX");
        for (int i = 0; i < levelSize && count < heap->size; i++) {
            printf("%d ", heap->elements[count++]);
        }
        printf("\n");
        level++;
        levelSize *= 2;
    }
}

int main() {
    MinMaxHeap* heap = createMinMaxHeap(MAX_HEAP_SIZE);
    
    int data[] = {3, 7, 9, 23, 45, 1, 5, 14, 25, 24, 13, 11, 8, 19, 4, 31, 35, 56, 20, 52};
    int size = sizeof(data) / sizeof(data[0]);
    
    printf("Inserting: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
        insert(heap, data[i]);
    }
    
    printf("\n\n");
    displayHeap(heap);
    printf("\n");
    displayHeapLevels(heap);
    
    printf("\nMinimum = %d\n", findMin(heap));
    printf("Maximum = %d\n", findMax(heap));
    
    free(heap->elements);
    free(heap);
    
    return 0;
}
