#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	Node* prev;
	Node* next;
}Node;

Node* createNode(int val) {
	
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->data = val;
	newNode->prev = NULL;
	newNode->next = NULL;
	
	return newNode;
}

Node* insertTail(Node* tail, int val) {
	
	Node* newNode = createNode(val);
	
	if (tail == NULL) {
		tail = newNode;
		tail->next = newNode;
		tail->prev = newNode;
		return tail;
	}
	
	newNode->prev = tail;
	newNode->next = tail->next;
	tail->next->prev = newNode;
	tail->next = newNode;
	tail = newNode;
	return tail;
	
}

Node* insertHead(Node* tail, int val) {
	
	if (tail == NULL) {
		tail = insertTail(tail, val);
		return tail;
	}
	
	Node* temp = createNode(val);
	temp->next = tail->next;
	temp->prev = tail;
	tail->next->prev = temp;
	tail->next = temp;
	return tail;
}

Node* insertByPos(Node* tail, int val, int pos) {
	
	if (tail == NULL) {
		tail = insertTail(tail, val);
		return tail;
	}
	
	if (pos == 1) {
		Node* temp = createNode(val);
		temp->next = tail->next;
		temp->prev = tail;
		tail->next->prev = temp;
		tail->next = temp; //ganti posisi selalu terakhir
		return tail;
	}
	
	else {
		Node* temp = createNode(val);
		Node* curr = tail->next;
		int count = 1;
		while(curr != tail && count < pos) {
//			printf("curr: %d\n", curr->data);
			count++;
			curr = curr->next;
		}
//		printf("curr sekarang: %d\n", curr->data);


		if (count < pos) {
			printf("posisi melebihi panjang list\n");
			return 0;
		}
		//GAK BOLEH KEBALIK
		temp->next = curr; // hubungkan new ke data (yang posisi yang dimau) 
		temp->prev = curr->prev; //hubungkan new ke data sebelum
		curr->prev->next = temp; //ganti hubungan data sebelum ke temp
		curr->prev = temp; //mengganti posisi temp jadi sebelum curr
		
		return tail;
	}
	
	
	
}


Node* popByVal(Node* tail, int val) {
	
	if (tail == NULL) {
		printf("List kosong\n");
		return tail;
	}
	
	if (tail->next == tail && tail->data == val) {
		free(tail);
		return tail;
	}
	
	
	//popTail
	if (tail->data == val) {
		Node* del = tail;
		tail->prev->next = tail->next;
		tail->next->prev = tail->prev;
		tail = tail->prev;
		free(del);
		return tail;
	}
	
	
	Node* curr = tail->next;
	do {
		curr = curr->next;
	} while(curr != tail->next && curr->data != val);
	
	if (curr->data != val) {
		printf("Data tidak ditemukan\n");
		return tail;
	}
	Node* del = curr;
	curr->prev->next = del->next;
	curr->next->prev = del->prev;
	free(del);
	return tail;
	
}

void view(Node* tail) {
	
	if (tail == NULL) {
		printf("List Kosong\n");
		return;
	}
	
	Node* curr = tail->next;
	do {
		printf("[%d | %d (%d) | %d]", curr->prev, curr->data, curr, curr->next);
		if (curr->next != tail->next) printf(" <-> ");
		curr = curr->next;
	} while(curr != tail->next);
	
	printf("\ntail = %d (%d)\n", tail->data, tail);
	
}

int main() {
	
	printf("Soal 10:\n");
	Node* tail10 = NULL;
	tail10 = insertTail(tail10, 33);
	tail10 = insertTail(tail10, 3);
	tail10 = insertTail(tail10, 5);
	tail10 = insertTail(tail10, 81);
	view(tail10);
	
	printf("\nInsert 85 ke posisi 3:\n");
	tail10 = insertByPos(tail10, 85, 3);
	view(tail10);
	
	printf("==========================\n");
	printf("Soal 11:\n");
	Node* tail11 = NULL;
	tail11 = insertTail(tail11, 84);
	tail11 = insertTail(tail11, 26);
	tail11 = insertTail(tail11, 92);
	tail11 = insertTail(tail11, 57);
	view(tail11);
	
	printf("\nInsert 80 ke posisi akhir:\n");
	tail11 = insertTail(tail11, 80);
	view(tail11);
	
	printf("==========================\n");
	printf("Soal 12:\n");
	Node* tail12 = NULL;
	tail12 = insertTail(tail12, 31);
	tail12 = insertTail(tail12, 18);
	tail12 = insertTail(tail12, 24);
	tail12 = insertTail(tail12, 65);
	view(tail12);
	
	printf("\nInsert 63 ke posisi awal:\n");
	tail12 = insertHead(tail12, 63);
	view(tail12);
	
	printf("=============================\n");
	printf("Soal 13:\n");
	Node* tail13 = NULL;
	tail13 = insertTail(tail13, 59);
	tail13 = insertTail(tail13, 68);
	tail13 = insertTail(tail13, 76);
	tail13 = insertTail(tail13, 37);
	tail13 = insertTail(tail13, 34);
	view(tail13);
	
	printf("\nDelete 59:\n");
	tail13 = popByVal(tail13, 59);
	view(tail13);
	
	printf("=============================\n");
	printf("Soal 14:\n");
	Node* tail14 = NULL;
	tail14 = insertTail(tail14, 48);
	tail14 = insertTail(tail14, 39);
	tail14 = insertTail(tail14, 29);
	tail14 = insertTail(tail14, 58);
	tail14 = insertTail(tail14, 95);
	view(tail14);
	
	printf("\nDelete 95:\n");
	tail14 = popByVal(tail14, 95);
	view(tail14);
	
	printf("=============================\n");
	printf("Soal 15:\n");
	Node* tail15 = NULL;
	tail15 = insertTail(tail15, 22);
	tail15 = insertTail(tail15, 39);
	tail15 = insertTail(tail15, 56);
	tail15 = insertTail(tail15, 50);
	tail15 = insertTail(tail15, 12);
	view(tail15);
	
	printf("\nDelete 50:\n");
	tail15 = popByVal(tail15, 50);
	view(tail15);
	
	return 0;
}
