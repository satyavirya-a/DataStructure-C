#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

typedef struct node {
	int key;
	char* name;
	struct node* next;
}node;

node* hashTable[SIZE] = {NULL};

node* createNode(char* name, int key) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->key = key;
	newNode->name = strdup(name);
	newNode->next = NULL;
	
	return newNode;
}

//Hashing Func
int division(int key) {
	return key % SIZE;
}

int midSquare(int key) {
	
	long long int square = key*key;
	int temp = square;
	int digit = 0;
	//cari total digit
	while (temp > 0 ) {
		digit++;
		temp /=10;
	}
	//karena mau ambil 3 digit ditengah
	int digityangdiambil = 3;
	
	if (digit < digityangdiambil) return (int)square; //kalau ternyata kurang dari 3 angka
	
	int trimnum = (digit - digityangdiambil)/2; //dibagi 2 karena seharusnya kanan dan kiri kan
												//kita pake yang ujung kanannya doangs
	for (int i = 0; i <trimnum; i++) {
		square = square / 10;
	}
	
	//untuk yang digit 3 ditengah 1000
	return square % 1000;
	
}

int folding(int key) {
	//misal mau bagi 2 angka
	int divisor = 2*10;
	int part = 0;
	int sum = 0;
	while (key > 0) {
		part = key % divisor;
		
		sum += part;
		
		key /= divisor;
	}
	return sum;
}

int rotating(int key) {
	
	int remainder = 0;
	int result = 0;
	while (key > 0) {
		remainder = key % 10;
		result = result*10 + remainder;
		key /= 10;
	}
	return result;
}

int hashFunc(int key) {
	int hasil = midSquare(key);
	hasil = folding(hasil);
	hasil = division(hasil);
	
	return hasil;
}


//chaining
void insert(char* name, int key) {
	int hashIdx = hashFunc(key);
	
	node* newNode = createNode(name, key);
	
	if (hashTable[hashIdx] == NULL) {
		hashTable[hashIdx] = newNode;
		return;
	}
	
	node* curr = hashTable[hashIdx];
	while (curr->next != NULL) {
		curr = curr->next;
	}
	
	curr->next = newNode;
	return;
	

}

void view() {
	for (int i = 0; i < SIZE; i++) {
		if (hashTable[i] == NULL) {
			printf("idx %d = Kosong\n", i);
		}
		else {
			if (hashTable[i]->next == NULL) {
				printf("idx %d = %d\n", i, hashTable[i]->key);
			}
			else {
				node* curr = hashTable[i]; 
				while( curr != NULL) {
					printf("idx %d = %d\n", i, curr->key );
					curr = curr->next;
				}
				
			}
		}          
	}
}

void pop(int key) {
	int hashIdx = hashFunc(key);
	
	if (hashTable[hashIdx] == NULL) {
		printf("gak bisa di pop\n");
		return;
	}
	
	if (hashTable[hashIdx]->key == key) {
		node* del = hashTable[hashIdx];
		hashTable[hashIdx] = hashTable[hashIdx]->next;
		free(del->name);
		free(del);
		return;
	}
	
	if (hashTable[hashIdx]->key != key) {
		node* curr = hashTable[hashIdx];
		while (curr->next != NULL && curr->next->key != key) {
			curr = curr->next;
		}
		
		if (curr->next == NULL ) {
			printf("tidak ditemukan");
			return;
		}
		node* del = curr->next;
		curr->next = del->next;
		free(del->name);
		free(del);
		return;
		
	}
	
	
}




int main() {
	
	int key = 243;
	int hasil = midSquare(key);
	printf("hasil= %d\n", hasil);
	int hasil2 = rotating(hasil);
	printf("hasil2 = %d\n", hasil2);
	
	return 0;
} 	
