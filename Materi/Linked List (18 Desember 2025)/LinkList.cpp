#include <stdio.h>
#include <stdlib.h>

// abstrak data type (user defined) -> data type yang kaga ada di predefine (int, float, char)
// struct bisa jadi tools buat abstrak data type


//data structure itu arrangement data di computer memory atau disk storage


//link list -> dynamic data structure sequence pake node
//ada value & pointer yang nunjuk ke selanjutnya


//Queque -> antrian (first in first out)
//Stack -> first in last out

//binary tree -> structure yang ada node tapi pointernya 2 (left and right)






//karakteristik linklist:
//pointer head
//node, yaitu:
	//pointer next
	//value
	
//link list cuma bisa diakses sequential manner (transverse)
//tapi disimpennya kaga di consecutive memory locations

typedef struct Node { 
	int data; 		//structure member
	struct Node *next;
}Node;

Node* createNode(int data) {
	
	//alokasi (sewa) dulu memory
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	//error handling
	if (newNode == NULL) {
		printf("Gagal\n");
		exit(1);
	}
	
	//isi datanya
	newNode->data = data;
	newNode->next = NULL;
	
	return newNode;
}

void printList(Node* node) {
	while(node != NULL) {
		printf("%d -> ", node->data);
		node = node->next;
	}
	
	printf("NULL\n");
}

//insert di awal atau head
void insertHead(struct Node **head, int val) {
	
	//buat node baru
	Node *newNode = createNode(val);
	
	//LANGKAH LANGKAH INSERT DI AWAL
		//koneksiin new node ke head
		newNode->next = *head;
		
		//ganti head jadi newNode
		*head = newNode;
		
	
}

void insert(Node *head, int pos, int val) {
	
	int count = 0;
	Node *newNode = createNode(val);
	
	//transverse sampai ke titik yang dimau
	Node *curr = head;
	while (count < (pos - 1) - 1) {
		curr = curr->next;
		count++;
	}
	
	newNode->next = curr->next;
	curr->next = newNode;
	
}

void Hapus(struct Node **head, int pos) {
	int count = 0;
	Node *curr = *head;
	if (pos == 1) {
		*head = curr->next;
		free(curr);
	}
	else {
		while (count < (pos-1) - 1) { //posisi dikurang 1 karena index, index dikurang satu karena mau delete dari node sebelumnya
			curr = curr->next;
			count++; 
		}
		
		Node *del = curr->next;
		curr->next = del->next;
		free(del);
	}
	
}



int main() {
	
	//buat pointer struct buat cara awalnya
	Node* head = NULL;
	
	//buat node-node untuk linked list
	Node* node1 = createNode(5);
	Node* node2 = createNode(4);
	Node* node3 = createNode(3);
	
	
	//hubungkan tiap nodenya dan JADIKAN NODE1 JADI HEAD
	head = node1;
	node1->next = node2;
	node2->next = node3;
	
	printList(head);
	
	
	
	//insert new node di head (awal)
	insertHead(&head, 7);
	
	
	printList(head);
	
	//delete
	Hapus(&head, 1);
	
	printList(head);
	
	//insert di tengah
	insert(head, 3, 10);

	printList(head);	
	
}
