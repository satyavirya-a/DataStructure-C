#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

typedef struct Item{
	char* key;
	int data;
	Item* next;
}Item;

Item* HashTable[SIZE] = {NULL};


	//=========================HASH FUNCTION==========================
//Division
int hashDiv(int key) {
	return key % SIZE; //dari 0 sampai (SIZE - 1)
}

//Jumlahin ASCII
int hashAscii(char * str) {
	int sum = 0;
	
	int len = strlen(str);
	//jumlahin ascii semua karakter
	for (int i =0 ; i< len; i++) {
		sum += (int) str[i];
	}
	
	return sum;
}

//Rotating / Reverse
int hashRot(int key) {
	int result = 0;
	int remainder = 0;
	
	while (key > 0) {
		remainder = key % 10;
		result = result * 10 + remainder; //digit sebelum dikali 10, tambahin digiti yang baru dimodulo
		key = key/10;
	}
	
	return result;
}

int hashFunc(char* str) {
	int result = hashAscii(str);
	result = hashDiv(result);
	result = hashRot(result);
	return result;
}


	//=========================== FUNCTION ===============
void insert(char* key, int data) {
	Item* newItem = (Item*) malloc(sizeof(Item));
	newItem->data = data;
	newItem->key = strdup(key);
	newItem->next = NULL;
	
	int hashIdx = hashFunc(key);
	if (HashTable[hashIdx] == NULL) {
		HashTable[hashIdx] = newItem;
	}
	else {
		//transverse sampai curr->next == NULL
		Item* curr = HashTable[hashIdx];
		
		while (curr->next != NULL) {
			curr = curr->next;
		}
		
		curr->next = newItem;
		
	}
}

void print(){
	for (int i= 0; i < 100; i++) {
		if (hashTable[i] == NULL) {
			printf("Kosong\n");
		}
		else {
			Item* curr = hashTable[i];
			while (curr != NULL) {
				printf("%s ->",n curr->data);
				curr = curr->next;
			}
		}
	}
}

Item* search(char* key) {
	
	//cari indexnya pake hash
	int idx = hashFunc(key);
	
	if (HashTable[idx] == NULL) {
		printf("Data tidak ada ");
	}
	
//	else {
//		if ()
//	}
}

Item* deleteItem(char* key, ) {
	int hashIdx = 
	if (hashTable == NULL) {
		printf("DATA Kosong");
	}
	else {
		Item* curr = hashTable[idx];
		Item* prev = NULL;
		while (curr != NULL) {
			
		}
	}
	
	
}


int main() {
	
	int key1 = 453;
	int divKey = hashDiv(key1);
	printf("divKey : %d\n", divKey);
	
	char key2[] = {"NasiGoreng"};
	int asciKey = hashAscii(key2);
	printf("asciKey = %d\n", asciKey);
	
	insert("PPTIBCA", 10);
	insert("PPTIBCA", 60);
	
	
	return 0;
}
