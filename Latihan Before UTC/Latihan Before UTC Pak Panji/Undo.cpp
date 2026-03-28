#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char* str;
	
	struct Node* next;
}Node;

Node* create(const char* str) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->str = strdup(str);
	n->next = NULL;
	
	return n;
}

Node* pushHead(Node* head, const char* str) {
	Node* n = create(str);
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
	
	Node* del = head;
	head = head->next;
	free(del->str);
	free(del);
	
	return head;
}


void view(Node* head) {
	if (head == NULL) {
		return;
	}
//	Node* curr = head;
//	while (curr != NULL) {
//		printf("%s", curr->str);
//		if (curr->next != NULL) {
//			printf(" ");
//		}
//		curr = curr->next;
//	}
	
	//ini berarti node paling terakhir tapi seharusnya ke print pertama
	if (head->next == NULL) {
		printf("%s", head->str);
		return;
	}

	view(head->next);
	printf(" %s", head->str);
	
}


Node* freeAll(Node* head) {
	Node* curr = head;
	while (curr != NULL) {
		Node* del = curr;
		curr = curr->next;
		free(del->str);
		free(del);
	}
	
	return NULL;
}

int main() {
	
	int n;
	Node* main = NULL;
	Node* temp = NULL;
	
	scanf("%d", &n); getchar();
	
	
	
	for (int i =0 ; i < n; i++) {
		char com[100];
		scanf("%s", com);
		if (strcmp(com, "UNDO") == 0) {
			if (main == NULL) {
				continue;
			}
//			temp = pushHead(temp, main->str); //TAMBAHAN REDO
			main = popHead(main);
		}
		
		else if (strcmp(com, "TYPE") == 0) {
//			if (temp != NULL) {
//				temp = freeAll(temp); 	//TAMBAHAN REDO
//			}
			
			char str[100];
			
			scanf("%s", str);
			main = pushHead(main, str);
			
		}
//		else if (strcmp(com, "REDO") == 0) { //TAMBAHAN REDO
//			if (temp == NULL) {
//				continue;
//			}
//			main = pushHead(main, temp->str);
//			temp = popHead(temp);
//		}
		else {
			printf("Command Salah!");
		}
	}
	
	if (main == NULL) {
		printf("Editor Kosong\n");
	}
	else {
		view(main);
		printf("\n");
	}
	
	
	
	
	
	
	
	return 0;
}
