#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int size;
	int id;
	
	struct Node* next;
}Node;

Node* create(int size, int id) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->size = size;
	n->id = id;
	n->next = NULL;
	
	return n;
}

Node* pushTail(Node* head, int size, int id) {
	Node* n = create(size, id);
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
	if (head == NULL) {
		printf("All Success\n");
		return;
	}
	
	printf("Failed IDs: ");
	Node* curr = head;
	while (curr != NULL) {
		printf("%d", curr->id);
		if (curr->next != NULL) {
			printf(" ");
		}
		curr = curr->next;
	}
}

int main() {
	
	Node* head = NULL;
	int n;
	int b;
	scanf("%d %d", &n, &b);
	
	for (int i = 0; i < n; i++) {
		int id, size;
		scanf("%d %d", &id, &size );
		head = pushTail(head, size, id);
	}
	
	Node* failed = NULL;
	while (head != NULL && b >= 0) {
		if (b >= head->size) {
			b -= head->size;
			head = popHead(head);
		}
		else {
			failed = pushTail(failed, head->size, head->id);
			head = popHead(head);
		}
	}
	
	view(failed);
	
	
	return 0;
}
