/*
Tipe linked list:
	Single Linked List (Navigasi kedepan)
	Doubly Linked List (bisa ke depan dan kebelakang)
	Circular linked List (Single and Double) (last element nunjuk ke depan lagi [gak ada yang null])
					Single : satu arah doang
					Double : bisa kebelakang 2 arah

- Array:
Element

- Linked List:
Node (data dan link)
Head (pintu masuk untuk masuk ke data)
	Single: cuma masuk lewat head

Linked List dibagi tiap fungsi:
- Insert : Front, End, Mid
- Delete : Pront, End, Mid
- Display : Show All data
- Seek (Stack mencari data paling atas, Queque mencari data yang terluar) : lihat data yang terluar

*/

//Pak Panji pake Replit
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;




Node* createNode(int val) {
	
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->data = val;
	newNode->next = NULL;
	
	return newNode;
}

//last in, first out (lifo)
//Node* insertFront(Node **head, int val) { //harus pakai pointer to pointer supaya keupdate headnya kalau mau langsung
//	
//
//	if (*head == NULL) {
//		*head = createNode(val);
//		return *head;
//	}
//	else {
//		Node* newNode = createNode(val);
//		newNode->next = *head;	//sambungin new node ke head yang lama
//		*head = newNode; //!! penting !! selalu update head to new node
//		return *head;
//	}
//}

Node* insertFront(Node *head, int val) { //kalau mau assign ke head lagi ya gak papa
	

	if (head == NULL) {
		head = createNode(val);
		return head;
	}
	else {
		Node* newNode = createNode(val);
		newNode->next = head;	//sambungin new node ke head yang lama
		head = newNode; //!! penting !! selalu update head to new node
		return head;
	}
}

//first in, first out (fifo)
Node* insertEnd(Node *head, int val) {
	
	//buat node yang mau dimasukin
	Node *newNode = createNode(val);
	
	if (head == NULL) {
		head = newNode;
		return head;
	}
	
	//transversing dulu sampai ketemu yang next null (tail)
	Node *curr = head;
	while(curr->next != NULL) {
		curr = curr->next;
	}
	//berarti sekarang posisinya udah di tail nih
	curr->next = newNode; //link to new node at the end
	return head;

}

Node* insertMid(Node *head, int val, int pos) {
	
	Node* newNode = createNode(val);
	
	if (head == NULL) {
		head = newNode;
		return head;
	}
	
	if (pos == 1 ) {
		head = insertFront(head, val);
		return head;
	}
	
	Node *curr = head;
	pos--; //karena kita mau menuju 1 node sebelum posisi yang mau di add
	while (curr != NULL && pos != 1) { //pos != 1 itu karena kita mau sisain 1 jarak dengan target posisi yang mau ditaruh
		pos--;
		curr = curr->next;
		
	}
	
	if (curr == NULL) {
		printf("Posisi tidak ditemukan\n");
		return head;
	}
	
	newNode->next = curr->next;
	curr->next = newNode;
	
	
	return head;
}


Node* deleteFront(Node* head) {
	
	if (head == NULL) {
		printf("List Kosong tidak bisa di print");
		return head;
	}
	
	else {
		Node* del = head;
		head = head->next;
		free(del);
		return head;
	}
}

Node* deleteEnd(Node* head) {
	if (head == NULL) {
		printf("List Kosong tidak bisa di delete\n");
		return head;
	}
	
	else {
		Node* curr = head;
		while (curr->next->next != NULL) { //berhenti sampai 1 node sebelum tail
//			printf("current: %d\n", curr->data);
			curr = curr->next;
		}
//		printf("curr %d\n", curr->data);
		Node* del = curr->next;
		free(del);
		curr->next = NULL; //harus di NULL in agar bisa kosongin pointer & kebaca itu akhirnya
		return head;
	}
	
}

Node* deleteMidbyPos(Node* head, int pos) {
	if (head == NULL) {
		printf("List Kosong tidak bisa di delete\n");
	}
	
	if (pos == 1) {
		head = deleteFront(head);
		return head;
	}
	
	else {
		pos--; //supaya berhenti di pos -1
		Node* curr = head;
		while (curr->next != NULL && pos != 1) { //kalau insert di setelah akhir bisa, tapi kalau delete setelah akhir mana bisa
				//makanya ini curr->next beda dengan insert
			pos--;
			curr = curr->next;
		}
		if (curr->next == NULL ) {
			printf("posisi melebihi size\n");
			return head;
		}
//		printf("curr %d\n",curr->data );
		Node* del = curr->next;
		curr->next = del->next;
		free(del);
		

		return head;
	}
}

Node* deleteMidbyVal(Node* head, int val) {
	if (head == NULL) {
		printf("List Kosong tidak bisa di delete\n");
	}
	
	if (val == head->data) {
		head = deleteFront(head);
		return head;
	}
	
	else {
		Node* curr = head;
		while (curr->next != NULL && curr->next->data != val) { //berhenti di 1 node sebelum data yang mau dihapus
			curr = curr->next;
		}
		
		if (curr->next == NULL) {
			printf("value tidak ada\n");
			return head;
		}
		else {
			Node* del = curr->next;
			curr->next = del->next;
			free(del);
			return head;
		}
		
		
	}
}

void view(Node* head) {
	
	//Jangan lupa buat kondisi kalau misal list kosong
	if (head == NULL) {
		printf("List Kosong\n");
		return;
	}
	
	//transversing sampai akhir
	Node* curr = head;
	while (curr != NULL) {
		printf("%d -> ", curr->data );
		curr = curr->next;
	}
	printf("NULL\n");
}



int main() {
	
//	//contoh bikin node langsing
//	Node *node1 = createNode(54);
//	Node *node2 = createNode(32);
//	
////	//koneksiin node langsung
//	node1->next = node2;
	
	Node* head = NULL;
//	insertFront(&head, 54);
//	insertFront(&head, 32);
//	insertFront(&head, 12);
	head = insertFront(head, 54);
	head = insertFront(head, 32);
	head = insertFront(head, 12);
	view(head);
	
	head = insertEnd(head, 9);
	head = insertEnd(head, 100);
	view(head);
	
	head = insertMid(head, 5, 1);
	view(head);
	head = insertMid(head, 1000, 3);
	head = insertMid(head, 69, 8);
	view(head);
//	head = insertMid(head, 74, 10); 
	
	head = deleteFront(head);
	view(head);
	
	head = deleteEnd(head);
	view(head);
	
	head = deleteMidbyPos(head, 5);
	view(head);
	
	
	head = deleteMidbyVal(head, 102);
	view(head);
	
	
	
	printf("\n\n");
	
	Node* head2 = NULL;
	head2 = insertFront(head2, 10);
	view(head2);
	head2 = deleteFront(head2);
	view(head2);
	
	
	return 0;
}
