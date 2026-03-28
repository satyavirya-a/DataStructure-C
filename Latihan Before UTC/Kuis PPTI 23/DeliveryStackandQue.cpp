#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int id;
	int w;
	int isNotHome;
	
	struct Node* next;
}Node;

Node* create(int id, int w) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->id = id;
	n->w = w;
	n->isNotHome = 0;
	
	n->next = NULL;
	
	return n;
}

Node* pushTail(Node* head, int id, int w) {
	Node* n = create(id, w);
	
	if (head == NULL) {
		head = n;
		return head;
	}
	
	Node* curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = n;
	return head;
	
}

//buat headNotHome
Node* pushHead(Node* head, int id, int w) {
	Node* n = create(id, w);
	if (head == NULL) {
		head = n;
		return head;
	}
	
	n->next = head;
	head = n;
	
	return head;
	
}

Node* popHead(Node* head) {
	if (head == NULL) {
		return head;
	}
	
	if (head->next == NULL) {
		Node* del = head;
		head = NULL;
		free(del);
		return head;
	}
	
	Node* del = head;
	head = head->next;
	free(del);
	
	return head;
}



void ubahisNotHomae(Node* head, int id) {
	Node* curr = head;
	while (curr != NULL) {
		if (curr->id == id) {
			curr->isNotHome = 1;
			printf("%d is change to not home %d\n", curr->id, curr->isNotHome);
		}
		curr = curr->next;
	}
}
void print(Node* head) {
	Node* curr = head;
	while (curr != NULL) {
		printf("%d", curr->id);
		if (curr->next != NULL) {
			printf(" ");
		}
		curr = curr->next;
	}
	printf("\n");
}
//void printStack(Node* head) {
//	if (head == NULL) {
//		return;
//	}
//	
//	print(head->next);
//	if (head->next == NULL) {
//		printf("%d", curr->id);
//	}
//	else {
//		printf(" %d", curr->id);
//	}
//	
//}





int main() {
	int t;
	int m;
	Node* head = NULL;
	Node* headNotHome = NULL;
	
	scanf("%d %d", &t, &m);
	
	for (int i =0; i < t; i++) {
		int p, w;
		scanf("%d %d", &p, &w);
		head = pushTail(head, p, w);
	}
	
	int u;
	scanf("%d", &u);
	
	for (int i = 0; i < u; i++) {
		int p;
		scanf("%d", &p);
		
		ubahisNotHomae(head,p);
		
	}
	
	Node* curr = head;
	while (curr != NULL) {
		if (curr->isNotHome == 1) {
			printf("%d is not home\n", curr->id);
			headNotHome = pushHead(headNotHome, curr->id, curr->id);
			head = popHead(head);
		}
		
		else {
			printf("%d isNotHome var curr %d\n", curr->id, curr->isNotHome);
			if (curr->w < m) {
				m -= curr->w;
				head = popHead(head);
			}
			else if (curr->w > m) {
				break;
			}
			
		}
		curr = curr->next;
	}
	
	print(head);
	print(headNotHome);
	
}
