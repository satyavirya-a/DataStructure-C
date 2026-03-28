#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int id;
	
	struct Node* left;
	struct Node* right;
}Node;

typedef struct NodeL {
	int id;
	
	struct NodeL* next;
}NodeL;

Node* create(int id) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->id = id;
	n->left = NULL;
	n->right = NULL;
	
	return n;
}

NodeL* createL(int id) {
	NodeL* n = (NodeL*)malloc(sizeof(NodeL));
	n->id = id;
	n->next = NULL;
	
	return n;
}

int isInTree(Node* root, int id) {
	if (root == NULL) {
		return -1;
	}
	
	if (root->id == id) {
		return 1;
	}
	
	else if (id < root->id) {
		return isInTree(root->left, id);
	}
	
	else if (id > root->id) {
		return isInTree(root->right, id);
	}
}


Node* insert(Node* root, int id) {
	if (root == NULL) {
		return create(id);
	}
	
	if (id < root->id) {
		root->left = insert(root->left, id);
	}
	
	else if (id > root->id) {
		root->right = insert(root->right, id);
	}
	
	return root;
}

NodeL* push(NodeL* head, int id) {
	NodeL* n = createL(id);
	if (head == NULL) {
		head = n;
		return head;
	}
	
	NodeL* curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	
	curr->next = n;
	return head;
	
}

void view(NodeL* head) {
	if (head == NULL) {
		return;
	}
	
	NodeL* curr = head;
	while (curr != NULL) {
		printf("%d", curr->id);
		if (curr->next != NULL) {
			printf("->");
		}
		
		curr = curr->next;
	}
}

void findPath(Node* root, int id ) {
	if (root == NULL) {
		return;
	}
	if (root->id == id) {
		printf("%d", root->id);
		return;
	}
	
	if (id < root->id) {
		printf("%d->", root->id);
		findPath(root->left, id);
	}
	
	else if (id > root->id) {
		printf("%d->", root->id);
		findPath(root->right, id);
	}
	
	
}

int main() {
	
	//DARI PADA BUAT LINKED lIST mending 
	//validasi dulu aja apakah ada atau tidak di treenya
	
	int n;
	Node* root = NULL;
	
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		int id;
		scanf("%d", &id);
		root = insert(root, id);
	}
	
	int idTar;
	scanf("%d", &idTar);
//	NodeL* head = NULL;
	
	int isKetemu = isInTree(root, idTar);
	if (isKetemu == -1) {
		printf("ID Tidak Ditemukan\n");
	}
	else {
		findPath(root, idTar);
		printf("\n");
	}
	
	
	
	
	return 0;
}
