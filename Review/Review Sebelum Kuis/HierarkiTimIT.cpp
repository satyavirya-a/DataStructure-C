#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int key;
	node* left;
	node* right;
}node;

node* createNode(int key) {
	node* n = (node*)malloc(sizeof(node));
	n->key = key;
	n->left = NULL;
	n->right = NULL;
	
	return n;
}

node* insertBST(node* root, int key) {
	if (root == NULL) {
		return createNode(key);
	}
	
	if (key < root->key) {
		root->left = insertBST(root->left, key);
	}
	
	else if (key > root->key) {
		root->right = insertBST(root->right, key);
	}
	else {
		return root;
	}

	
}

int search(node* root, int key) {
	if (root == NULL) {
		return -1;
	}
	
	if (key < root->key) {
		return search(root->left, key);
	}
	else if(key > root->key) {
		return search(root->right, key);
	}
	else if (key == root->key) {
		return root->key;
	}
}

node* findbigleft(node* root) {
	node* curr = root;
	while (curr->right != NULL) {
		curr = curr->right;
	}
	
	return curr;
}

node* pop(node* root, int key) {
	if (root == NULL) {
		printf("tidak bisa di remove");
		return NULL;
	}
	
	if (key < root->key) {
		root->left = pop(root->left, key);
	}
	else if (key > root->key) {
		root->right = pop(root->right, key);
	}
	
	else {
		
		if (root->right == NULL && root->left == NULL) {
			free(root);
			return NULL;
		}
		
		if (root->left == NULL) {
			node* temp = root->right;
			free(root);
			return temp;
		}
		
		if (root->right == NULL) {
			node* temp = root->left;
			free(root);
			return temp;
		}
		
		//simpan nilai anak
		node* temp = findbigleft(root->left);
		//ganti nilai yang mau diedit
		root->key = temp->key;
		root->left = pop(root->left, temp->key);
	}
	
	return root;
}

void viewPre(node* root) {
	if (root == NULL) {
		return;
	}
	
	printf("%d -> ", root->key);
	viewPre(root->left);
	viewPre(root->right);
	
}

void viewIn(node* root) {
	if (root == NULL) {
		return;
	}
	
	viewIn(root->left);
	printf("%d -> ", root->key);
	viewIn(root->right);
	
}

void viewPost(node* root) {
	if (root == NULL) {
		return;
	}
	
	viewPost(root->left);
	viewPost(root->right);
	printf("%d -> ", root->key);
}

int main() {
	
	node* root = NULL;
	root = insertBST(root, 10);
	root = insertBST(root, 5);
	root = insertBST(root, 20);
	root = insertBST(root, 3);
	root = insertBST(root, 7);
	root = insertBST(root, 25);
	
	viewPre(root);
	printf("\n\n");
	viewIn(root);
	printf("\n\n");
	viewPost(root);
	printf("\n\n");
	
	return 0;
}
