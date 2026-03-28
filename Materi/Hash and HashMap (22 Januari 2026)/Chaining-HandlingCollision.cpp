#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef struct DataItem {
	int key;
	int data;
	struct DataItem *next;
} DataItem;

DataItem* hashTable[SIZE];

int hashFunc(int key) {
	return key % SIZE;
}

void insert(int key, int data) {
	DataItem* newItem = malloc(sizeof(DataItem));
	newItem->key = key;
	newItem->data = data;
	newItem->next = NULL;
	
	int hashIndex = hashFunc(key);
	
	if (hashTable[hashIndex] == NULL) { //jika kosong, masukin newItem
		hashTable[hashIndex] = newItem;
		printf("Data masuk");
	}
	
	else { //kalau ada isinya ? Insert tail
		DataItem* current = hashTable[hashIndex];
		while (current->next != NULL) {
			current = current->next;
		}
		
		current->next = newItem;
	}
	
	

}

/*
	DELETE
	buat hashIdx
	buat pointer curr = table[hashidx] dan prev = null
	selama curr bukan null
		jika curr->key == key
			jika prev == null (head doang)
				ganti value table jadi curr->next (NULL)
			else (masih ada dibelakangnya)
				node prev (node sebelum curr) ->next = curr->next [sambungin sebelum dan sesudah curr]
			
			bisa return
		
		(kalau key nya curr bukan yang dicari)
		prev = curr 
		curr = curr->next
	
	DISPLAY
	looping i dari idx 0 sampai SIZE
		buat pointer curr = hashTable[i];
		while (curr != NULL)
			print curr->key
		
*/	
	

