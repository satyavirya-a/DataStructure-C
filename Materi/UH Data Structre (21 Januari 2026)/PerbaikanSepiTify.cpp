#include <stdio.h>

typedef struct Node{
	char* title;
	Node* next;
}Node;

Node* newNode(char* title) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	
	//cara manual string
	newNode->title = (char*)malloc(sizeof(title) + 1);
	strcpy(newNode->title, title);
	
}

int main() {
	
	
	
	
	
	return 0;
}
