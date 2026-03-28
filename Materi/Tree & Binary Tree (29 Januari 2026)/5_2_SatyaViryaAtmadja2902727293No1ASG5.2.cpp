#include <stdio.h>
#include <string.h>
//Sistem Monitoring Sensor 

//PAKAI LINKED LIST
//typedef struct node {
//	char item;
//	node* left;
//	node* right;
//}node;
//
//node* arrayTree(char tar[], int idx, int size) {
//	node *root = NULL;
//	
//	if (root == NULL) {
//		return
//	}
//	
//	if(idx < size){
//		root = createNode(tar[idx]);
//	
//		root->left = arrayTree(tar, 2*idx+1);
//		root->right = arrayTree(tar, 2*idx+2);
//	}
//}



void ArrayTree(char tar[], int size) { 
	
	int i =0;

	while(tar[i] != '\0') {
		printf("Node Parent: %c (Indeks %d)\n", tar[i], i);
		if (tar[2*i+1] && 2*i+1 < size){
			
			printf("-> Left Child: %c (Indeks %d)\n", tar[2*i+1], 2*i+1);
		}
		
		else if (tar[2*i + 1] == NULL || 2*i + 1 > size) {
			printf("-> Left Child: Tidak Ada\n");
		}
		
		
		if (tar[2*i + 2] && 2*i+ 2 < size) {
			
			printf("-> Right Child: %c (Indeks %d)\n",tar[2*i + 2], 2*i + 2);
		}
		else if (tar[2*i + 2] == NULL || 2*i + 2 > size) {
			printf("-> Right Child: Tidak Ada\n");
		}
		
		if (2*i+1 > size && 2*i+ 2 > size) { //bisa juga dibuat flag trus di cek, kalau left == 1 || right == 1, dia internal
			printf("-> Status: Ini adalah LEAF NODE.\n"); 
		}
		
		else {
			printf("-> Status: Ini adalah INTERNAL NODE.\n"); //internal, masih di dalam tree (internal) bukan di ujung
		}
		printf("-------------------------------------\n");
		
		i++;
	}
	
}


int main() {
	
	char sensorTree[10] = {'A', 'B', 'C', 'D', 'E', 'F'};
	int len = strlen(sensorTree);
	printf("=== Analisis Struktur Tree Berbasis Array ===\n");
	printf("Referensi Materi Halaman 14 (Rumus Indeks)\n\n");
	ArrayTree(sensorTree, len-1);
	
	return 0;
}
