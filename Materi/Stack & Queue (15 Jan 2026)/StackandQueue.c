#include <stdio.h>
//BEBAS PAKE APA AJA

//STACK
/*sering di utc dan uac Priorty Queue
kalau di linked list itu cuma pop head dan insert head doang (LIFO last in first out)
kalau penuh di array harus reconstruct 
variabel:
TOP address paling atas
MAX maximum num of element

linked list stack:
1. Node (data dan address to the next node)
2. Start pointer (Head) = TOP
3. Insert dan pop cuma bisa di head
4. TOP = NULL stack kosong

Array stack:
1. Kalau di pop itu "tidak sepenuhnya ilang"
2. Kalau di insert itu di timpa
*/

//typedef struct Node
//CONTOH PAKE ARRAY

#define MAX 6
int stack_arr[MAX];
int top = -1; //initianilasii posisi top (DARI SEBELUM MASUK ARRAY)

int isEmpty() {
	if (top == -1) {
		return 1; //true
	}
	else {
		return 0; 
	}
}

int isFull() {
	if (top == MAX - 1) {
		return 1; //true
	}
	
	else {
		return 0;
	}
}


void print() {
	if (isEmpty()) {
		printf("Stack Kosong\n");
		return;
	}
	
	//traversing
	for (int i = top; i >= 0; i--) {
		printf("%d\n", stack_arr[i]);
	}
}

void push(int data) {
	if (isFull()) {
		printf("Stack Overflow");
		return;
	}
	top = top + 1; //di tambah dulu baru diinsert
	stack_arr[top = data;]
}

int pop() {
	int val;
	if (isEmpty()) {
		printf("Stack Underflow");
		exit(1);
	}
	value = stack_arr[top];
	top = top-1; //INI DELETE NYA
	return value;
}

int size() {
	
}

int main() {
	
	
	
	
	return 0;
}
