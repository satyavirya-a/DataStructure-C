#include <stdio.h>
#include <stdlib.h>

//CSLL
//circular itu intinya setelah tail balik ke awal

//waktu push head
//node yang awal itu newNode->next = newNode

//kalau circular single pake tail itu lebih enak karena bisa akses akhir sama head (tail->next)
typedef struct Node {
	int data;
	struct Node* next;
}Node;

Node* createNode(int val ) {
	Node* newNode = (Node* ) malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->data = val;
	
	return newNode;
}

Node* pushHead(Node* tail, int val) {
	Node* newNode = createNode(val);
	
	if (tail == NULL) {
		tail = newNode;
		tail->next = tail; //ini yang buat jadi circular
		//ini pertama kali doang
	}
	else {
		//cari dulu di
		newNode->next = tail->next; //hubungin newNode di depan tail->next (head)
		tail->next = newNode; //head jadi newNode (yang berubah)
		
		
	}
}

Node* pushTail(Node* tail, int val) {
	
	if (tail == NULL) {
		tail = pushHead(tail, val);
		return tail;
	}
	
	else {
		Node* newNode = createNode(val); 
		newNode->next = tail->next; //hubungin newNode ke head
		tail->next = newNode; //hubungin tail yang lama ke newNode
		tail = newNode; //update tail jadi yang baru
		return tail;
	}
}

//push mid ada 2
//by value (di urutin)
//by pos (1 based)

Node* pushByVal(Node* tail, int val) {
	
	
	if (tail == NULL || val <= tail->next->data) {
		tail = pushHead(tail, val);
		return tail;
	}
	
	else if (val >= tail->data) {
		tail = pushTail(tail, val);
		return tail;
	}
	
	Node* newNode = createNode(val);
	
	Node* curr = tail->next;
	
	//perlu stop di node sebelumnya (value <= val)
	//validasi curr->next itu udah di sebelumnya
	while (curr != tail && val > curr->next->data ) { //jika curr == tail udah selesai transver
					//selama input value > data next 
		curr = curr->next;
	}
	
	//SELALU MULAI HUBUNGIN NEWNODE DULLU
	//hubungin newNode ke curr next dulu
	newNode->next = curr->next;
	curr->next = newNode;
	
	return tail;
		

}


//pos--; itu karena kita udah di satu ceritanya
Node* pushByPos(Node* tail, int val, int pos) {
	//mending pake count aja 
	
	if (pos < 1) {
		printf("Posisi tidak valid");
		return tail;
	}
	
	if (tail == NULL || pos == 1) {
		tail = pushHead(tail, val);
		return tail;
	}
	
	
	int count = 1; //starting position nya 1 (di node 1)
	Node* curr = tail->next;
	//pos yang dimau
	//count itu harus pos - 1 ( 1 sebelum pos )
	//curr == tail itu berarti udah yang terakhir 
	while (curr != tail && count != pos - 1) {
		count++;
		curr = curr->next;
	}
	
	
	//ini berarti ukuran kurang banyak
	if (curr == tail && count != pos - 1) {
		printf("Ukuran kurang anjir\n");
		return tail;
	}
	
	//ini diterakhir 
	if (curr == tail && count == pos - 1) {
		tail = pushTail(tail, val);
		return tail;
	}
	
	Node* newNode = createNode(val);
	newNode->next = curr->next;
	curr->next = newNode;
	return tail;
	
}

Node* popHead(Node* tail) {
	
	if (tail == NULL) {
		printf("List Kosong\n");
		return tail;
	}
	
	Node* del = tail->next;
	tail->next = tail->next->next;
	free(del);
	
	return tail;
}

Node* popTail(Node* tail) {
	if (tail == NULL) {
		printf("List Kosong\n");
		return tail;
	}
	
	//transverse dulu sampai curr->next == tail
	Node* del = tail->next;
	Node* curr = NULL;
	while (del != tail) {
		curr = del;
		del = del->next;
	}
	
	curr->next = del->next;
	free(del);
	tail = curr;
//	curr->next = tail->next;
//	tail = curr;
//	free(curr->next);
	return tail;
}

Node* popByVal(Node* tail, int val) {
	if (tail ==NULL) {
		printf("List Kosong");
		return tail;
	}
	
	if (tail->data == val) {
		tail = popTail(tail);
		return tail;
	}
	
	if (tail->next->data == val) {
		tail = popHead(tail);
		return tail;
	}
	
	//transverse sampai ke sebelum nilai
	Node* curr = tail->next;
	while(curr != tail && curr->next->data != val) {
		curr = curr->next;
		
	}
	
	// kalau gak nemu
	if (curr == tail && val != tail->data) {
		printf("Value gak ketemu\n");
		return tail;
	}
	
	Node* del = curr->next;
	curr->next = del->next;
	
	//kasih kondisi 
	free(del);
	return tail;
	
}

Node* popByPos(Node* tail, int pos) {
	
	//cek kosong
	if (tail == NULL) {
		printf("List nya kosong\n");
		return tail;
	}
	
	if (pos < 1) {
		printf("Input invalid\n");
		return tail;
	}
	
	//cek ujung ujungnya
	if (pos == 1) {
		tail = popHead(tail);
		return tail;
	}
	
	//transverse
	int count = 1; //posisi awal 1
	Node* curr = tail->next;
	while (curr != tail && count != pos - 1) {
		count++;
		curr = curr->next;
	}
	
	if (curr == tail  && count != pos -1) {
		printf("tidak ada node\n");
		return tail;
	}
	
	if (curr == tail && count == pos -1) {
		tail = popTail(tail);
		return tail;
	}
	
	Node* del = curr->next;
	curr->next = del->next;
	free(del);
	
	return tail;
}

void view(Node* tail) {
	Node* curr = tail->next;
	
	//jadi mulai ngejalanin dulu sekali
	do {
		printf("%d", curr->data);
		if (curr->next != tail->next) printf(" -> ");
		curr = curr->next;
	} while(curr != tail->next);
	printf("\ntail->next = %d\n", tail->next->data);
	printf("\n");
	
	//ada juga yang loopingnya sampe sebelum akhir
	//trus di bawah looping baru print tail
	
	//atau pakai while
	
//	while (curr != tail) {
//		printf("%d -> ", curr->data);
//	}
	//
	
	

}


int main() {
	
	Node* tail = NULL;
	tail = pushHead(tail, 5);
	tail = pushHead(tail, 4);
	tail = pushHead(tail, 3);
	view(tail);
	
	tail = pushTail(tail, 10);
	tail = pushTail(tail, 20);
	view(tail);
	
	tail = pushByVal(tail, 7);
	view(tail);
	
	tail = pushByPos(tail, 20, 3);
	view(tail);
	
	
	tail = popByPos(tail, 7);
	view(tail);
	
//	tail = popByVal(tail, 7);
//	view(tail);
	
	
	return 0;
}
