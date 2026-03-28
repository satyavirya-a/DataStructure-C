#include <stdio.h>


int main() {
	
	//Deklarasi variabel = Alokasi byte di memory
	//Value, Data type, Address

	
	//POINTER
	// pointer -> hal yang menunjuk ke alamat suatu variabel (Simpen alamat variabel lain)
	// operator = & (address) dan * (dereferencing)
	
	//pass information
	//return value banyak (Bisa pake struct)
	
	//tree, link list, dll
	int x;
	int *px;
	px = &x;
	*px = 5;
	
	printf("x = %d\n", x);
	
	//Pointer to pointer
	int y = 20;
	int *py;
	int **ppy;
	int ***pppy;
	
	py = &y;
	ppy = &py;
	pppy = &ppy;
	
	printf("y = %d\n", ***pppy);
	free(pppy);
	
	
	//ARRAY
	//arr kumpulan alamat variabel yang bisa diubah (mutable) dan homogenues (sama jenis datanya)
	//di referensi oleh index
	
	//array dimensi banyak
	int arr[2][2][2][2] = {
	    {
	        { {1, 2}, {3, 4} },
	        { {5, 6}, {7, 8} }
	    },
	    {
	        { {9, 10}, {11, 12} },
	        { {13, 14}, {15, 16} }
	    }
	};
	
	
	printf("%d\n", arr[1][0][0][1]); //dari gede ke spesifik cell
	
	/*1 itu dari { {1, 2}, {3, 4} }, index 0   |   { {9, 10}, {11, 12} },   index 1
	        	{ {5, 6}, {7, 8} }			   |	{ {13, 14}, {15, 16} }   
											   |
	
	*/
	
	/*0 itu dari { {9, 10}, {11, 12} }  index 0   |    { {13, 14}, {15, 16} }   index 1
											      |
	*/
	
	/*0 itu dari {9, 10}, index 0 | {11, 12} index 1
	
	*/
		
	/*1 itu dari 9 index 0  | 10 index 1
	*/
}
