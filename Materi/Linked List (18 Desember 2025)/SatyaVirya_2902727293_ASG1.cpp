#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
	
	int key;
	char* name;
	struct Node* next;
	
}Node;

Node* head = NULL;
//Node* tail = NULL;

							//const biar gak ada berubah berubah di function
Node* createNode(int key, const char* str) {
	
	Node* node = (Node*)malloc(sizeof(Node));
	node->name = (char*)malloc(strlen(str) + 1); //buat \0
	strcpy(node->name, str);
	node->key = key;
	node->next = NULL;
	
	return node;
}

void insert() {
	printf("MASUKAN 5 Data Key dan Name\n");
	int angka;
	char str[30];
	
	for (int i =0 ; i < 5; i++) {
		printf("Data Node-%d:\n", i+ 1);
		printf("Key: ");
		scanf("%d", &angka); getchar();
		printf("Name: ");
		scanf("%s", str); getchar();
		
		Node *newNode = createNode(angka, str);
			
		newNode->next = head;
		head = newNode;
		
		
	
		
	}
}


void print() {
	
	Node *curr = head;
	while(curr != NULL) {
		printf("Key = %d | Name = %s\n", curr->key, curr->name);
		curr = curr->next;
	}
	
	printf("NULL\n");
}

void hapus() {
	int tar;
	printf("Key = ");
	scanf("%d", &tar);
	
	if (head == NULL) {
        printf("List kosong\n");
        return;
    }
    
	Node *curr = head;
	
	if (tar == head->key) {
		head = head->next;
		free(curr->name);
		free(curr); //yang di free itu variable temp ya
		return;
	}
	while (curr->next != NULL && curr->next->key != tar) {
		curr = curr->next;
	}
	if (curr->next == NULL) {
		printf("Key tidak ditemukan\n");
		return;
	}
	
	
	Node* del = curr->next;
	curr->next = del->next;
	free(del->name);
	free(del);
}

void menu() {
	
	int opsi;
	
	while(1) {
		printf("MENU\n");
		printf("1. Insert\n");
		printf("2. Delete\n");
		printf("3. Display\n");
		printf("4. Exit\n");
		printf(">> ");
		scanf("%d", &opsi); getchar();
		
		switch (opsi) {
			case 1: insert();
				break;
			case 2: hapus();
				break;
			case 3:print();
				break;
			case 4: return;
		}
	}
	
}

int main() {
	
	
	
	menu();
	
	
	
	return 0;
}
