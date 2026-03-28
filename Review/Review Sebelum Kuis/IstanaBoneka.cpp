#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char* name;
	int status;
	struct node* next;
	struct node* prev;
}node;

node* createNode(const char* name, int status) {
	node* n = (node*)malloc(sizeof(node));
	n->name = strdup(name);
	n->status = status;
	n->next = NULL;
	n->prev = NULL;
	
	return n;
}

node* regist(node* head, const char* name, int status) {
	node* newNode = createNode(name, status);
	if (head == NULL) {
		head = newNode;
		return head;
	}
	
	if (status > head->status) {
		newNode->next = head;
		head->prev = newNode;
		head = head->next;
		return head;
	}
	
	node* curr = head;
	while (curr->next != NULL && curr->status >= status) {
		curr = curr->next;
	}
	
	newNode->next = curr->next;
	newNode->prev = curr;
	if (curr->next != NULL) {
		curr->next->prev = newNode;
	}
	curr->next = newNode;
	
	return head;
	
	
}

void view(node* head) {
	if (head == NULL) {
		printf("list kosong\n");
		return;
	}
	node* curr = head;
	while (curr != NULL) {
		printf("%s ", curr->name);
		if (curr->status == 1) {
			printf("FAST_TRACK\n");
		}
		else if (curr->status == 0) {
			printf("REGULER\n");
		}
		curr = curr->next;
	}
}



int main() {
	
	char line[100];
	char comm[50];
	node* head = NULL;
	int n;
	scanf("%[^\n]", line ); getchar();
	sscanf(line, "%s %d", comm, &n);
	
//	printf("%s %d\n", comm, n );


		
	if (strcmp(comm, "REGISTER") == 0) {
		for (int i =0; i < n; i++) {
			char line2[100];
			char name[100];
			char stat[100];
			int status;
			scanf("%[^\n]", line2); getchar();
			sscanf(line2, "%s %s", name, stat );
			if (strcmp(stat, "FAST_TRACK") == 0) {
				status = 1;
			}
			else {
				status = 0;
			}
			head = regist(head, name, status);
		}
		
	}
	
	
	view(head);
	
	
	
	return 0;
}
