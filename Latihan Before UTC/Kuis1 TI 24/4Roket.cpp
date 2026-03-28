#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//fifo -> queue
typedef struct node {
	int id;
	int req;
	struct node* next;
}node;

node* createNode(int id, int req) {
	node* n = (node*)malloc(sizeof(node));
	n->id = id;
	n->req = req;
	n->next = NULL;
	
	return n;
}

node* insert(node* head, int id, int req) {
	node* n = createNode(id, req);
	
	if (head == NULL) {
		head = n;
		return head;
	}
	
	node* curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	
	n->next = curr->next;
	curr->next = n;
	return head;
	
}

//di proses dari head -> popHead

void view(node* head) {
	if (head == NULL) {
		return;
	}
	node* curr = head;
	while (curr != NULL) {
		printf("%d -> ", curr->id);
		curr = curr->next;
	}
	
}

node* pop(node* head) {
	if (head == NULL) {
		return head;
	}
	
	node* del = head;
	head = head->next;
	free(del);
	return head;
}

int isAda(node* head, int awal) {
	while (head != NULL && awal >= 0) {
		if (awal >= head->req) {
			awal -= head->req;
			return 1;

		}
		else {
			break;
		}
		
	}
	return 0;
	
}

void result(node* head, int awal) {

	while (head != NULL && awal >= 0) {
		if (awal >= head->req) {
			printf("%d ", head->id);
			awal -= head->req;
//			printf("sisa %d\n", awal);
			
			head = pop(head);

		}
		else {
			head = pop(head);
		}
	}
	
}



int main() {
	
	int awal;
	int n;
	node* head = NULL;
	
	scanf("%d %d", &n, &awal);
	
	for (int i =0 ; i < n; i++) {
		int id;
		int req;
		scanf("%d %d", &id, &req);
		head = insert(head, id, req);
	}
	
//	view(head);
//	if (result(head, awal) == 0) {
//		printf("Fail All\n");
//		return 0;
//	}
	if (isAda(head, awal) == 1) {
		result(head, awal);
	}
	else if (isAda(head, awal) == 0) {
		printf("Fail All\n");
	}
	
	
	
	return 0;
}
