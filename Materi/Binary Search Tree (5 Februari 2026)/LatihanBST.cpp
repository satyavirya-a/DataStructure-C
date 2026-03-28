#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char* nim;
	char* name;
	node* right;
	node* left;
}node;


node* createNode(const char* name, const char nim[]) {
	node* newNode = (node*)malloc(sizeof(node));
	
	newNode->name = strdup(name);
	newNode->nim = strdup(nim);
	newNode->right = NULL;
	newNode->left = NULL;
	
	return newNode;
}

node* find(node* root, const char nim[]) {
	if (root == NULL) {
		return NULL;
	}
	
	if (strcmp(root->nim, nim) == 0) {
		return root;
	}
	else if (strcmp(nim, root->nim ) < 0) {
		return find(root->left, nim);
	}
	else if (strcmp(nim, root->nim ) > 0) {
		return find(root->right, nim);
	}
	
}

node* insert(node* root, const char* name, const char nim[]) {
	if (root == NULL) {
		return createNode(name, nim);
	}
	
	if (strcmp(nim, root->nim) == 0) {
		printf("Data tidak boleh sama\n");
		return root;
	}
	
	else if (strcmp(nim, root->nim) < 0) {
		root->left = insert(root->left, name, nim);
	}
	
	else if (strcmp(nim, root->nim) > 0) {
		root->right = insert(root->right, name, nim);
	}
	return root;

}

node* findbigval(node* root) {
	node* curr = root;
	while (curr != NULL & curr->right != NULL) {
		curr = curr->right;
	}
	
	return curr;
}

node* del(node* root, const char* nim) {
	if (root == NULL) {
		return NULL;
	} 
	if (strcmp(nim, root->nim) < 0) {
		root->left = del(root->left, nim);
	}
	else if (strcmp(nim, root->nim) > 0) {
		root->right = del(root->right, nim);
	}
	else {
		if (root->left == NULL) {
			node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			node* temp = root->left;
			free(root);
			return temp;
		}
		
		
		node* temp = findbigval(root->left); //cari child left paling gede
		root = temp;
		root->left = del(root->left, temp->nim);
		
		
		
		
	}
}

void viewIn(node* root) {
	if (root == NULL) {
		return;
	}
	
	viewIn(root->left);
	printf("(%s) %s\n", root->nim, root->name);
	viewIn(root->right);
}

void menuFind(node* root) {
	if (root == NULL) {
		printf("Masukkan Data Terlebih dahulu\n");
		return;
	}
	printf("FIND MAHASISWA\n");
	char tarNim[4];
	printf("NIM mahasiswa yang mau dicari: ");
	scanf("%s", tarNim);
	
	node* hasil = find(root, tarNim);
	if (hasil == NULL) {
		printf("Tidak ditemukan\n");
	}
	else {
		printf("Data ditemukan!\n");
		printf("NIM: %s\n", hasil->nim);
		printf("Name: %s\n",hasil->name);
	}
	getchar();
	
}
node* menuInsert(node* root) { //kalau pake &, bisa pake void
	char name[100];
	char nim[4];
	printf("INSERT MAHASISWA\n");
	printf("Nama: ");
	scanf(" %[^\n]", name);
	do {
		printf("NIM (maksimal 3 huruf): ");
		scanf("%s", nim);
		if (strlen(nim) > 3) {
			printf("Tidak sesuai urutan\n");
		}
	} while(strlen(nim) > 3);
	
	root = insert(root, name, nim );
	printf("data berhasil dimasukan!\n");
	return root;
}

node* menuDelete(node* root) {
	char nim[4];
	printf("DELETE MAHASISWA\n");
	viewIn(root);
	printf("===================\n");
	printf("NIM: ");
	scanf("%s", nim);
	root = del(root, nim);
	printf("Terima kasih!\n");
	return root;
	
}




int main() {
	
	node* root1 = NULL;
	int opt;
	do {
		if (root1 != NULL) printf("Data Mahasiswa: \n");
		viewIn(root1); 
		if (root1 != NULL) printf("\n");
		printf("==========================\n");
		printf("MAHASISWA MANAGER\n");
		printf("1. Find Mahasiswa\n");
		printf("2. Insert Mahasiswa\n");
		printf("3. Delete Mahasiswa\n");
		printf("4. Exit\n");
		printf(">> ");
		scanf("%d", &opt); getchar();
		switch (opt) {
			case 1: menuFind(root1); 
				break;
			case 2: root1 = menuInsert(root1); //menuInsert(&root1) supaya gak root1 =, variabel di local itu struct doang, pass parameter by &
				break;
			case 3: root1 = menuDelete(root1);
				break;
			case 4: printf("Exiting...\n");
				break;
			default: printf("Salah Opsi\n");
		}
	} while (opt != 4);
	
	
	
	
	return 0;
}
