#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
	int id;
	int t;
	
	struct Node* next;
} Node;

Node* create(int id, int t) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->id = id;
	n->t = t;
	n->next = NULL;
	
	return n;
}

Node* pushTail(Node* head, int id, int t) {
	Node* n = create(id, t);
	
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

Node* popHead(Node* head) {
	if (head == NULL) {
		return head;
	}
	
	Node* del = head;
	head = head->next;
	free(del);
	
	return head;
}

void view(Node* head) {
	Node* curr = head;
	while(curr != NULL) {
		printf("%d", curr->id);
		if (curr->next != NULL) {
			printf(" ");
		}
		curr = curr->next;
	}
}


int main() {
	
	Node* head = NULL;
	Node* hasil = NULL;
	
	int n;
	int limit;
	
	scanf("%d %d", &n, &limit);
	
	for (int i = 0; i < n; i++) {
		int id;
		int t;
		
		scanf("%d %d", &id, &t);
		head = pushTail(head, id, t);
	}
	
	view(head);
	printf("\n");
	
	while (head != NULL) {
		printf("%d curr id\n", head->id);
		if (head->t <= limit) {
			printf("%d masuk ke hasil\n", head->id);
			hasil = pushTail(hasil, head->id, 0);
			head = popHead(head);
		}
		else {
			printf("%d masuk ke head lagi\n", head->id);
			head->t -= limit;
			head = pushTail(head, head->id, head->t);
			head = popHead(head);
		}
	}
	
	view(hasil);
	
	return 0;
}
