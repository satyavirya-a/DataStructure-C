#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	
	int id;
	
	struct Node* left;
	struct Node* right;
}Node;

Node* create(int id) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->id = id;
	n->left = NULL;
	n->right = NULL;
	
	return n;
}

//intung leaf bisa langsung pas di insert, tambahin parameter int *cLeaf
Node* insert(Node* root, int id) {
	if (root == NULL) {
		return create(id);
	}
	
	if (id < root->id) {
		//buat kondisi if (root->left != NULL && root->right != NULL) *cLeaf += 1
		root->left = insert(root->left, id);
	}
	
	else if (id > root->id) {
		//buat kondisi if (root->left != NULL && root->right != NULL) *cLeaf += 1
		root->right = insert(root->right, id);
	}
	
	return root;
}

void countLeaf(Node* root, int* count) {
	if (root == NULL) { //JANGAN LUPA SAFETY NET
		return;
	}
	if (root->left == NULL && root->right == NULL) {
		*count = *count + 1;
		return;
	}
	if (root->left != NULL) {
		countLeaf(root->left, count);
	}
	if (root->right != NULL) {
		countLeaf(root->right, count);
	}
}

int main() {
	
	int n;
	Node* root = NULL;
	
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		int id;
		
		scanf("%d", &id);
		root = insert(root, id);
		int cLeaf = 0;
		countLeaf(root, &cLeaf);
		printf("%d\n", cLeaf);
	}
	return 0;
}

