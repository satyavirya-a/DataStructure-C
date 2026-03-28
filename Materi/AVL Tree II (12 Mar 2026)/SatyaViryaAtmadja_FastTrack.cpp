#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int id;
	char* productName;
	int stock;
	
	struct Node* left;
	struct Node* right;
	int height;
	
}Node;

Node* create(int id, char* productName, int stock) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->id = id;
	n->productName = strdup(productName);
	n->stock = stock;
	
	n->left = NULL;
	n->right = NULL;
	n->height = 1;
	
	return n;
}

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

int height(Node* n) {
	if (n == NULL) {
		return 0;
	}
	return n->height;
}

int getBalance(Node* n) {
	return (height(n->left) - height(n->right));
}

Node* rotateRight(Node* n) {
	Node* x = n->left;
	Node* T2 = x->right;
	
	x->right = n;
	n->left = T2;
	
	x->height = 1 + max(height(x->left), height(x->right));
	n->height = 1 + max(height(n->left), height(n->right));
	
	return x;
}

Node* rotateLeft(Node* n) {
	
	Node* x = n->right;
	Node* T2 = x->left;
	
	x->left = n;
	n->right = T2;
	
	x->height = 1 + max(height(x->left), height(x->right));
	n->height = 1 + max(height(n->left), height(n->right));
	
	return x;
	
}
//view inorderrr
//kalau hapus, langsing ilang


Node* insert(Node* root, int id, char* productName, int stock) {
	
	if (root == NULL) {
		return create(id, productName, stock);
	}
	
	if (id < root->id ) {
		root->left = insert(root->left, id, productName, stock);
	}
	
	else if (id > root->id) {
		root->right = insert(root->right, id, productName, stock);
	}
	
	else {
		printf("Error: ID Produk sudah terdaftar!.\n");
		return root;
	}
	
	//update height node sebelumnya
	root->height = 1 + max(height(root->left), height(root->right));
	
	//hitung balance
	int balance = getBalance(root);
	
	if(balance > 1 && id < root->left->id) {
		return rotateRight(root);
	}
	
	if (balance > 1 && id > root->left->id) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	
	if (balance < -1 && id > root->right->id) {
		return rotateLeft(root);
	}
	
	if (balance < -1 && id < root->right->id) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	
	
	return root;
}

Node* search(Node* root, int id) {
	if (root == NULL) {
		return NULL;
	}
	
	if (id < root->id) {
		return search(root->left, id);
	}
	
	else if (id > root->id) {
		return search(root->right, id);
	}
	else {
		return root;
	}
	
	
}

void viewIn(Node* root) {
	if (root == NULL) {
		return;
	}
	
	viewIn(root->left);
	printf("ID: %d\n", root->id);
	printf("Nama: \"%s\"\n", root->productName);
	printf("Stok: %d\n\n", root->stock);
//	printf("BalanceFact: %d\n\n", getBalance(root));
	viewIn(root->right);
	
}

Node* findbig(Node* root) {
	Node* curr = root;
	
	while (curr != NULL && curr->right != NULL) {
		curr = curr->right;
	}
	
	return curr;
}

Node* pop(Node* root, int id) {
	if (root == NULL) {
		return root;
	}
	
	if (id < root->id) {
		root->left = pop(root->left, id);
	}
	else if (id > root->id) {
		root->right = pop(root->right, id);
	}
	
	
	else {
		if (root != NULL && root->left == NULL) {
			Node* temp = root->right;
			free(root->productName);
			free(root);
			return temp;
		}
		else if (root != NULL && root->right == NULL) {
			Node* temp = root->left;
			free(root->productName);
			free(root);
			return temp;
		}
		
		else {
			Node* temp = findbig(root->left);
			
			root->id = temp->id;
			free(root->productName);
			root->productName = strdup(temp->productName);
			root->stock = temp->stock;
			
			
			root->left = pop(root->left, temp->id);
			
			
		}
			
	}
	
		//update height node sebelumnya
	root->height = 1 + max(height(root->left), height(root->right));
	
	//hitung balance
	int balance = getBalance(root);
	
	if(balance > 1 && getBalance(root->left) >= 0) {
		return rotateRight(root);
	}
	
	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	
	if (balance < -1 && getBalance(root->right) <= 0) {
		return rotateLeft(root);
	}
	
	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	
	
	return root;
}

void buyProduct(Node* root) {
	int id;
	int amount;
	printf("Menu Beli\n");
	printf("Masukan ID: ");
	scanf("%d", &id); getchar();
	Node* tar = search(root, id);
	
	if (tar == NULL) {
		printf("Barang tidak ditemukan\n");
		return;
	}
	
	printf("Jumlah beli: ");
	scanf("%d", &amount); getchar();
	
	tar->stock += amount;
	printf("Success\n");
	return;
}

Node* sellProduct(Node* root) {
	int id;
	int amount;
	printf("Menu Jual\n");
	printf("Masukan ID: ");
	scanf("%d", &id); getchar();
	
	Node* tar = search(root, id);
	if (tar == NULL) {
		printf("Barang tidak ditemukan\n");
		return root;
	}
	
	printf("Jumlah jual: ");
	scanf("%d", &amount); getchar();
	
	if (amount > tar->stock) {
		printf("Transaksi Gagal: Stok tidak mencukupi!\n");
		return root;
	}
	
	tar->stock -= amount;
	printf("Success\n");
	if (tar->stock == 0 ) {
		printf("Product %s Habis!\n", tar->productName);
		root = pop(root,tar->id);
		return root;
	}
	return root;
}


Node* menuInsert(Node* root) {
	printf("Menu Tambah Product Baru\n\n");
	
	int id;	
	printf("Masukan ID: ");
	scanf("%d", &id); getchar();
	

	
	char name[51];
	do {
		printf("Masukan Nama [Maksimal 50 char]: ");
		scanf("%[^\n]", name); getchar();
	} while (strlen(name) > 50);
	
	int stock;
	printf("Masukan Stok: ");
	scanf("%d", &stock); getchar();
	
	root = insert(root, id, name, stock);
	return root;
}

Node* menuDelete(Node* root) {
	printf("Menu Delete\n");
	int id;
	printf("Hapus ID: ");
	scanf("%d", &id); getchar();
	root = pop(root, id);
	viewIn(root);
	getchar();
	return root;
}

Node* freeAll(Node* root ) {
	if (root == NULL) {
		return NULL;
	}
	
	freeAll(root->left);
	freeAll(root->right);
	
	free(root->productName);
	free(root);
	
	return NULL; //jagnan lupa di RETURN
}
int main() {
	
	
	Node* root = NULL;
	
//	root = insert(root, 105, "Laptop Asus", 10);
//	root = insert(root, 107, "Laptop Asus", 10);
//	root = insert(root, 108, "Laptop Asus", 10);
//	root = insert(root, 109, "Laptop Asus", 10);
//	root = insert(root, 110, "Nasi Asus", 15);
//	root = insert(root, 102, "Goreng Asus", 20);
//	root = insert(root, 104, "Enak Asus", 30);
//	root = insert(root, 103, "Enak Asus", 30);
//	root = insert(root, 102, "Enak Asus", 30);
	
//	int ketemu = search(root, 7);
//	printf("%d ketemu kaga\n", ketemu);
//	viewIn(root);
	
//	root = sellProduct(root, 105, 10);
//	viewIn(root);

	int opt;
	do {
		printf("FastTrack\n");
		printf("1. Tambah Produk Baru\n"
		"2. Transaksi Beli (Tambah Stok)\n"
		"3. Transaksi Jual (Kurangi Stok)\n"
		"4. Hapus Produk dari Sistem\n"
		"5. Tampilkan Seluruh Produk\n"
		"6. Keluar\n");
		printf(">> ");
		scanf("%d", &opt); getchar();
		switch (opt) {
			case 1: root = menuInsert(root);
				break;
			case 2: buyProduct(root);
				break;
			case 3: root = sellProduct(root);
				break;
			case 4: root = menuDelete(root);
				break;
			case 5: viewIn(root);
				break;
			case 6: 
				root = freeAll(root);
				printf("Exiting...");
				break;
			default: printf("Invalid Input");
		}
	} while (opt != 6);
	
	
	return 0;
}
