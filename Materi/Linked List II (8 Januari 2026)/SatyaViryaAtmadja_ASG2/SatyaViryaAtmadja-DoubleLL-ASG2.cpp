#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	Node* prev;
	Node* next;
} Node;

Node* createNode(int val) {
	
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = val;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
}

Node* insertTail(Node* head, int val) {
	
	Node* newNode = createNode(val);
	
	if (head == NULL) {
		head = newNode;
		return head;
	}
	
	else {
		//kalau mau insert tail tapi gak ada ptr tail, ya harus di transverse
		//karena kita gak bisa langsung ke akhir, cari dulu node yang nextnya null
		Node* curr = head;
		while(curr->next != NULL) {
			curr = curr->next;
		}
		newNode->next = curr->next;
		newNode->prev = curr;
		curr->next = newNode;
		return head;
	}
	
	
}

Node* popbyVal(Node* head, int val) {
	
	if (head == NULL) {
		printf("list kosong, nothing to delete\n");
		return head;
	}
	
	//cuma 1 data
	if (head->next == NULL && head->data == val) {
		free(head); //setelah di free, tidak boleh diakses lagi
		return head;
	}
	
	if (head->data == val) {
		Node* del = head;
		head = head->next;
		head->prev = NULL; //bedanya dengan single ada variable prev yang harus diperhatiin juga
		free(del);
		return head;
	}
	
	Node* curr = head;
	while(curr->next != NULL && curr->next->data != val) {
		curr = curr->next;
	}
	
	//sesuai validasi di while
	if (curr->next == NULL)  {
		printf("Data tidak ditemukan\n");
		return head;
	}
	
	Node* del = curr->next;
	curr->next = del->next; //data yang sebelumnya dihubungkan ke yang sesudahnya
	if (del->next != NULL) {
		del->next->prev = curr; // data yang sesudahnya dihubungkan ke data yang sebelum dari yang mau diapus
	}
	
	free(del);
	
	return head;
}

void view(Node* head) {
	Node* curr = head;
	
	if (head == NULL) {
		printf("list kosong\n");
		return;
	}
	while (curr != NULL) {
		printf("[%d | %d (%d) | %d]", curr->prev, curr->data, curr, curr->next);
		if (curr->next != NULL) printf(" <-> ");
		curr = curr->next;
	}
	
	printf("\nhead = %d (%d)\n", head->data, head);
}

int main() {
	
	printf("Soal No 7:\n");
	Node* head7 = NULL;
	head7 = insertTail(head7, 39);
	head7 = insertTail(head7, 23);
	head7 = insertTail(head7, 1);
	head7 = insertTail(head7, 96);
	head7 = insertTail(head7, 26);
	view(head7);
	
	printf("Delete 39:\n");
	head7 = popbyVal(head7, 39);
	view(head7);
	
	
	printf("===================\n");
	printf("Soal No 8:\n");
	Node* head8 = NULL;
	head8 = insertTail(head8, 65);
	head8 = insertTail(head8, 45);
	head8 = insertTail(head8, 25);
	head8 = insertTail(head8, 67);
	head8 = insertTail(head8, 59);
	view(head8);
	
	printf("Delete 59:\n");
	head8 = popbyVal(head8, 59);
	view(head8);
	
	printf("===================\n");
	printf("Soal No 9:\n");
	Node* head9 = NULL;
	head9 = insertTail(head9, 0);
	head9 = insertTail(head9, 83);
	head9 = insertTail(head9, 72);
	head9 = insertTail(head9, 95);
	head9 = insertTail(head9, 42);
	view(head9);
	
	printf("Delete 72:\n");
	head9 = popbyVal(head9, 72);
	view(head9);

	return 0;
}
