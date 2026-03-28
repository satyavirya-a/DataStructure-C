#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//priority queue

typedef struct node {
	int key;
	char* name;
	struct node* next;
}node;

node* createNode(int key, const char* name) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->key = key;
	newNode->name = strdup(name);
	newNode->next = NULL;
	
	return newNode;
}

node* insert(node* head, int key, const char* name) {
	node* newNode = createNode(key, name);
	if (head == NULL) {
		head = newNode;
		return head;
	}
	if (key < head->key) {
		newNode->next = head;
		head = newNode;
		return head; 
	}

	
	node* curr = head;
	while (curr->next != NULL && curr->next->key <= key ) { //selama node selanjutnya masih ada dan key < key node selanjutnya
		curr = curr->next;
	}
	
	newNode->next = curr->next;
	curr->next = newNode;
	return head;
	
	
}

int main() {
	
	
	
	return 0;
}
