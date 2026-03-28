#include <stdio.h>
//tail nya nanti ke head tidak NULL

//lebih enak kalau pake tail kalau single
//single
typedef struct Node {
	int data;
	Node* next;
}Node;

/* 

Insert Tail:
	new Node
	node->next = tail->next
	tail->next = node
	tail = node
	
Insert Beginning:
	new Node
	node->next = tail->next
	tail->next = node
	Gak perlu update tail

Delete dan di mid mirip kaya di yang biasa
*/

//Double Circular Linked list
/*

	pake tail
	
InsertMidbyPos:
	new Node
	curr = tail
	pos--
	transverse while (curr != tail && pos != 1) //berhenti di posisi yang mau diganti
		pos--
		curr = curr->next
	
	node->prev = curr
	node->next = curr->next
	curr->next = node
	node->next->prev = node
	if curr == tail 
		tail = node
	
		

InsertEnd:
	
	
	node->prev = tail
	node->next = tail->next
	tail->next = node
	node->next->prev = node
	
	tail = node


*/

int main() {
	
	
	
	
	return 0;
}
