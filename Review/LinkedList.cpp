#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int data;
	char* name;
	node* next;
}node;

node* createNode(char* name, int data) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->name = strdup(name);
	newNode->data = data;
	newNode->next = NULL;
	
	return newNode;
}

node* pushHead(node* head, char* name, int data) {
	
	node* newNode = createNode(name, data);
	
	if (head == NULL) {
		head = newNode;
		return head;
	}
	
	newNode->next = head;
	head = newNode;
	return head;

}

node* pushTail(node* head, char* name, int data) {
	
	node* newNode = createNode(name, data);
	
	if (head == NULL) {
		head = newNode;
		return head;
	}
	
	node* curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	
	curr->next = newNode;
	return head;
	
	
}

node* pushMidbypos(node* head, int pos, char* name, int data) {
	
	node* newNode = createNode(name, data);
	
	if (head == NULL) {
		head = newNode;
		return head;
	}
	
	if (pos == 1) {
		head = pushHead(head, name, data);
		return head;
	}
	
	node* curr = head;
	int i = 0;
	while (curr->next != NULL && i < pos - 2 ) {
		i++;
		curr = curr->next;
	}
	newNode->next = curr->next;
	curr->next = newNode;
	
	return head;
	
}

node* popHead(node* head) {
	if (head == NULL) {
		return NULL;
	}
	
	node* del = head;
	head = head->next;
	free(del->name);
	free(del);
	return head;
}

/*

Cek apakah list kosong?

Cek apakah isinya cuma 1 node (kode barusan)?

Jika bukan keduanya, jalankan logika prev dan curr untuk menghapus node terakhir (kode sebelumnya).

*/
node* popTail(node* head) {
	if (head == NULL) {
		return NULL;
	}
	
	if (head->next == NULL) {
		node* del = head;
		free(del->name);
		free(del);
		head = NULL;
		return(head);
		
	}
	
	node* curr = head;
	node* prev = NULL;
	while(curr->next != NULL) {
		prev = curr;
		curr = curr->next;
	}
	
	prev->next = NULL;
	free(curr->name);
	free(curr);
	return head;
}

node* popbyVal(node* head, int val) {
	
	if (head == NULL) {
		return NULL;
	}
	
	
	if (head->data == val) {
		head = popHead(head);
		return head;
	}
	
	node* curr = head;
	while (curr->next != NULL && curr->next->data != val) {
		curr = curr->next;
	}
	
	if (curr->next == NULL && curr->data != val) {
		printf("Data tidak ada");
		return head;
	}
	node* del = curr->next;

	curr->next = del->next;
	
	free(del->name);
	free(del);
	
	return head;

}


int main() {
	
	
	return 0;
}


