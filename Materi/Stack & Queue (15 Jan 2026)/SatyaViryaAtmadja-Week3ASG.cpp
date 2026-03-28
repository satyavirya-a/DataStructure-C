#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Tulis nama
//umur, status

//insert, delete (wajib), view (optional)

//3  hapus 3 antrian (yang paling atas) 
//berapa banyak antrian yang mau dihapus ? 3 pop head 3 kali
//push sesuai prioritas

//input pasien pertama:
//nama
//umur
//status

//ESAY
//No 1: convert trus calculate
//No 2: convert dulu baru calculate
//No 3: convert doang No 4 juga convert doang
//Hanya bisa hapus 5, 5 lagi tidak bisa
//delete nya pake priority queue delete head



typedef struct Node {
	int umur;
	char* nama;
	int prior;
	struct Node* next;
	
}Node;

Node* createNode(const char* nama, int umur) {
	
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->nama = strdup(nama);
	newNode->umur = umur;
	newNode->prior = 0;
	
	return newNode;
}
//low itu 3
//high itu 1
Node* pushHead(Node* head, Node data) {
	
	Node* newNode = createNode(data.nama, data.umur);
	newNode->prior = data.prior;
	
	if (head == NULL) {//kalau masih kosong
		head = newNode;
		return head;
	}
	
	if (newNode->prior < head->prior) { //kalau cuma ada 1 node dan pas mau nambah prior nya lebih kecil dari head
		newNode->next = head;
		head = newNode;
		return head;
	}
	
	Node* curr = head;
	while (curr->next != NULL && newNode->prior >= curr->next->prior ) { //selama selanjutnya bukan null 
													//&& newNode->prior masih lebih besar dari priority node selanjutnya
//		printf("curr: %s\n", curr->nama);
		curr = curr->next;
	}
	
	
	newNode->next = curr->next;
	curr->next = newNode;
	
	return head;
	
	
}

int size(Node* head) {
	if (head == NULL) {
		return 0;
	}
	
	int count = 0;
	Node* curr = head;
	while(curr != NULL) {
		count++;
		curr = curr->next;
	}
	return count;
}
//pasien: 5
//delete: 10
//delete only pasien
Node* pop(Node* head) { //pophead
	
	if (head == NULL) {
		printf("List Kosong");
		return head;
	}
	
	Node* del = head;
	head = head->next;
	free(del->nama);
	free(del);
	return head;
	
}

void view(Node* head) {
	
	if (head == NULL) {
		printf("Data tidak ada, silahkan masukan data terlebih dahulu\n");
		return;
	}
	
	printf("Linked List after entering data:\n");
	Node* curr = head;
	while(curr != NULL) {
		printf("Nama: %s, Umur: %d, Status: %d\n", curr->nama, curr->umur, curr->prior);
//		printf("Nama: %s\n", curr->nama);
		curr = curr->next;
	}
	
	return;
}

void menuInsert(Node** head) {
	system("cls");
	Node newPasien;
	newPasien.nama = (char*)malloc(100*sizeof(char));
	char strstat[10];
	printf("Masukan data pasien:\n");
	printf("Nama: ");
	scanf("%[^\n]", newPasien.nama); getchar();
	printf("Umur: ");
	scanf("%d", &newPasien.umur); getchar();
	printf("Status [Low, Mid, High] (case sensitive): ");
	scanf("%s", strstat); getchar();
	if (strcmp(strstat, "Low") == 0) {
		newPasien.prior = 3;
	}
	else if (strcmp(strstat, "Mid") == 0) {
		newPasien.prior = 2;
	}
	else if (strcmp(strstat, "High") == 0) {
		newPasien.prior = 1;
	}

	*head = pushHead(*head, newPasien);
	free(newPasien.nama);
	
}

void menuDelete(Node **head) {
	int angka;
	system("cls");
	printf("Total Pasien: %d\n", size(*head));
	printf("Jumlah data yang mau didelete: ");
	scanf("%d", &angka); getchar();
	if (angka < size(*head)) {
		for (int i = 0; i < angka; i++) {
			*head = pop(*head);
//			printf("Pasien sekarang: %d", size(*head));
		}
		printf("Successfully deleted %d pasien!\n", angka);
		getchar();
		return;
	}
	
	else {
		int max = size(*head);
		for (int i = 0; i < max; i++) {
			*head = pop(*head);
//			printf("Pasien sekarang: %d", size(*head));
		}
		printf("Successfully deleted %d pasien!\n", max);
		getchar();
		return;
	}
	
	
}



int main() {
	
	Node* head = NULL;
	int opt = 0;
	do {
		system("cls");
		view(head);
		
		printf("===========================\n");
		printf("Menu Priority Queue\n");
		printf("1. Add data\n");
		printf("2. Delete data\n");
		printf("3. Exit\n");
		printf(">> ");
		scanf("%d", &opt);
		getchar();
		
		switch (opt) {
			case 1: menuInsert(&head);
				break;
			case 2: menuDelete(&head);
				break;
			case 3: printf("Exiting...");
				break;
			default:
				printf("input salah, coba lagi");
				break;
		}
	} while (opt != 3);
	
	return 0;
}
