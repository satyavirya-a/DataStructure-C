#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int val;
	
	struct Node* left;
	struct Node* right;
	int height;
}Node;

Node* create(int val) {
	Node* n = (Node*)malloc(sizeof(Node));
	
	n->val = val;
	n->left = NULL;
	n->right = NULL;
	n->height = 1;
	
	return n;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int height(Node* root) {
	if (root == NULL) {
		return 0;
	}
	return root->height;
}

int getBalance(Node* root) {
	return height(root->left) - height(root->right);
}

Node* rotateRight(Node* root) {
	Node* newRoot = root->left;
	Node* orphan = newRoot->right;
	
	newRoot->right = root;
	root->left = orphan;
	
	root->height = 1 + max(height(root->left), height(root->right));
	newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));
	
	return newRoot;
}

Node* rotateLeft(Node* root) {
	Node* newRoot = root->right;
	Node* orphan = newRoot->left;
	
	newRoot->left = root;
	root->right = orphan;
	
	root->height = 1 + max(height(root->left), height(root->right));
	newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));
	
	return newRoot;
}

Node* insert(Node* root, int val) {
	if (root == NULL) {
		return create(val);
	}
	
	if (val < root->val) {
		root->left = insert(root->left, val);
	}
	
	else if (val > root->val) {
		root->right = insert(root->right, val);
	}
	
	else {
		return root;
	}
	
	root->height = 1 + max(height(root->left), height(root->right)); //Update height dulu baru get balance nya
	int balance = getBalance(root);
	
	if (balance > 1 && val < root->left->val) {
		return rotateRight(root);
	}
	
	else if (balance > 1 && val > root->left->val) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	
	else if (balance < -1 && val > root->right->val) {
		return rotateLeft(root);
	}
	
	else if (balance < -1 && val < root->right->val) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	
	return root;
}

Node* bigChild(Node* root) {
	Node* curr = root;
	while (curr->right != NULL) {
		curr = curr->right;
	}
	
	return curr;
	
}

Node* pop(Node* root, int val) {
	if (root == NULL) {
		return NULL;
	}
	
	if (val < root->val) {
		root->left = pop(root->left, val);
	}
	
	else if (val > root->val) {
		root->right = pop(root->right, val);
	}
	
	else {
		if (root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp;
		}
		else if (root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else {
			Node* temp = bigChild(root->left);
			root->val = temp->val;
			
			root->left = pop(root->left, temp->val);
		}
	}
	
	if (root == NULL) {
		return root;
	}
	
	
		root->height = 1 + max(height(root->left), height(root->right)); //Update height dulu baru get balance nya
	int balance = getBalance(root);
	
	if (balance > 1 && getBalance(root->left) >= 0) {
		return rotateRight(root);
	}
	
	else if (balance > 1 && getBalance(root->left) < 0) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	
	else if (balance < -1 && getBalance(root->right) <= 0) {
		return rotateLeft(root);
	}
	
	else if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	
	return root;
}


int main() {
	
	
	
	return 0;
}
