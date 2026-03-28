#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Adelson Veleskii, E.M.Landis

//LL RR itu single rotation, 
	//node tengah ke atas, atas jadi anak tengah
//LR RL itu double rotation
	//node bawah ke tengah, tengah jadi anak bawah, trus single rotation

typedef struct Node {
	int val;
	int height;
	
	struct Node* left;
	struct Node* right;
}Node;


//ngitung balance factor pakai height, dari yang posisi yang mau di insert

Node* create(int val) {
	Node* n = (Node*)malloc(sizeof(Node));
	
	n->val = val;
	n->height = 1; //awalnya selalu 1
	n->left = NULL;
	n->right = NULL;
	
	return n;
}

//fungsi untuk cari max
int max(int a, int b) {
	if (a > b) return a;
	else return b;
}


//fungsi untuk ambil height anak anaknya
int height(Node* root) {
	if (root == NULL) {
		return 0;
	}
	return root->height;
}


//LEFT ROTATE
Node* rightRotate(Node* n) {
	
	Node* x = n->left;
	Node* T2 = x->right;
	
	// perform rotation
	x->right = n; // atas jadi anak tengah
	n->left = T2; // anak dari n yang udah di tengah jadi anak dari tengah yang naik ke atas
	
				//cari max height ANAK kiri atau kananya, berarti paretnya + 1 dari sana
	n->height = max(height(n->left), height(n->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	
	return x; // JANGAN LUPA DI KEMBALIKAN LAGI
}

Node* leftRotate(Node* n) {
	
	Node* y = n->right;
	Node* T2 = y->left;
	
	y->left = n;
	n->right = T2;
	
	n->height = max(height(n->left), height(n->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	
	return y;
}


//fungsi check balance
int getBalance(Node* root) {
	return (height(root->left) - height(root->right));
}


//fungsi insert INGET!! yang dilihat dimulai path dari apa yang diinsert
Node* insert(Node* root, int val) {
	if (root == NULL) {
		return create(val);
	}
	
	if (val < root->val ) {
		root->left = insert(root->left,val);
	}
	
	else if (val > root->val) {
		root->right = insert(root->right, val);
	}
	else {
		return root; //gak boleh sama
	}
	
	//update height untuk node sebelumya berdasarkan height anak paling besar
	root->height = 1 + max(height(root->left), height(root->right));
	

	//HITUNG BALANCENYA
	int balance = getBalance(root);
	
	
	//kalau balance lebih dari 1, lakukan rotating sesuai syarat
		//yang tadinya parent jadi anak,
		 //anak yang ditengah, child subtree lawan arahnya pindah ke (anak yang tadinya root)
	
	//LL	
	if (balance > 1 && val < root->left->val) { //val yang mau dimasukin lebih kecil  (bentuk: /)
		return rightRotate(root);
	}
	
	//LR
	if (balance > 1 && val > root->left->val) { //val yang maun dimasukin lebih besar (bentuk: <)
		root->left = leftRotate(root->left); //urusin anak (bentuk akhir: /)
		return rightRotate(root); //LL
	}
	
	//RR 
	if (balance < -1 && val > root->right->val) {
		return leftRotate(root);
	}
	
	//RL
	if (balance < -1 && val < root->right->val) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}


Node* findBig(Node* root) {
	Node* curr = root;
	
	while (curr != NULL && curr->right != NULL) {
		curr = curr->right;
	}
	
	return curr;
}


//DELETE
//yang di free itu selalu leaf
//pengganti node yang di delete itu anak terbesar subtree kiri

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
		Node* temp = NULL;
		if (root->left == NULL) {
			temp = root->right;
			free(root);
			return temp;
		}
		
		else if (root->right == NULL) {
			temp = root->left;
			free(root);
			return temp;
		}
		
		else {
			temp = findBig(root->left);
			
			root->val = temp->val;
			root->left = pop(root->left ,temp->val);
		}
	}
	
		//update height untuk node sebelumya berdasarkan height anak paling besar
	root->height = 1 + max(height(root->left), height(root->right));
	

	//HITUNG BALANCENYA
	int balance = getBalance(root);
	
	
	//kalau balance lebih dari 1, lakukan rotating sesuai syarat
		//yang tadinya parent jadi anak,
		 //anak yang ditengah, child subtree lawan arahnya pindah ke (anak yang tadinya root)
	
	//LL	
	if (balance > 1 && getBalance(root->left) >=0) { //getbalance itu maksunya bentuknya gini  (bentuk: /) root->left > root->right
		return rightRotate(root);
	}
	
	//LR
	if (balance > 1 && getBalance(root->left) < 0) { //val yang maun dimasukin lebih besar (bentuk: <)
		root->left = leftRotate(root->left); //urusin anak (bentuk akhir: /)
		return rightRotate(root); //LL
	}
	
	//RR 
	if (balance < -1 && getBalance(root->right) >=  0) {
		return leftRotate(root);
	}
	
	//RL
	if (balance < -1 && getBalance(root->right) <  0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;	
		
}

int main() {
	
	
	return 0;
}

