#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	
	int id;
	node* left;
	node* right;
}node;

node* createNode(int id) {
	node* n = (node*)malloc(sizeof(node));
	n->id = id;
	n->left = NULL;
	n->right = NULL;
	
	return n;
}

node* insert(node* root, int id) {
	if (root == NULL) {
		return createNode(id);
	}
	
	if (id < root->id) {
		root->left = insert(root->left, id);
	}
	else if (id > root->id) {
		root->right = insert(root->right, id);
	}
//	else {
//		return root;
//	} SEHARUSNYA KAGA PAKE ELSE
	//kalau sama, seharusnya kaga di apa apa in
	return root;
}

//void leftSum(node* root, int* hasil) {
//	if (root == NULL) {
//		return;
//	}
//	
//	*hasil += root->id;
//	leftSum(root->left, hasil);
//}
//
//void rightSum(node* root, int* hasil) {
//	if (root == NULL) {
//		return;
//	}
//	
//	*hasil += root->id;
//	rightSum(root->right, hasil);
//}

//fungsi diatas salah karena kalau kiri, kanannya kaga keitung nantinya
int calculateSum(node* root) {
	if (root == NULL) {
		return 0;
	}
	
	return root->id + calcuateSum(root->left) + calculateSum(root->right);
}

void view(node* root) {
	if (root == NULL) {
		return;
	}
	
	view(root->left);
	printf("%d",root->id);
	view(root->right);
}

int main() {
	
	int n;
	
	node* root = NULL;
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int id;
		scanf("%d", &id);
		root = insert(root, id);
		int kiri = 0;
		int kanan = 0;
		kiri = calculateSum(root->left);
		kanan = calculateSum(root->right);
		printf("%d\n", abs(kiri-kanan));
		
	}
	
//	view(root);
	
	return 0;
}

