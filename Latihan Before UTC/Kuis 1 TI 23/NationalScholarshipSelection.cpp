#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
	int val;
	int level;
	
	struct Node* left;
	struct Node* right;
}Node;

typedef struct NodeL {
	int val;
	struct NodeL* next;
}NodeL;

Node* createNode(int val, int level) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->val = val;
	n->level = level;
	n->left = NULL;
	n->right = NULL;
	
	return n;
}

NodeL* createNodeL(int val) {
	NodeL* n = (NodeL*)malloc(sizeof(NodeL));
	n->val = val;
	n->next = NULL;
	return n;
}

Node* insert(Node* root, int val, int* level) {
	if (root == NULL) {
		return createNode(val, *level);
	}
	
	if (val < root->val ) {
		*level = *level + 1;
		root->left = insert(root->left, val, level);
	}
	
	else if(val > root->val) {
		*level = *level +1;
		root->right = insert(root->right, val, level);
	}
	
	else {
		return root;
	}
}

NodeL* pushTail(NodeL* head, int val) {
	NodeL* n = createNodeL(val);
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

void view(Node* root) {
	if (root == NULL) {
		return;
	}
	
	view(root->left);
	view(root->right);
	printf("%d (%d level)\n", root->val, root->level);
}

void viewL(NodeL* head) {
	NodeL* curr = head;
	while (curr != NULL) {
		printf("%d", curr->val);
		if (curr->next != NULL) {
			printf(" ");
		}
		curr = curr->next;
	}
}


void storeLL(Node* root, NodeL** head, int height) {
	if (root == NULL) {
		return;
	}
	
	if (root->level == height) {
		*head = pushTail(*head, root->val);
	}
	
	storeLL(root->left, head, height);
	storeLL(root->right, head, height);
}


Node* deleteNode(Node* root, int val) {
	if (root == NULL) {
		return root;
	}
	
	if(val < root->val) {
		return deleteNode(root->left, val);
	}
	
	else if (val > root->val) {
		return deleteNode(root->right, val);
	}
	
	else {
		if (root->left != NULL && root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp;
		}
		
		else if (root->right != NULL && root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp;
		}
		
		else {
			//kondisi kaga ada 2 2 nya, langsung free root
		}
		
		//kondisi punya anak 2, cari anak kiri terbersar
	}
}

int main() {
	
	int n;
	Node* root = NULL;
	
	int height = 0;
	scanf("%d", &n);
	for (int i= 0; i < n; i++) {
		int id;
		scanf("%d", &id);
		root = insert(root, id, &height);
	}
	
	view(root);
	NodeL* head[height] = {NULL};
	for (int i = 0; i < height; i++) {
		storeLL(root, &head[i], i);
		viewL(head[i]);
		printf("\n");
	}
	

	
	
	
	return 0;
}
