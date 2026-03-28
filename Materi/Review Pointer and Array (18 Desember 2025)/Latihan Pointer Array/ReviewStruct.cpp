#include <stdio.h>


typedef struct {
	
	char nim[11];
	char name[100];
	double gpa;
	Alamat a;
	
	
}Mahasiswa; //kalau misal ga pake typedef ini jadi variable struct baru
//size tergantung member



//nested struct
typedef struct {
	char street[100];
	int noRumah;
}Alamat;


int main() {
	
	int n;
	
	scanf("%d", &n); getchar(); //nangkep enter biar gak langsung jadi string yang sampe ketemu enter
	
	Mahasiswa mhs[n];
	
	
	//INPUT data struct
	for (int i =0 ; i < n; i++) {
		scanf("%[^\n]", mhs[i].name);
		
		scanf("%s", mhs[i].nim);
		
		scanf("%d", &mhs[i].gpa);
		getchar(); //buat iterasi selanjutnya harus pake getchar juga
	}
	
	
	
	
	
	
	return 0;
}
