#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	
	int data;
	Node* next;
	
}Node;

Node* createNode(int val) {
	
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->data = val;
	newNode->next = NULL;
	
	return newNode;
}

Node* insertTail(Node* tail, int val) {
	
	Node* temp = createNode(val);
	
	if (tail == NULL) {
		tail = temp;
		temp->next = temp; //menunjuk ke diri sendiri
		return tail;
	}
	
	else {
		temp->next = tail->next; //hubungkan temp dengan tail->next
		tail->next = temp; //hubungkan tail dengan temp
		tail = temp; // update tail jadi temp
		return tail;
	}
	
}

Node* insertMidbyPos(Node* tail, int val , int pos) {
	
	Node* temp = createNode(val);
	
	//list kosong, ya insert biasa
	if (tail == NULL) {
		tail = insertTail(tail, val);
		return tail;
	}
	 
	//insert dihead
	if (pos == 1) {
		temp->next = tail->next;
		tail->next = temp;
		return tail;
	}
	
	int count = 1;
	Node* curr = tail->next;
	while (count < pos - 1 && curr != tail) {
		count++;
		curr = curr->next;
	}
	
	//udah 1 puteran, tapi count masih dibawah posisi yang diminta
	if (count < pos - 1) {
		printf("Posisi melebihi panjang list\n");
		return tail;
	}
	
	temp->next = curr->next;
	curr->next = temp;
	return tail;
	
}

Node* popbyVal(Node* tail, int val) { //iterasinya sampai curr aja tapi harus buat pointer prev
//supaya lebih intuitif
	
	//list kosong
	if (tail == NULL) {
		printf("List Kosong\n");
		return tail;
	}
	
	//list cuma 1
	if (tail->next == tail && tail->data == val) {
		free(tail);
		tail = NULL;
		return tail;
	}
	
	//pop head
	if (tail->next->data == val) {
		Node* del = tail->next;
		tail->next = del->next;
		free(del);
		return tail;
	}
	

	//CARI NODE TARGET (curr), 1 PUTARAN DOANG
	Node* curr = tail->next;
	Node* prev = tail;
	do {
//		printf("curr: %d\n", curr->data);
		if (curr->data == val) {
			break;
		}
		
		prev = curr;
		curr = curr->next;
	} while (curr != tail->next);
	//kenapa curr != tail->next karena kita mau lihat sebelum terakhir doang gak nyampe akhir kaya looping view
	
//	printf("curr: %d\n", curr->data);
	
	//validasi tidak ketemu (ketika sudah 1 putaran
	if (curr == tail->next && curr->data != val) {
		printf("Value tidak ditemukan\n");
		return tail;
	}
	
	//kalau ternyata tail yang mau dipop
	if (curr == tail) {
		Node* del = curr;
		prev->next = curr->next; //hubungkan node sebelum tail ke setelah tail
		tail = prev; //ganti tail jadi node dibelakang tail
		free(del);
		return tail;
	}
	
	Node* del = curr;
	prev->next = curr->next; //hubungkan node sebelum dengan sesudah
	free(del);
	
	return tail;
}

void view(Node* tail)  {
	
	if (tail == NULL) {
		printf("List Kosong\n");
		return;
	}
	
	Node* curr = tail->next;
	do {
		printf("[%d (%d) | %d]", curr->data, curr, curr->next);
		if (curr->next != tail->next) printf(" -> ");
		curr = curr->next;
	}
	while (curr != tail->next); 
	
	
	printf("\ntail = %d (%d)\n", tail->data, tail);
	
}

int main() {
	
	printf("Soal No 3:\n");

	Node* tail3 = NULL;
	tail3 = insertTail(tail3, 1);
	tail3 = insertTail(tail3, 84);
	tail3 = insertTail(tail3, 55);
	tail3 = insertTail(tail3, 19);
	tail3 = insertTail(tail3, 68);
	view(tail3);
	
	
	printf("\n\nInsert 17 ke posisi 4:\n");
	tail3 = insertMidbyPos(tail3, 17, 4);
	view(tail3);
	
	printf("\n=========================\n");
	printf("Soal No 4:\n");
	Node* tail4 = NULL;
	tail4 = insertTail(tail4, 2);
	tail4 = insertTail(tail4, 13);
	tail4 = insertTail(tail4, 35);
	tail4 = insertTail(tail4, 63);
	tail4 = insertTail(tail4, 75);
	view(tail4);

	
	printf("\n\nDelete 2:\n");
	tail4 = popbyVal(tail4, 2);
	
	view(tail4);

	printf("\n=========================\n");
	printf("Soal No 5:\n");
	Node* tail5 = NULL;
	tail5 = insertTail(tail5, 59);
	tail5 = insertTail(tail5, 31);
	tail5 = insertTail(tail5, 89);
	tail5 = insertTail(tail5, 73);
	tail5 = insertTail(tail5, 95);
	view(tail5);

	
	printf("\n\nDelete 95:\n");
	tail5 = popbyVal(tail5, 95);
	
	view(tail5);

	printf("\n=========================\n");
	printf("Soal No 6:\n");
	Node* tail6 = NULL;
	tail6 = insertTail(tail6, 34);
	tail6 = insertTail(tail6, 33);
	tail6 = insertTail(tail6, 96);
	tail6 = insertTail(tail6, 47);
	tail6 = insertTail(tail6, 57);
	view(tail6);

	
	printf("\n\nDelete 33:\n");
	tail6 = popbyVal(tail6, 33);
	
	view(tail6);

	
	
	return 0;
}
