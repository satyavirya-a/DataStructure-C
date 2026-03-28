#include <stdio.h>

/*
Tree -> non linear data structure
hubungan rierarchical relationships

root (akar) = top most node in tree
edge 		= garis menghubungkan 2 nodes
leaf node	= node tidak punya anak
Sibling 	= same PARENT
path		= jalur (A-B-C)
ancestor node = node yang diatasnya
descendant node = node yang dibawahya

LEVEL = posisi (paling atas root level0)
dari big picture
DEGREE = total anak yang dimiliki


BINARY TREE
punya 2 anak paling banyak

anak kiri dan anak kanan

DEPTH (kedalaman) = dari ROOT sampai ke node yang dituju (depth root 0)
dilihat dari jalur

Height (ketinggian) = dimulai dari 0, dari leaf sampai root

Max number of node in level k = 2^k
Max number of node of height h = 2^(h+1) - 1 (-1 karena dimulai dari root)	HEIGHT dimulai dari 0


Minimum height for n nodes 2log(n)
Maximum height for n nodes n-1 	(skewed tree)


ARRAY
root idx = 0
left = 2p+1, p = parent idx
right = 2p + 2
parent = (p-1)/2


LINKED LIST
using edge berupa pointer:
node* left
node* right
node* parent (two way)


Jenis Binary Tree:
Perfect : lengkap anaknya 2
Complete : Left child haru ada dari parent paling kiri
Skewed : setiap node cuma punya 1 anak (hirarki list)
Balanceed : Terlihat gak jauh level antar leaf (gak terlalu jomplang)


EXPRESSION TREE
Prefix = operator operand operand
Postfix = operand operand operator
Infix = operand operator operand



PREFIX:
kalau dia operator -> masuk kiri, masukan operator
rekursi selama curr-> left != NULL - >operator oop

TRANvERSE:
cek apakah masih ada ->next asg
Print


INFIX
putchar('{') untuk scope atau presendence di setiap node

tranversing pakai dfs (yang di kodingin)

kalau udah paling dalam, cek lagi apakah bisa didalemet

BFS
Print nya melebar , per level dimulai dari yang paling atas


*/


typedef struct node {
	int item;
	node* left;
	node* right;
}node;

//bikin nodenya sama kaya linked list



void prefixOrder(node* root) {
	if (root == NULL) {
		return;
	}
	
	printf("%d ", root->item);
	if (root->left != NULL) prefixOrder(root->left);
	if (root->right != NULL) prefixOrder(root->right);
}

void infixOrder(node* root) {
	if (root == NULL) {
		return;
	}
	
	//di expression tree, kalau operator, putchar(')')
	if (root->left != NULL) infixOrder(root->left);
	printf("%d ", root->item);
	if (root->right != NULL) prefixOrder(root->right);
	//di expression tree, kalau operator, putchar(')')
}

void postfixOrder(node* root) {
	if (root == NULL) {
		return;
	}
	if (root->left != NULL) postfixOrder(root->left);
	if (root->right != NULL) postifxOrder(root->right);
	printf("%d", root->item);
}


//is_operator, fungsi return int yang kalau operator 1, default 0
//CONSTRCUT TREE dari POSTFIX
node* construct_tree(char postfix[]) {
	node* stack[100];
	int top = -1;
	int i = 0;
	while (postifx[i] != '\0') {
		char ch = postfix[i];
		
		if (ch >= 'A' && ch <= 'Z') {//kalau ini bukan operator
		
			node* newNode = create(ch); //bikin new node
			
			stack[++top] = newNode; //isi stack[++top] dengan newNode nya
		}
		else { //kalau ini operator, harus bikin tree
			
			node* newNode = create(ch); //buat newnode dari operator
			
			newNode->right = stack[top--]; //newNode->right = stack[top--] pop sebelumnya
			
			newNode->left = stack[top--]; //newNode->left = stact[top--] pop sebelumnya lagi 
			
			stack[++top] = newNode; //stack[++top] = newNode, setelah pop 2 sebelumnya, push lagi hasil tree nya
			
			
		}
		
		i++;
	}
	return stack[top--]; //return tree nya yang ada di stack di index ke top
}

int main() {
	
	
	
	
	return 0;
}
