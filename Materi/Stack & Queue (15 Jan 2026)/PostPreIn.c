#include <stdio.h>

//sama kaya di dismath

//Infix 
/* scan dari kiri
search highest precendence
*/

//Postfix (PAKE STACK)
/*
	search sampai ketemu operator pertama
	Implement Stack:
	1. kalau ketemu operand (masuk stack)
	2. kalau ketemu operator (pop head 2 kali) push(hasil operasi 2 operasi sebelumnya)
	Pop pertama itu A, Pop kedua itu B
	Push nya push(B, A) JANGAN LUPA DIBALIK (karena seharusnya baca dari kiri kan
*/

//PREFIX (PAKE QUEUE) 
/*
	baca dari KANAN
	Implementasi:
	1. kalau ketemu operand (masuk stack)
	2. Kalau ketemu operator (pop head 2 kali) push (A operator B
	Pop pertama A, pop kedua itu B
	push(A, B) KAGA USAH DIBALIK KARENA BACA DARI KANAN
	
*/
int main() {
	
	
	return 0;
}
