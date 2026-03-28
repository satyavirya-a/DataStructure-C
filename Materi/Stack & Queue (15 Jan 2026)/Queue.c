#include <stdio.h>

//QUEUE
/*
Ada front (depan) ada rear (belakang/terakhir)
Jika mau insert, dari belakang:
	(kalau full)
		return error
	(kalau kosong)
		front = front + 1
		rear = rear + 1
	(lainnnya)
		rear = rear + 1
	
	arr[rear] = data
	
Jika mau pop, dari depan:
	buat valuedeleted untuk di return nanti
	(validasi apakah front == rear)
		deletedValue = queue[front]
		front == -1 
		rear == -1
	
	front++
	
Cek full:
	if (rear = max - 1)
	
display:
	iterasi for (i = front; i <= rear; i++)
	

	
Linked List:
1. Ada 2 pintu (1 masuk 1 keluar)
2. Push Tail dan Pop head DOANG
3. Kalau Front = Rear = NULL queue empty
4. Bisa juga ada fungsi peek() return value front (yang mau keluar)
*/

//CIRCULAR QUEUE
/*
mengatasi masalah kekosongan memory sia-sia ketika pop head 
ada fungsi next() = return indeks yang kosong setelah di delete
next(){
	return data + 1 % MAX;
newIsFull:
	if (rear != front && next(rear) == front) return 1
	
print:
(validasi posisi rear < front)
print dari front sampe MAX-1
	VALIDASI kalau i == MAX-1 && i != rear
		kalau gak ketemu print dari 0 sampai sama dengan rear
(kalau rear > front

push:
	bedanya ketika gak kosong dan gak penuh
	rear = next(rear)
	
pop:
	beadnya di
	front = next(front)
Ketika disuruh implementasi stack and queue:
bisa pake linked list atau pake arr

*/

int main() {
	
	
	
	
	return 0;l
}
