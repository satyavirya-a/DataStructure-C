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
	if (root== NULL) {
		return 0;
	}
	return root->height;
}

int getBalance(Node* root) {
	if (root == NULL) {
		return 0;
	}
	return height(root->left) - height(root->right);
}



Node* updateHeight(Node* root)  {
	if (root == NULL) {
		return 0;
	}
	
	root->height = 1 + max(height(root->left), height(root->right));
	
	return root;
}

Node* rotateRight(Node* root) {
	Node* newRoot = root->left;
	Node* orphan = newRoot->right;
	
	newRoot->right = root;
	root->left = orphan;
	
	updateHeight(root);
	updateHeight(newRoot);
	
	return newRoot;
}

Node* rotateLeft(Node* root) {
	Node* newRoot = root->right;
	Node* orphan = newRoot->left;
	
	newRoot->left = root;
	root->right = orphan;
	
	updateHeight(root);
	updateHeight(newRoot);
	
	return newRoot;
}

Node* rotateLeftRight(Node* root) {
	
}


Node* fixImbalace(Node* root, int val) {
	updateHeight(root);
		
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
		
	return fixImbalace(root, val);
		

	

	
}

Node* findBigChild(Node* root) {
	if (root == NULL ) {
		return root;
	}
	Node* curr = root;
	while (curr->right != NULL) {
		curr = curr->right;
	}
	return curr;
	
}

Node* deleteNode(Node* root, int val) {
	if (root == NULL) {
		return root;
	}
	
	if (val < root->val) {
		root->left = deleteNode(root->left, val);
	}
	else if (val > root->val) {
		root->right = deleteNode(root->right, val);
	}
	
	else {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			return NULL;
		}
		
		else if (root->left == NULL) {
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
			Node* temp = findBigChild(root);
			
			root->val = temp->val;
			
			root->left = deleteNode(root->left, temp->val);
		}
	}
	
	if (root == NULL) return NULL;
	return fixImbalace(root, val);
}

void preOrder(Node* root) {
	if (root == NULL) {
		return;
	}
	
	printf("%d\n", root->val);
	preOrder(root->left);
	preOrder(root->right);
}



int main() {
	
	Node* root = NULL;
	
	root = insert(root, 5);
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 3);
	preOrder(root);
	
	
	int n;
	
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		int val;
		scanf("%d", &val);
		
		root = insert(root, val);
	}
	
	int q; 
	scanf("%d", &q);
	
	char str[100];
	
	scanf(" %[^\n]", str);
	char* temp = strtok(str, " ");
	
	
	return 0;
}
