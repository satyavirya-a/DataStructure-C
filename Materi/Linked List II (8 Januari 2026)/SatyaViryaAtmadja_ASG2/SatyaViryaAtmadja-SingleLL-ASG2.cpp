#include <stdio.h>
#include <stdlib.h>
//Single Linked List


typedef struct Node {
	int data;
	Node* next;
}Node;

Node* createNode(int val){
	
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->data = val;
	newNode->next = NULL;
	
	return newNode;
	
}

Node* pushHead(Node* head, int val) {
	
	Node* newNode = createNode(val);
	
	if (head == NULL) {
		head = newNode;
		return head;
	}
	
	else {
		newNode->next = head; //hubungkan new dengan head
		head = newNode; 	//update head jadi newNode
		return head;
	}
}

Node* popbyVal(Node* head, int val) {
	
	//list kosong
	if (head == NULL) {
		printf("List Kosong\n");
		return head;
	}
	
	//popHead
	if (val == head->data) {
		Node* del = head;
		head = head->next;
		free(del);
		return head;
	}
	
	Node* curr = head;
	while(curr->next != NULL && curr->next->data != val) {
		curr = curr->next;
	}
	
	//validasi data tidak ketemu (nilai curr adalah tail, data selanjutnya tidak ada)
	if (curr->next == NULL) { 
		printf("data tidak ditemukan\n");
		return head;
	}
	
	Node *del = curr->next; //buat variabel temp
	curr->next = del->next; //hubungkan curr dengan node setelah del
	free(del); //free
	
	return head;
}

void view(Node* head) {
	
	
	if (head == NULL) {
		printf("List Kosong\n");
		return;
	}
	
	Node* curr = head;
	while (curr != NULL ) {
		printf("[ %d (%d) | %d ]",  curr->data, curr,  curr->next);
		if (curr->next != NULL) printf("->");
		curr = curr->next;
	}
	
	printf("\nhead = %d (%d)\n\n", head->data, head);
	
}

int main() {
	
	printf("Soal No 1:\n");
	Node* head1 = NULL;
	
	head1 = pushHead(head1, 81);
	head1 = pushHead(head1, 42);
	head1 = pushHead(head1, 62);
	head1 = pushHead(head1, 13);
	head1 = pushHead(head1, 67);
	view(head1);

	
	printf("Delete 81\n");
	head1 = popbyVal(head1, 81);
	view(head1);
	
	printf("=============================================\n");
	printf("Soal No 2:\n");
	Node* head2 = NULL;
	head2 = pushHead(head2, 23);
	head2 = pushHead(head2, 65);
	head2 = pushHead(head2, 25);
	head2 = pushHead(head2, 60);
	head2 = pushHead(head2, 0);
	view(head2);

	
	
	printf("Delete 25\n");
	head2 = popbyVal(head2, 25);
	view(head2);

	return 0;
}
