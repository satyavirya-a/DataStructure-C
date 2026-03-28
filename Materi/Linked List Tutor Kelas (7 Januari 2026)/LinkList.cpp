#include <stdio.h>
#include <stdlib.h> //buat malloc

/*
	
	Heap = menggunakan ram kita (jadi terbatas) sampai selesai running
	Stack = dinamis

*/

typedef struct Node {
 	int value;
 	
 	Node* next;  //point (nunjuk) ke selanjutnya
 	
} Node;

//awalnya NULL karena gak nunjuk ke mana mana

Node* head = NULL; //titik nunjuk awal
Node* tail = NULL; //titik tunjuk yang akhir


//create node baru
Node* createNode(int val) {
	
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->value = val;
	newNode->next = NULL;
	
	return newNode; //tipe functionnya Node karena returnnya juga node
}

void pushHead(int val) {
	
	Node* newNode = createNode(val);
	
	//2 kondisi 
	if (head == NULL) {
		tail = head = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}
	
}

void pushTail(int val) {
	
	
	Node* newNode = createNode(val);
	tail->next = newNode;
	
	tail = newNode;
	
	
}

void view() {
	Node* curr = head; //head gak boleh pindah pindah, jadi buat pointer baru namanya curr
	
	while(curr != NULL) {
		printf("%d->", curr->value);
		curr = curr->next;
	}
	printf("NULL\n");
	
}


void popHead() {
	
	if (head == NULL) {
		printf("List nya kosong\n");
		return;
	}
	
	Node* del = head;
	head = del->next;
	if (head == NULL) tail = NULL; //kalau misalnya headnya null, tailnya juga null LIST nya hilang
	free(del);
}


void popTail() {
	
		if (head == NULL) {
			printf("List kaga ada\n");
			return;
		}
		
		if (head == tail) {
			free(head); 	// kalau free itu di ilangin
			tail = NULL; //NULL itu berarti pointer nya di kosongin
		}
	
		
		Node *curr = head;
		Node *del = NULL;
		while (curr->next != tail) { //kondisi tail itu ketika selanjutnya NULL
			curr = curr->next;
		}
		
		//udah di depan sebelum yang mau didelete
		del = curr->next;
		curr->next = del->next;
		free(del);
		
//		//ATAU
//		free(tail);
//		tail = curr;
//		tail->next = NULL;
		
}

void popMid(int val) {
	
	if (val == head->value) {
		popHead();
		return;
	}
	
	if (val == tail->value) {
		popTail();
		return;
	}
	
	
	//selain itu, iterasi biasa
	Node* curr = head;
	while (curr != NULL ) {
		curr = curr->next;
		if (curr != NULL && curr->value == val) break;
		printf("Current: %d\n", curr->value);
	}
	
	//while ini akan berhenti di SEBELUM yang mau di pop
	Node *del = curr->next;
	curr->next = curr->next->next; //lompat
	
	if (curr->next == NULL)  { //supaya kalau yang diapus 1 angka disebelum tail
		tail = curr;
	}
	
	if (curr == NULL) {
		printf("Gak ketemu\n");
		return;
	}
	
	free(del);
	
}

int main() {
	
	int array[3]; //cuma static 3 doang
	
	int * arr = (int*) malloc(3*sizeof(int)); //size of int = 4 * 3 = 12
	//(tipe data)* namaVar = (typecasting dalam pointer) malloc (size)
	//malloc itu tipe data void
	
	
	//lifo sistemnya
	pushHead(5);
	pushHead(10);
	pushHead(15);
	pushHead(20);
	
	view();
	
	popHead(); 
	
	view();
	
	
	
	free(arr); //arr bisa di free jadi dinamis
	return 0;
}
