#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 100

typedef struct node {
	char* plate;
	char* name;
	char* code;
	struct node* next;

}node;

node* hashTable[SIZE] = {NULL};

node* createNode(const char* plate,const char* name ) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->plate = strdup(plate);
	newNode->name = strdup(name);
	newNode->code = NULL;
	newNode->next = NULL;
	
	return newNode;
}

//hashing func
int ASCIISum(const char* plate) {
	int res = 0;
	int len = strlen(plate);
	for (int i = 0; i < len; i++) {
		res += plate[i];
	}
	
	return res;
}

int midSquare(int angka) {
	long long int square = angka*angka;
	long long int result = square;
	int digitres = 2; //mau ambil 2
	int digit = 0;
	while (square > 0) {
		digit++;
		square /= 10;
	}
	
	int trim = (digit - digitres)/2;
	
	for (int i =0 ; i < trim; i++) {
		result /= 10;
	}
	
	int hasil = result % 100;
	
	return hasil;
}

int hashFunc(const char* plate) {
	int hasil = ASCIISum(plate);
	hasil = midSquare(hasil);
	
	return hasil;
}

char* genParCode() {
	
	char alphanum[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int n = strlen(alphanum) - 1;
	static char res[5];
	for (int i =0 ; i < 5; i++) {
		res[i] = alphanum[rand() % n];
	}
	res[5] = '\0';
	
	return res;
	
}

void insert(const char* plate, const char* name ) {
	node* newNode = createNode(plate, name);
	newNode->code = strdup(genParCode());
	
	//simpen di index
	int hashIdx = hashFunc(plate);
	
	if (hashTable[hashIdx] == NULL) {
		hashTable[hashIdx] = newNode;
		printf("Plate: %s\n", hashTable[hashIdx]->plate);
		printf("Name: %s\n", hashTable[hashIdx]->name);
		printf("Code: %s\n", hashTable[hashIdx]->code);
		return;
	}
	node* curr = hashTable[hashIdx];
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = newNode;
	
	printf("Plate: %s\n", hashTable[hashIdx]->plate);
	printf("Name: %s\n", hashTable[hashIdx]->name);
	printf("Code: %s\n", hashTable[hashIdx]->code);
	return;
	
	
}

void view() {
	for (int i =0 ; i < SIZE; i++) {
		if (hashTable[i] == NULL) {
			printf("idx %d = NULL\n", i);
		}
		else {
			printf("idx %d = %s\n", i, hashTable[i]->code);
			node* curr = hashTable[i]->next;
			while (curr != NULL) {
				printf("%s\n", curr->code);
				curr = curr->next;
			}
		}
	}
}

void searchPlate(const char* plate) {
	//cari langsung pake hashIdx
	int hashIdx = hashFunc(plate);
	if (hashTable[hashIdx] == NULL) {
		printf("Data tidak ditemukan\n");
	}
	if (strcmp(hashTable[hashIdx]->plate, plate) == NULL) {
		printf("Plate: %s\n", hashTable[hashIdx]->plate);
		printf("Name: %s\n", hashTable[hashIdx]->name);
		printf("Code: %s\n", hashTable[hashIdx]->code);
	}
	else {
		node* curr = hashTable[hashIdx];
		while (curr != NULL && strcmp(curr->plate, plate) != 0) {
			curr = curr->next;
		}
		
		if (curr != NULL) {
			printf("Plate: %s\n", curr->plate);
			printf("Name: %s\n", curr->name);
			printf("Code: %s\n", curr->code);
		}
		else {
			printf("Data tidak ditemukan\n");
		}
		
		
	}
}

void remove2(const char* platetar) {
	int hashIdx = hashFunc(platetar);
	
	if (hashTable[hashIdx] == NULL) {
		printf("Data tidak ditemukan\n");
	}
	//cuma 1 node dan dia yang mau didelete
	if (strcmp(hashTable[hashIdx]->plate, platetar) == 0 && hashTable[hashIdx]->next == NULL) {
		free(hashTable[hashIdx]->name);
		free(hashTable[hashIdx]->plate);
		free(hashTable[hashIdx]->code);
		hashTable[hashIdx] = NULL;
	}
	//node banyak tapi pophead
	else if(strcmp(hashTable[hashIdx]->plate, platetar) == 0 && hashTable[hashIdx]->next != NULL){
		node* curr  = hashTable[hashIdx];
		hashTable[hashIdx] =  hashTable[hashIdx]->next;
		free(curr->plate);
		free(curr->plate);
		free(curr);
	}
	else {
		node* curr = hashTable[hashIdx];
		node* prev = NULL;
		while (curr != NULL && strcmp(curr->plate, platetar) != 0) {
			prev = curr;
			curr = curr->next;
		}
		
		if (curr != NULL) {
			prev->next = curr->next;
			free(curr->name);
			free(curr->plate);
			free(curr->code);
			free(curr);
		}
		else {
			printf("Data tidak ditemukan\n");
		}
		
		
	}
}


void menuInsert() {
	char name[100];
	char plate[10];
	printf("Plate: ");
	scanf("%s", plate); getchar();
	printf("Name: ");
	scanf("%[^\n]", name); getchar();
	insert(plate, name);
}

void verify() {
	char plate[10];
	printf("Plate: ");
	scanf("%s", plate); getchar();
	searchPlate(plate);
	
}

void menuRemove() {
	char plate[10];
	printf("Plate: ");
	scanf("%s", plate);
	remove2(plate);
}

 

int main() {
	
	srand(time(NULL));
	int opt;
	
	do {
		view();
		printf("1. Register\n");
		printf("2. Verify\n");
		printf("3. View All\n");
		printf("4. Remove Vehicle\n");
		printf("5. Exit\n");
		scanf("%d", &opt); getchar();
		switch (opt) {
			case 1: menuInsert();
				break;
			case 2: verify();
				break;
			case 3: view();
				break;
			case 4: menuRemove();
				break;
			case 5:
				break;
			default: printf("OPsi salah\n");
		}
	} while (opt != 5);
	
	
	return 0;
}







