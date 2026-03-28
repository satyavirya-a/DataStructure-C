#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100 

//key itu nama (NOT CASE SENSITIVE, pake to lower)
//pake minimal 3 beda method function (KOMBINASI) di comment aja
//jadi panggil function di hashIDX nya ada 3 variabel yang dimasukin ke fungsi methodnya
//Pake chaining dapat point

//CHAINING jadi pake linked list
//insert, display, delete, edit (?)


typedef struct Node{
	int no;
	char* key;
	char* email;
	struct Node* next;
	
} Node;

Node* hashTable[SIZE] = {NULL};



//Method digit Extraction (1st, 2nd, and 3rd digit)
int digExtrac(char* key, int size, int pos[]) {
	int ExtractVal = 0;
	
	//to lowernya cuma pas hashing, aslinya mah ga berubah, buat variabel baru aja
	//JANGAN GANTI POINTER KARENA ITU AKAN BERUBAH DI MAIN, tetep kesimpen perubahaannya karena pointer
	int len = strlen(key);
	char *copy = strdup(key);
	for (int j = 0; j < len; j++) {
		copy[j] = tolower(key[j]);
	}
	
	int batas = strlen(copy);
	for (int i = 0; i < size; i++) {
		if (pos[i] - 1 < batas) {//walau pasti seharusnya digitnya sesuai, tambahin validasi aja biar gak index out of bound
			ExtractVal += copy[pos[i] - 1]; // atau kalau gak mau buat variable temp, langsung extract += tolower(key)
		}
		
	}
	free(copy); //kalau langsung tolower kaga usah pake free free an dan sebenernya kalau langsung tolower(key) lebih cepet juga
	return ExtractVal;
	
}

//Method Rotating
int rotate(int num) {
	
	int remainder = 0;
	int reverse = 0;
	while (num > 0) {
		//mengabil digit paling belakarng
		remainder = num % 10;
		
		//nambah digit baru (*10) di reverse dan masukan digit belakang awal ke reverse
		reverse = reverse * 10 + remainder;
		//angka reverse akan dimulai dari digit paling belakang
		
		//hilangkan digit paling belakang dari angka
		num = num/10;
	}
	return reverse;
}

//Method Division
int division(int num) {
	
	return num % SIZE;
}


void insert(int size, int pos[], char* key, const char* email, int no) {
	
	//deklarasi item baru
	Node* newItem = (Node*) malloc(sizeof(Node));
	newItem->key = strdup(key);
	newItem->email = strdup(email);
	newItem->no = no;
	newItem->next = NULL;
	
	
	//buat hashIdx dengan 3 method (digit extraction, rotate, division)
	int hashIdx = digExtrac(key, size, pos);
//	printf("hashIdx digit = %d\n", hashIdx);
	hashIdx = rotate(hashIdx);
//	printf("hashIdx rotate = %d\n", hashIdx);
	hashIdx = division(hashIdx);
//	printf("hashIdx divi = %d\n", hashIdx);
	
	
	//lakukan logika insert
	if (hashTable[hashIdx] == NULL) { //kalau misal data di index kosong
		hashTable[hashIdx] = newItem;
	}
	else { //kalau gak kosong, CHAINING
		
		Node* curr = hashTable[hashIdx];
		while (curr->next != NULL) {
			curr = curr->next;		
		}
		
		curr->next = newItem;
		
	}

}



void pop( char* keyTar, int pos[], int size) {
	
	//langsung hashing tanpa iterasi for buat cari idxnya
	int idxHashTar = digExtrac(keyTar, size, pos);
	idxHashTar = rotate(idxHashTar);
	idxHashTar = division(idxHashTar);
	
	//kalau di index ternyata kosong
	if (hashTable[idxHashTar] == NULL) {
		printf("Data tidak ditemukan\n");
		return;
	}
	
	//pop head
	if (strcmp(hashTable[idxHashTar]->key, keyTar) == 0) {
		Node* del = hashTable[idxHashTar];
		hashTable[idxHashTar] = hashTable[idxHashTar]->next; 
		free(del->email);
		free(del->key);
		free(del);
		printf("Data berhasil dihapus!");
		return;
	}
	else {
		//cek dulu apakah next nya null atau engga, kaalu null ya apa yang mau di cek, langsung return error aja
		if (hashTable[idxHashTar]->next == NULL) {
			printf("Data tidak ditemukan");
			return;
		}
		
		//kalau gak ketemu di headnya, cari tranverse sampai ketemu
		Node* curr = hashTable[idxHashTar];
		while (curr->next != NULL && strcmp(curr->next->key, keyTar) != 0 )  {
			curr = curr->next;
		}
		
		//kalau ketemu di tengah
		if (strcmp(curr->next->key, keyTar) == 0 ) {
			Node* del = curr->next;
			curr->next = del->next;
			free(del->email);
			free(del->key);
			free(del);
			printf("Data berhasil dihapus!");
		}
		
		//kalau kaga ketemu
		else {
			printf("Data tidak ditemukan\n");
			return;
		}
		
	}
}

void view(Node* head, int i) {
	Node* curr = head;
	
	printf("Idx-%d:\nName: %s\nNomor Telepon: %d\nEmail: %s\n", i, curr->key, curr->no, curr->email);
	curr = curr->next;
	while (curr != NULL) {
		
		printf("-------\n");
		printf("Name: %s\nNomor Telepon: %d\nEmail: %s\n", curr->key, curr->no, curr->email);
		
		curr = curr->next;
	}
}

void viewTable() {
	
	printf("== View Data ==\n\n");
	
	for (int i = 0 ; i < SIZE; i++) {
		if (hashTable[i] == NULL) {
			printf("Idx-%d: ~~~\n", i);
		}
		else {
			view(hashTable[i], i);
		}
		
	}
}

void menuInsert(int pos[], int size) {
	char nama[100];
	char email[100];
	int no;
	printf("== Insert Data ==\n\n");
	
	printf("%d. Masukkan data baru:\n", cData + 1);
	printf("Nama: ");
	scanf(" %[^\n]", nama );
	printf("Nomor Telepon: ");
	scanf("%d", &no ); getchar(); //getchar itu karena setelah input angka angka 
	printf("Email: ");
	scanf(" %s", email );
	
	insert(size, pos, nama, email, no);
	printf("Data berhasil dimasukan!");
	getchar();
	cData++;
}

void menuDele(int pos[], int size) {
	printf("== Delete Data ==\n");
	char keyTar[100];
	printf("Masukan nama yang ingin di delete:");
	scanf(" %[^\n]", keyTar);
	
	pop(keyTar, pos, size);

	getchar();
}




int main() {
	
	int pos[] = {1, 3};
	int size = sizeof(pos)/sizeof(pos[0]);
	
	int opt;
	do {
		system("cls");
		printf("== Buku Telepon ==\n");
		printf("1. Insert Data\n");
		printf("2. Display Data\n");
		printf("3. Delete Data\n");
		printf("4. Exit\n");
		printf(">> ");
		scanf("%d", &opt); getchar();
		switch (opt) {
			case 1: system("cls") ;
				menuInsert(pos, size);
				getchar();
				break;
			case 2:system("cls") ;
				viewTable();
				getchar();
				break;
				
			case 3: menuDele(pos, size);
				getchar();
				break;
			case 4:printf("Exiting..\n");
				break;
			default:
				printf("Salah opsi\n");
		}
	} while (opt != 4);
	
	
	
	
	
	
	
	
	
	
//	char duit[] = {"Tolung Saya"};
//	int hashIdx = digExtrac(duit, size, pos);
//	printf("hashIdx = %d\n", hashIdx);
//	
//	hashIdx = rotate(hashIdx);
//	printf("hashIdx = %d\n", hashIdx);
//	
//	hashIdx = division(hashIdx);
//	printf("hashIdx = %d\n", hashIdx);
	
	return 0;
}
