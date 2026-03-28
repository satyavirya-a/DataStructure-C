#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char *word;
	Node* next;
	
}Node;

Node* head = NULL;
Node* tail = NULL;
Node* redoHead = NULL;
Node* redoTail = NULL;

Node* createNode(const char* str) {
	
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->word = strdup(str);
	newNode->next = NULL;
	
	return newNode;
}

void pushTail(const char* str) {
	
	Node* newNode = createNode(str);
	
	if (head == NULL) {
		head = tail = newNode;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}
}

void popTail() {
	
	Node* curr = head;
	
	if (head == NULL) {
		printf("Data tidak ada\n");
		return;
	}
	if (head == tail) {
		free(head);
		head = tail = NULL;
		return;
	}
	
	while(curr->next != tail) {
		curr = curr->next;
	}
	
	if (redoHead == NULL) {
		tail = redoHead;
	}
	else {
		tail->next = redoHead;
		redoHead = tail;
	}
	tail = curr;
	tail->next = NULL;
}

void add() {
	system("cls");
	char str[100]; //kalau gak mau pake buffer, harus getline()
	printf("Add Word\n");
	
	printf("Masukan word: ");
	scanf("%s", str); getchar();
	pushTail(str);
}

void view() {
	system("cls");
	Node *curr = head;
	printf("VIEW DOC\n");
	
	if (head == NULL) {
		printf("Data kosong\n");
		return;
	}
	
	while(curr != NULL) {
		printf("%s", curr->word);
		if (curr->next != NULL) printf("*");
		curr = curr->next;
	}
	
//	for(Node *n = head; n; n = n->next){
//		printf("%s ", n->word);
//	}
//	printf("\n");
}

void delAll() {
	system("cls");
	while (head != NULL) {
		popTail();
	}
	
}


void menu() {
	
	int opt = 0;
	
	do {
		system("cls");
		printf("Doc\n");
		printf("1. Add Word\n");
		printf("2. Undo\n");
		printf("3. View Document\n");
		printf("4. Clear All\n");
		printf("5. Redo\n");
		printf("6. Exit\n");
		printf(">> ");
		scanf("%d", &opt); getchar();
		
		switch (opt) {
			case 1: add();
				break;
			case 2: popTail();
				getchar();
				break;
			case 3: view();
				getchar();
				break;
			case 4: delAll();
				getchar();
				break;
			case 5:
				break;
		}
	} while (opt != 6);
}

int main() {
	
	menu();
	
	
	return 0;
}
