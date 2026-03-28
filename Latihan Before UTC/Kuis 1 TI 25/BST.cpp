#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	
	int time;
	node* left;
	node* right;
}node;

node* createNode(int time) {
	node* n = (node*)malloc(sizeof(node));
	n->time = time;
	n->left = NULL;
	n->right = NULL;
	
	return n;
}

node* insert(node* root, int time) {
	if (root == NULL) {
		return createNode(time);
	}
	
	if (time < root->time ) {
		root->left = insert(root->left, time);
	}
	
	else if (time > root->time) {
		root->right = insert(root->right, time);
	}
	else {
		return root;
	}
}

//find deepest depth 
void finddeepest(node* root, int depth, int* maxdepth) {
	if (root->right == NULL && root->left == NULL) {
		if (depth >= *maxdepth) {
			*maxdepth = depth;
		}
	}
	
	if (root->left != NULL) {
		finddeepest(root->left, depth+1, maxdepth);
	}
	
	if (root->right != NULL) {
		finddeepest(root->right, depth+1, maxdepth);
	}
	
	
}

//mencari hasil kali leaf
int productleaf(node* root, int hasil, int depth, int maxdepth) {

	if (root->right == NULL && root->left == NULL ) {
		if (depth == maxdepth) {
			return root->time;
		}
		else {
			return 1;
		}
			
	}
	
	if (root->left != NULL) {
		hasil *= productleaf(root->left, hasil, depth+1, maxdepth);
	}
	if (root->right != NULL) {
		hasil *= productleaf(root->right, hasil, depth + 1, maxdepth);
	}
	
	return hasil;
	
}

int main() {
	
	int n;
	int time;
	node* root = NULL;
	scanf("%d", &n); 
	for (int i = 0; i < n; i++) {
		scanf("%d", &time);
		root = insert(root, time);
		int maxdepth = 1;
		finddeepest(root, 1, &maxdepth);
		int hasil = 0;
		hasil = productleaf(root, 1, 1, maxdepth);
		printf("%d\n", hasil);
	}
	

	
	
	
	return 0;
}
