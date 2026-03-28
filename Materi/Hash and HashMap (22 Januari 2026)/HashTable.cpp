#include <stdio.h>
#include <stdlib.h>
#include <string.h> //supaya kalau ada yang convert di string bisa

//ada input -> masuk fungsi hash -> disimpen di index

/*
	Maps (Dictionary)
	KEY - VALUE
	
	Hash table itu kumpulan data 
		Hash set -> store set (not repeated values)
		Hash map -> ada Key ada Value
		
	Hash Table itu lebih ke hash map
	
	Hashing : proses key menjadi index (untuk nanti jadi searching idx)
	Hashing pake hash function
	
	
*/


/*
	Example:
	ada 5 string: dafi, ayam, ikan, goreng, nasi
	hash func: first char ASCII jadi idx
	buat hash table 25 element
	
	Table:
	1. Ayam
	2.
	3. 
	4.dafi
	5.
	6.
	7.
	....
	24.
	25.
	
	kalau misal ada elemen yang sama ? namanya Collision
	cara atasinya ada linear prob atau chaining

*/

/* 
	Cara hashing (Jenis Hash Function)
	- bebas yang penting berubah jadi angka di range indexnya
	
	MID SQUARE: Kuadratin key, ambil nilai tengah 
	atau kuadratin trus diubah ke biner dulu trus mask and shift (lebih oke untuk komputer)
	lebih baik ambil lebih dari 8 bit kalau mau pake biner (karena komputer itu 8 bit or 16 bit
	
		kenapa kalau saling berjauhan dia bagus ? 
		semakin dia gak dempetan ketika ganti value lain, 
		jadinya lebih bervariasi dan tidak menimbulkan collision
		
		KITA PAKE ARRAY SOALNYA BUTUH INDEX dan langsung akses indexnya
		jadi supaya searching lebih cepat
	
	DIVISION: Key MOD angka
	biasanya angka nya size array/tablenya
	
	
	FOLDING: partisi key, jumlah, ambil angka digit
	tapi rulesnya bebas
	
 	DIGIT EXTRACTION: digit dari key kita ambil bebas
 	
 	ROTATING HASH: nambah varian supaya bervariasi, di reverse string
 	
 	bisa tambah function karena anjay supaya variasi
	
	
	
*/


/* 
	Collision = Kalau ada yang sama, solusinya ?
	
	Misal, array udah mau penuh. lakukan rehashing, jadi dilakuan hashing ulang agar ada yang kosong
	REHASHING: buat array baru dengan size 2x , trus masukin data lama ke array baru
	
	LINEAR PROBING: kalau ada yang penuh
	lakukan transverse sampai ketemu idx yang kosong, masukin ke situ
	
		jadi nanti searching nya dimulai dari idx, nanti looping i++ sampai ketemu value yang dimau
		
	CHAINING: kalau collisiom
		dia jadi head trus bisa buat linked list dari setiap idx

*/

#define TABLE_SIZE 5

typedef struct DataItem{
	int data;
	int key;
} DataItem;

DataItem* hashArray[TABLE_SIZE];
DataItem* dummy;


//IN SEMUA  HASH FUNCTION
int division(int key) {
	return key % TABLE_SIZE;
}

int digitExtract(int key, int pos[], int size) {
	
	//ubah ke string dulu
	char buffer[100];
	sprintf(buffer, "%d", key);
	
	int extractVal = 0;
	for (int i = 0; i < size; i++) {
		extractVal = extractVal * 10 + (buffer[pos[i] - 1] - '0'); 
	}
	return extractVal;
}

//integer itu di floor kalau comma
int folding(int key) {
	int sum = 0;
	
	while (key > 0) {
		sum += key % 100; //kita mau ambil 2 digit tiap pembagiannya
							//MAU PARTISI BERAPA DIGIT ? 
		key = key/100;
	}
	
	return sum;
}

//mid square itu bisa gede soalnya di square kan, jadi better pakai long long
int midSquare(int key) {
	long long int square = key * key;
	char str[20];
	sprintf(str, "%lld", square );
	
	int length = strlen(str);
	int mid = length / 2;
	
	//bisa disesuaikan
	int result; 
	if (length % 2 == 0) {
		result = (str[mid - 1] - '0') * 10 + (str[mid] - '0');
	}
	else {
		result = (str[mid-1] - '0') * 100 +  (str[mid] - '0') * 10 + (str[mid+1] - '0');
	}
	return result;
}

int rotate(int key) {
	//bisa ubah ke string trus reverse string
//	char buffer[50];
//	sprintf(buffer, "%d", key);

	int reminder = 0;
	int reverse  = 0;
	
	while (key > 0) {
		reminder = key % 10;
		//dikali 10 itu untuk untuk tambahin digit dibelakang reverse yang udah ada
		reverse = reverse* 10 + reminder;
		//angka yang dimasukin reverse itu mulai dari digit terkecil karena sistemnya remainder
		key = key / 10;
	}
	
	return reverse;
}

void ContohPenggunaanHashFunction() {
		int key = 3121;
	
	//division
	int divNum = division(key);
	printf("Division: %d\n", divNum);
	
	//digit extr
	int pos[] = {1, 3, 5};
	int size = sizeof(pos)/sizeof(pos[0]); //jumlah digit yang mau diambil
	int digExtNum = digitExtract(key, pos, size);
	printf("Digit Extraction: %d\n", digExtNum);
	
	//folding
	int foldNum = folding(key);
	printf("Folding: %d\n", foldNum);
	
	
	//mid square
	int midSquNum = midSquare(key);
	printf("Mid Square: %d\n", midSquNum);
	
	
	//rotating
	int rotNum = rotate(key);
	printf("Rotating: %d\n", rotNum);
}


void insert(int key, int data) {
	
	//buat struct baru
	DataItem* item = (DataItem*)malloc(sizeof(DataItem));
	item->data = data;
	item->key = key;
	
	//lakukan hashing buat cari idx
		//dalam kasus ini kita pake key untk hashing
		
	int hashIdx = division(key);
	
	//iterasi table, cari ada yang sama ga
	for (int i = 0; i < TABLE_SIZE; i++) {
	
		int idx = (hashIdx + i) % TABLE_SIZE; //dimodulus supaya agar semua index array terpenuhi
												//kalau mulai dari tengah, dia bakal ngecek indeks sebelumnya juga
		//kalau kuadratik probing -> idx = (hashIdx + i * i) % TABLE_SIZE
		//kalau rehashing buat node (pointer struct)
				//buat pointer temporary untuk merujuk ke hashtable
				//ganti ukuran table
				//trus memory "table" nya di calloc dengan ukuran memory yang lebih gede
				//insert data tari old table ke table baru

		
		if (hashArray[idx] == NULL || hashArray[idx] == dummy) {
			hashArray[idx] = item;
			printf("%d inserted at index %d\n", data, idx); //kalau idx + 1 itu pos
			return;
		}
	
	}
	
	
	printf("table penuh, tidak bisa masuk\n");

}



int main() {
	
	dummy = (DataItem*)malloc(sizeof(DataItem));
	dummy->data = -1;
	dummy->key = -1;
	
	insert(1, 56);
	insert(1, 27);
	insert(2, 70);
	
	return 0;
}


