#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int id;
	
	struct Node* left;
	struct Node* right;
}Node;

Node* create(int id) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->id = id;
	n->left = NULL;
	n->right = NULL;
	
	return n;
}

//di insert bisa langsung cari depthnya, jadi kalau udah ada nilai yang sama, kaga bakal keitung juga
Node* insertWithDepth(Node* root, int id, int* depth, int currDepth){
	if (root == NULL) {
		*depth = currDepth;
		return create(id);
	}
	
	if (id < root->id) {
		root->left = insertWithDepth(root->left, id, depth, currDepth + 1);
	}
	
	else if (id > root->id) {
		root->right = insertWithDepth(root->right, id, depth, currDepth+1);
	}
	
	else {
		*depth = -1;
	}
	
	return root;
}
Node* insert(Node* root, int id) {
	if (root == NULL) {
		return create(id);
	}
	
	if (id < root->id) {
		root->left = insert(root->left, id);
	}
	
	else if (id > root->id) {
		root->right = insert(root->right, id);
	}
	
	return root; //kalau sama ya langsung return aja wak gagal
}

void findDepth(Node* root, int id, int* depth) {
//	printf("id %d depth sekarang %d\n", root->id, *depth);
	//bisa langsung root == NULL udah pasti yang paling bawah
	if (root == NULL) {
//		printf("Data tidak ditemukan");
		*depth = -1;
		return;
	}
	if (root->id == id) {
		return;
	}
	
	if (id < root->id) {
		*depth = *depth +1;
		findDepth(root->left, id, depth );
	}
	
	else if (id > root->id ) {
		*depth = *depth +1;
		findDepth(root->right, id, depth);
	}
}

void printDepthPreorder(Node* root, Node* main) {
	if (root == NULL) {
		return;
	}
	
	int depth = 1;
	findDepth(main, root->id, &depth);
	printf("%d\n", depth);
	printDepthPreorder(root->left, main);
	printDepthPreorder(root->right, main);
}

int main() {
	
	Node* root = NULL;
	
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int id;
		scanf("%d", &id);
		
		//HARUS SEARCH 3 KALI
		//harus cek dulu apakah udah ada di root
		int checkdepth = 1;
		findDepth(root, id, &checkdepth);
		if (checkdepth != -1) { //ada di root berarti
			continue; //langsung skip , kaga usah dicari dan di print
		}
		root = insert(root, id);
		int depth = 1;
		findDepth(root, id, &depth);
		
		if (depth == -1) {
			continue;
		}
		printf("%d\n", depth);
		
		
		//bisa langusng tanpa cek cek pake fungsi ini pengganti insert biasa
//		int depth1 = 1;
//		root = insertWithDepth(root, id, &depth1, 1);

	}
	
//	Bener tapi urutan print nya bukan preorder juga bang
//	printDepthPreorder(root, root);
}


