#include <stdio.h>
#include <stdlib.h>
//Hierarki Tim IT

typedef struct node {
	int id;
	node* left;
	node* right;
}node;

node* createNode(int id) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->id = id;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

void viewPreOrder(node* root) {
	if (root == NULL) {
		return;
	}
	
	printf("%d -> ", root->id );
	viewPreOrder(root->left);
	viewPreOrder(root->right);
}

void viewInOrder(node* root) {
	if (root == NULL) {
		return;
	}
	
	viewInOrder(root->left);
	printf("%d -> ", root->id);
	viewInOrder(root->right);
}

void viewPostOrder(node* root) {
	if (root == NULL) {
		return;
	}
	
	viewPostOrder(root->left);
	viewPostOrder(root->right);
	printf("%d -> ", root->id);
}




int main() {
	
	node* Manager = createNode(10);
	node* TeamLeadA = createNode(5);
	node* TeamLeadB = createNode(20);
	node* Staff1 = createNode(3);
	node* Staff2 = createNode(7);
	node* Staff3 = createNode(25);
	
	//1 dan 2
	Manager->left = TeamLeadA;
	Manager->right = TeamLeadB;
	
	//3
	TeamLeadA->left = Staff1;
	TeamLeadA->right = Staff2;
	
	//4
	TeamLeadB->right = Staff3;
	
	printf("--- Struktur Hierarki Tim ---\n\n");
	
	printf("Pre-Order Traversal (Struktur Pelaporan):\n");
	printf("(Urutan: Root -> Kiri -> Kanan)\n");
	viewPreOrder(Manager); printf("SELESAI\n\n");
	
	printf("In-Order Traversal (Urutan ID):\n");
	printf("(Urutan: Kiri -> Root -> Kanan)\n");
	viewInOrder(Manager); printf("SELESAI\n\n");
	
	printf("Post-Order Traversal (Botom-Up):\n");
	printf("(Urutan: Kiri -> Kanan -> Root)\n");
	viewPostOrder(Manager); printf("SELESAI\n\n");
	
	
	return 0;
}
