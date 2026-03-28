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
	n->height = 1;
	n->left = NULL;
	n->right = NULL;
	
	return n;
}

int max(int a , int b) {
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
	
	root->height = 1 + max(height(root->left), height(root->right)); // JANGAN KEBALIK, harus dari BAWAh ke atas
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
	else if (val > root->val ) {
		root->right = insert(root->right, val);
	}
	
	root->height = 1 + max(height(root->left), height(root->right));
	
	int balance = getBalance(root);
	
	if (balance > 1 && val < root->left->val ) { // single rotation (/) val < anak kiri root
		return rotateRight(root);
	}
	
	else if (balance > 1 && val > root->left->val) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	
	else if (balance < -1 && val > root->right->val) { // single rotation (\) val > anak kanan
		return rotateLeft(root);
	}
	
	else if (balance < -1 && val < root->right->val) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	
	return root;
	
	
}

Node* bigLeftChild(Node* root) {
	Node* curr = root;
	while (curr->right != NULL) {
		curr = curr->right;
	}
	
	return curr;
}


Node* pop(Node* root, int val) {
	if (root == NULL) {
		return NULL; // gagal
	}
	
	if (val < root->val) {
		root->left = pop(root->left, val );
	}
	else if (val > root->val) {
		root->right = pop(root->right, val);
	}
	
	else {
		if (root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp;
		}
		else {
			Node* temp = bigLeftChild(root->left);
			
			root->val = temp->val;
			
			root->left = pop(root->left, temp->val); // yang  di return itu root->left nya
		}
	}
	
	if (root == NULL) { // kalau satu node dan diapus
		return root;
	}
	
	root->height = 1 + max(height(root->left), height(root->right));
	
	int balance = getBalance(root);
	
							// kalau balance root->left > 0 berarti berat di kiri kalau = 0 itu berarti anaknya left ^
	if (balance > 1 && getBalance(root->left) >= 0) {
		return rotateRight(root);
	}
	
	else if (balance > 1 && getBalance(root->left) < 0) { // bentuk <
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	
	else if (balance < -1 && getBalance(root->right) <= 0) {
		return rotateLeft(root);
	}
	
	else if (balance < -1 && getBalance (root->right) > 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	
	return root;
	
}

int main() {
	
	
	
	return 0;
}
