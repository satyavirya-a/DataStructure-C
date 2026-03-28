#include <stdio.h>

//ada tambahan 1 pointer lagi yaitu prev

/*

kalau insertfront:
	buat node baru 
	node->next = head
	head->prev = node
	head = node
	
	
kalau insertEnd:
	buat node baru
	
	buat node curr
	transversing  curr->next != NULL
	curr->next = node
	node->prev = curr
	
	
kalau insertMidbyPos
	buat node baru
	
	buat node curr
	pos--
	while(curr != NULL && pos != 1)
		pos--
		curr = curr->next
	node->next = curr->next
	node->prev = curr
	curr->next->prev = node //yang mau kita ganti prev dari (curr->next)
	curr->next = node


kalau deleteMidbyValue:

	transverse sampai ke titik yang mau didelete
	
	(curr->prev)->next = curr->next
	(curr->next)->prev = curr->prev
	free(curr)
	

kalau deleteFront:
	head = head->next
	free(head->prev)
	head->prev = NULL

kalau deleteEnd:
	
	transverse sampai ke titik yang mau didelete
	curr->prev->next = NULL
	free(curr)

*/


typedef struct Node {
	int data;
	Node* next;
	Node* prev; //kalau head, prev nya NULL
}Node;


Node* createNode(int val) {
	
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->data = val;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
}

Node* insertFront(Node *head, int val) {
	if (head == NULL) {
		head = createNode(val);
		return head;
	}
	
	Node* newNode = createNode(val);
	newNode->next = head;
	head->prev = newNode;
	head = newNode;
	return head;
}

Node* insertEnd(Node* head, int val) {
	Node* newNode = createNode(val);
	
	if (head == NULL) {
		head = createNode(val);
		return head;
	}
	
	else {
		
		Node* curr = head;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		
		curr->next = newNode;
		
		
	}
	
}

Node* insertMidbyVal(int Val)


int main() {
	
	
	
	return 0;
}
