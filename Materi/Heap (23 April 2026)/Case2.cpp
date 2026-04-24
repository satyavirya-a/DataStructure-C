#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEAP_SIZE 100

typedef struct Data {
	char ID[5];
	int score;
}Data;

typedef struct MinMaxHeap {
	int size;
	Data* elements;
}MinMaxHeap;

MinMaxHeap* create(int capacity) {
	MinMaxHeap* h = (MinMaxHeap*)malloc(sizeof(MinMaxHeap));
	h->size = 0;
	h->elements = (Data*)malloc(capacity * sizeof(Data));
	
	return h;
}

void swap(Data *a, Data *b) {
	Data temp = *a;
	*a = *b;
	*b = temp;
}

//buat fungsi untuk dapatkan index pendukung
int parentIdx(int i) {
	if (i == 0) return -1;
	return (i - 1)/2;
}

int leftChildIdx(int i) {
	return 2*i + 1;
}

int rightChildIdx(int i) {
	return 2*i + 2;
}

int isMinLevel(int idx) {
	int level = 0;
	
	int i = idx;
	while (i > 0) {
		i = parentIdx(i);
		level++;
	}
	
	return (level % 2 == 0);
}

void bubbleUpMin(MinMaxHeap* heap, int idx) { //ngambil grandparent buat di cek apakah untuk level sama, udah cocok lokasinya
	int grandparentIdx;
	while(idx > 0) {
		grandparentIdx = parentIdx(parentIdx(idx));
		
		if (grandparentIdx >= 0 && heap->elements[idx].score < heap->elements[grandparentIdx].score) {
			swap(&heap->elements[idx], &heap->elements[grandparentIdx]);
			idx = grandparentIdx;
		}
		else {
			break;
		}
	}
}

void bubbleUpMax(MinMaxHeap* heap, int idx) {
	int grandparentIdx;
	while(idx > 0) {
		grandparentIdx = parentIdx(parentIdx(idx));
		
		if (grandparentIdx >= 0 && heap->elements[idx].score > heap->elements[grandparentIdx].score) {
			swap(&heap->elements[idx], &heap->elements[grandparentIdx]);
			idx = grandparentIdx;
		}
		else {
			break;
		}
	}
}

void bubbleUp(MinMaxHeap* heap, int idx) {
	if (idx == 0) return;
	
	int p = parentIdx(idx);
	
	if (isMinLevel(idx)) {
		
		if (heap->elements[idx].score > heap->elements[p].score) { //kalau misal lebih besar dari parent
			swap(&heap->elements[idx], &heap->elements[p]); //swap dengan parent dulu
			bubbleUpMax(heap, p); //baru cek dengan grandparent, awalnya min, karena pindah level jadi max, makanya cari yang max
		}
		else {
			bubbleUpMin(heap, idx); // kalau udah sesuai dengan parent, langsung cek dengan grandparent aja
		}
	}
	
	else { //max level
		if (heap->elements[idx].score < heap->elements[p].score) {
			
			swap(&heap->elements[idx], &heap->elements[p]);
			bubbleUpMin(heap, p);
		}
		
		else {
			bubbleUpMax(heap, idx);
		}
	}
}

int findMinDescendantIdx(MinMaxHeap* heap, int idx) {
	//cek children dan grandchild minimal untuk cari yang bisa menggantikan nilainya
	
	int minIdx = idx;
	int left = leftChildIdx(idx);
	int right = rightChildIdx(idx);
	
	//cek child
	if (left < heap->size && heap->elements[left].score < heap->elements[minIdx].score) {
		minIdx = left;
	}
	if (right < heap->size && heap->elements[right].score  < heap->elements[minIdx].score) {
		minIdx = right;
	}
	
	//cek lagi anak dari anak kiri
	if (left < heap->size) {
		int ll = leftChildIdx(left);
		int lr = rightChildIdx(left);
		
		if (ll < heap->size && heap->elements[ll].score < heap->elements[minIdx].score) {
			minIdx = ll;
		}
		if (lr < heap->size && heap->elements[lr].score < heap->elements[minIdx].score) {
			minIdx = lr;
		}
	}
	
	//cek anak dari anak kanan
	if (right < heap->size) {
		int rl = leftChildIdx(right);
		int rr = rightChildIdx(right);
		
		if (rl < heap->size && heap->elements[rl].score < heap->elements[minIdx].score) {
			minIdx = rl;
		}
		if (rr < heap->size && heap->elements[rr].score < heap->elements[minIdx].score) {
			minIdx = rr;
		}
	}
	
	return minIdx;
}

int findMaxDescendantIdx(MinMaxHeap* heap, int idx) {
	
	int maxIdx = idx;
	int left = leftChildIdx(idx);
	int right = rightChildIdx(idx);
	
	//cek child
	if (left < heap->size && heap->elements[left].score > heap->elements[maxIdx].score) {
		maxIdx = left;
	}
	if (right < heap->size && heap->elements[right].score  > heap->elements[maxIdx].score) {
		maxIdx = right;
	}
	
	//cek lagi anak dari anak kiri
	if (left < heap->size) {
		int ll = leftChildIdx(left);
		int lr = rightChildIdx(left);
		
		if (ll < heap->size && heap->elements[ll].score > heap->elements[maxIdx].score) {
			maxIdx = ll;
		}
		if (lr < heap->size && heap->elements[lr].score > heap->elements[maxIdx].score) {
			maxIdx = lr;
		}
	}
	
	//cek anak dari anak kanan
	if (right < heap->size) {
		int rl = leftChildIdx(right);
		int rr = rightChildIdx(right);
		
		if (rl < heap->size && heap->elements[rl].score > heap->elements[maxIdx].score) {
			maxIdx = rl;
		}
		if (rr < heap->size && heap->elements[rr].score > heap->elements[maxIdx].score) {
			maxIdx = rr;
		}
	}
	
	return maxIdx;
}

void bubbleDown(MinMaxHeap* heap, int idx) {
	if (heap->size <= idx) {
		return;
	}
	
	if (isMinLevel(idx)) {
		
		int m = findMinDescendantIdx(heap, idx);
		if (m != idx) {
			swap(&heap->elements[m], &heap->elements[idx]);
			
			if (parentIdx(m) != idx) {
				int p = parentIdx(m);
				if (heap->elements[m].score < heap->elements[p].score) {
					swap(&heap->elements[m], &heap->elements[p]);
				}
			}
			bubbleDown(heap, m);
		}
	}
	
	else {
		
		int m = findMaxDescendantIdx(heap, idx);
		if (m != idx) {
			swap(&heap->elements[m], &heap->elements[idx]);
			
			//kalau parent dari descendant itu bukan idx -> dia grandchild
			if (parentIdx(m) != idx) {
				int p = parentIdx(m); //cek lagi dengan parent nya apakah sudah sesuai
				if (heap->elements[m].score > heap->elements[p].score) {
					swap(&heap->elements[m], &heap->elements[p]);
				}
			}
			bubbleDown(heap,m); // rekursi ke tempat tadi ngambil value terbesar
		}
	}
}

void insert(MinMaxHeap* heap, Data key) {
	if (heap->size == MAX_HEAP_SIZE) {
		printf("Heap overflow\n");
		return;
	}
	
	heap->elements[heap->size] = key;
	heap->size++;
	bubbleUp(heap, heap->size - 1);
}

Data deleteMin(MinMaxHeap* heap) {
	Data temp = {0};
	if (heap->size == 0) {
		printf("Heap Kososng\n");
		return temp;
	}
	
	if (heap->size == 1) {
		temp = heap->elements[0];
		heap->size--;
		return temp;
	}
	
	temp = heap->elements[0];
	heap->elements[0] = heap->elements[heap->size - 1];
	heap->size--;
	bubbleDown(heap, 0);
	return temp;
}

Data deleteMax(MinMaxHeap* heap) {
	Data temp = {0};
	if (heap->size == 0 ) {
		printf("Heap Kosong\n");
		return temp;
	}
	
	if (heap->size == 1) {
		temp = heap->elements[0];
		heap->size--;
		return temp;
	}
	
	int maxIdx;
	if (heap->size == 2)  {
		maxIdx = 1;
	}
	else {
		maxIdx = (heap->elements[1].score > heap->elements[2].score) ? 1 : 2;
	}
	
	temp = heap->elements[maxIdx];
	
	heap->elements[maxIdx] = heap->elements[heap->size-1]; //di swap dengan idx terbesar
	heap->size--;
	if (maxIdx < heap->size) {
		bubbleDown(heap, maxIdx);
	}
	
	return temp;
}


void display(MinMaxHeap* heap) { 
	if (heap->size == 0) {
		return;
	}
	
	for (int i = 0; i < heap->size; i++ ) {
		printf("%s %d\n", heap->elements[i].ID, heap->elements[i].score);
	}
}


int main() {
	
	MinMaxHeap* heap = create(MAX_HEAP_SIZE);
	
	char line[100] = {0};
	do {
		scanf("%[^\n]", line);
//		printf("line sebelum strtok %s\n", line);
		getchar();
		char * command = strtok(line, " "); // PING DS01 64
		if (strcmp(command, "PING") == 0) {
			Data temp;
			char* ID = strtok(NULL, " ");
			strcpy(temp.ID, ID);
			
			char* ScoreString = strtok(NULL, " ");
			temp.score = atoi(ScoreString);
			
//			printf("data %s %d\n", temp.ID, temp.score);
			insert(heap, temp);
		}
		
		else if (strcmp(command, "DIVERT_SURPLUS") == 0) {
			Data temp = deleteMax(heap);
			printf("[LOGISTIC] Diverting surplus from Region %s (Score: %d)\n", temp.ID, temp.score);
		}
		
		else if (strcmp(command, "DISPATCH_SOS") == 0) {
			Data temp = deleteMin(heap);
			printf("[EMERGENCY] Routing aid to Region %s (Score: %d)\n", temp.ID, temp.score);
		}
	} while (strcmp(line, "SHUTDOWN") != 0);
	
//	display(heap);

	
	return 0;
}



