#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//pop head
// tiap push, ink berkurang
//input n task dan jumlah ink berapa

typedef struct node {
	int code;
	int ink;
	node* next;
}node;

node* createNode(int code, int ink) {
	node* n = (node*)malloc(sizeof(node));
	n->code = code;
	n->ink = ink;
	n->next = NULL;
	
	return n;
}

node* pushTail(node* head, int code, int ink) {
	if (head == NULL) {
		head = createNode(code, ink);
		return head;
	}
	
	node* curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	node* newNode = createNode(code, ink);
	newNode->next = curr->next;
	curr->next = newNode;
	return head;
}

//remove cuma bisa dari head;

node* popHead(node* head) {
	if (head == NULL) {
		printf("Data tidak ada\n");
		return head;
	}
	
	if (head->next == NULL) {
		node* del = head;
		free(del);
		head = NULL;
		return head;
	}
	
	node* del = head;
	head = head->next;
	free(del);
	return head;
}



void view(node* head) {
	if (head == NULL) {
		printf("Completed");
		return;
	}
	node* curr = head;
	while (curr!= NULL) {
		printf("%d", curr->code);
		if (curr->next != NULL) {
			printf(" ");
		}
		curr = curr->next;
	}
	return;
}

node* result(node* head, int totalInk) {
	node* curr = head;
	if (head == NULL || totalInk == 0) {
		return head;
	}
	while (head != NULL) {
		totalInk -= head->ink;
		if (totalInk >= 0) {
			head = popHead(head); //ketika == masih dijalankan
		}
		else {
			break;
		}
		
	
	}
	return head;
}

int main() {
	
	int n;
	int totalInk;
	node* head = NULL;
	scanf("%d %d", &n, &totalInk);
	for (int i =0 ; i < n; i++) {
		int code, ink;
		scanf("%d %d", &code, &ink);
		head = pushTail(head, code, ink);
	}
	
	head = result(head, totalInk);
	view(head);
	
	
	return 0;
}
