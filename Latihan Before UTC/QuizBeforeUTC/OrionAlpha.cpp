#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char* name;
	int fuel;
	int status;
	struct node* next;
}node;

node* createNode(const char* name, int fuel, int status) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->next = NULL;
	newNode->name = strdup(name);
	newNode->fuel = fuel;
	newNode->status = status;
	
	return newNode;
}

node* head = NULL;

void enqueue(const char* name, int fuel, int status) {
	
	node* newNode = createNode(name, fuel, status);
	if (head == NULL ) {
		head = newNode;
		return;
	}
	
	if (status >= head->status) {
		newNode->next = head;
		head = newNode;
		return;
	}
	
	//kalau gak null,
	node* curr = head;
	//cek dair status dulu, kalau lebih besar, stop
	while (curr->next != NULL) {
//		while (status <= curr->next->status) {
//			printf("curr = %s\n", curr->name);
//			curr = curr->next;
//		}

		if (status >= curr->next->status) {
			if (fuel <= curr->next->fuel) {
				break;
			}
		}
	
//		while (fuel >= curr->next->fuel) {
////			printf("curr = %s\n", curr->name);
//			curr = curr->next;
//		}
		
		curr = curr->next;
	}
	
	
	newNode->next = curr->next;
	curr->next = newNode;
	
	
	
	
}

void dequeue() {
	
	if (head == NULL) {
		printf("List Kosong\n");
		return;
	}
	
	node* del = head;
	head = head->next;
	free(del->name);
	free(del);
	
}

void view() {
	node* curr = head;
	while (curr != NULL) {
		printf("%s -> ", curr->name);
		curr = curr->next;
	}
	printf("NULL\n\n");
}



int main() {
	
	int n;
//	scanf("%d", &n); getchar();
	char name[100];
	int fuel;
	int status;
//	for (int i =0 ; i < n; i++) {
//		scanf("enqueue(%s, %d, %d)", name, &fuel, &status); getchar();
//		enqueue(name, fuel, status);
//	}

	enqueue("Apollo", 75, 0);
	enqueue("Voyager", 50, 0);
	enqueue("Odyssey", 90, 1);
	enqueue("Endeavour", 15, 0);
	enqueue("Pioneer", 80, 1);

	
	printf("Docking Order:\n");
	view();
	
	dequeue();
	
	printf("Docking Order After Dequeue:\n");
	view();
	
	return 0;
}
