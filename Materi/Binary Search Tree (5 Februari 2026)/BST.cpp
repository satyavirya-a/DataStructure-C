#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//MASUK UTS
//BINARY SEARCH Tree gak bisa input duplikat 

typedef struct node {
	char item;
	node* left;
	node* right;
}node;

node* createNode(char item) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->item = item;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

int search(node* root, char item) {
	if (root == NULL) {
		printf("rusak");
		return -1;
	}
	
	if (item == root->item ) {
		printf("found");
		return root->item;
	}
	
	if (item < root->item) {
		return search(root->left, item);
	}
	if (item > root->item) {
		return search(root->right, item);
	}
}

//insertion terjadi hanya di l
node* insert(node* root, char item) { //kala misal leaf itu sebenernya punya anak left NULL, anak right NULL

	if (root == NULL) {
		return createNode(item);
	}
	
	if (root->item == item) {
		printf("Tidak boleh ada nilai yang sama");
		return root;
	}
		
	if (item < root->item) {
		root->left = insert(root->left, item); //sampe ketemu null
	}
	
	else if (item > root->item) {
		root->right = insert(root->right, item); // smape ketemu null
	}
	
	return root;
}


//mencari anak terbesar
node* findbigchild(node* root) {
	node* curr = root;
	while (root != NULL && root->right != NULL) { //selama masih ada dan anak kannanya juga ada
		curr = curr->right;
	}
	return curr; //return node yang paling besar
}

//if kosong (tree belum ada) error
//else if val < tree->data, rekursif pop(tree->left, val)
//else if val > tree->data, rekursif pop(tree->right, val)
//kalau udah sama:
	//kalau ada 2 child:
		//temp = cari anak kiri terbesar dari root (ini yang mau menjadi pengganti)
		//replace key dan remove key lama secara rekursif sampe yang terjadi di leaf
					//atau
		//cari successor nya
	//kalau leaf:
		//langsung delete aman
	//kalau ada 1 child:
		// (else if tree->left != NULL):
			// tree = tree->left		delete node, sambungin parent dan childny aja 
		//(else if tree->right != NULL):
			//tree = tree->right
			
node* deleteNode(node* root, char val) {
	
	if (root == NULL) return root;
	
	//cari node yang mau diapus
	if (val < root->item) {
		root->left = deleteNode(root->left, val);
	}
	else if (val > root->item) {
		root->right = deleteNode(root->right, val);
	}
	else { //logika kalau udah ketemu yang mau diapus / udah ketemu mana yang mau di ganti
		
		//KASUS 1 CHILD ATAU ZERO CHILD
		if (root->left == NULL) { //ketika yang kiri udah abis
			node* temp = root->right; 
			free(root);
			return temp; //kembalikan nilai yang kanan
		}
		
		else if (root->right == NULL) { //ketika yang kanan udah abis
			node* temp = root->left;
			free(root);
			return temp; //kembalikan nilai yang kiri
		}
		//kalau 
		
		//KASUS 2 CHILD
		node* temp = findbigchild(root->left); //cari yang paling besar child di paling kiri
		
		root->item = temp->item; //diswab
		
		root->left = deleteNode(root->left, temp->item); //rekursi isi node yang setelah udah di swab, mau diapain
		
		
		
		
	}
}

//node* pop(node* root, char tar) {
//	node* curr = root;
//	node* parent = NULL;
//	
//	while (curr != NULL) {
//		if (tar == curr->item) {
//			parent = curr;
////			if (tar)
//		}
//	}
//		
//}

 

void viewIn(node* root) {
	if (root == NULL) {
		return;
	}
	
	viewIn(root->left);
	printf("%c ", root->item);
	viewIn(root->right);
}

int main() {
	
	node* root1 = NULL;
	
	root1 = insert(root1, 'c');
	root1 = insert(root1, 'a');
	root1 = insert(root1, 'd');

	
	viewIn(root1); printf("\n\n");
	
	root1 = deleteNode(root1, 'a');
	
	viewIn(root1);
//	
	return 0;
}
