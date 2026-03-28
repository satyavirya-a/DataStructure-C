#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int value;
	//kita buat pointer untuk nunjuk node selanjutnya
	struct Node* next;
}Node;

//fungsi transverse
void transverse(Node* node) {
	while (node != NULL) {
		//mau ngapain
		node = node->next;
	}
		
}
//fungsi insert di awal
void insertHead(Node **head, int val) {
	
	//buat node baru
	//hubungkan dengan head
	//ganti head jadi newnode

}

//fungsi insert di tengah
void insert(int pos, int val) {
	
	//kita pakai pointer next sebelum tempat yang mau kita tuju
	
	//LANGKAH LANGKAH
		//buat newNode
		//buat variabel struct pointer curr = head
		//buat variabel count = 0
		//Tranverse mulai dari 0 sampai count sesuai dengan pos-1
		//newNode->next = temp->next
		//temp-next = newNode
	
	 
	
}

void delete(Node *head, int tar) {
	
	//buat variabel struct pointer curr = head
	//if tar == head->value
		//majuin head (head = head->next)
		//free(curr)
	
	//else transverse sampai curr->next->value == tar
	//HUBUNG yang baru dengan selanjutnya, hubung yang lama dengan selanjutnya dari del
		//buat node baru buat delete (Node *del) delete ini jadi curr->next nya
		//(curr->next = del->next) jadi null dong
	//free(del)
}


int main() {
	
	//buat pointer head untuk awal linked list
	Node *head = NULL;
	
	//buat struct node baru, namanya node1
		//alokasi memory untuk struct node baru
		Node *node1 = (Node*)malloc(sizeof(Node));  //pakai pointer karena lokasinya itu gak harus bersebelahan memorinya
		
		//masukan data dan pointer ke mana
//		(*node).value = 10  ini sama aja
		node1->value = 10;
		node1->next = NULL;
	
	//jadikan node 1 sebagai head
	head = node1;
		
	
	
	//buat struct node baru lagi, namanya node2
		//alokasi memory buat node2
		Node *node2 = (Node*) malloc(sizeof(Node));
		node2->value = 5;
		node2->next = NULL;
	
	
	//HUBUNGKAN node1 dan node2
	node1->next = node2;
	
	
	//buat struct node ketiga
		//alokasi memory buat node3
		Node *node3 = (*Node) malloc(sizeof(Node));
		node3->value = 15;
		node3->next = NULL;
	
	//HUBUNGKAN node2 dan node3
	node2->next = node3;
	
	//print element node tertentu dari node sebelum sebelumnya
	printf("%d\n", head->value);
	printf("%d\n", head->next->value); //print elemen node2
	printf("%d\n", node1->next->next->value) //print elemen node3
	
	
	free(node1);
	free(node2);
	
	return 0;
}
