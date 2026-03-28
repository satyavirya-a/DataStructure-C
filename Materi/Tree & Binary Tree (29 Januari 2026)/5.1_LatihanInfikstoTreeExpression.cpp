#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char item;
	struct node* left;
	struct node* right;
}node;

node* createNode(char item) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->item = item;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
	
}

int isOperator(char a) {
	switch (a) {
		case '+': return 1;
		case '-': return 1;
		case '*': return 2;
		case '/': return 2;
		case '^': return 3;
		default : return 0;
	}
}

void infixToPostfix(const char infix[], char postfix[]) {
	char stack[100];
	int i = 0;
	int topStr = -1;
	int topStack = -1;
	while(infix[i] != '\0') {
		char c = infix[i];
		if (isOperator(c) == 0 && c != '(' && c != ')') { //kalau dia operand langsung masuk string
			postfix[++topStr] = c;
		}
		if (isOperator(c) > 0) { // kalau dia operator
			while (isOperator(stack[topStack]) >= isOperator(c) && stack[topStack] != '(' ) { //selama operator di stack >= operator yang mau dimasukin
				postfix[++topStr] = stack[topStack--];		//masukin operator di stack ke string
			}
			stack[++topStack] = c; //masukin operator yang mau dimasukin kalau di stack udah lebih kecil
		}
		if (c == '(') {
			stack[++topStack] = c; //simpen ( di stack aja buat batas loop )
		}
		if (c == ')') { //kalau ada )
			while( stack[topStack] != '(') { //selama dia bukan (
				postfix[++topStr] = stack[topStack--]; //masukin di string
			}
			topStack--; //buang ( terakhir
		}
		i++;
	}
	while (topStack >= 0) { //masukin sisa di stack sampe idx 0
		postfix[++topStr] = stack[topStack--];
	}
	
	postfix[++topStr] = '\0'; //JANGAN LUPA STRING di tutup \0

}

node* createBinaryTree(char postfix[]) {
	node* stack[100];
	int top = -1;
	int i = 0;
	while (postfix[i] != '\0') {
		char c = postfix[i];
		if (isOperator(c) > 0) {
			node* newNode = createNode(c);
			newNode->right = stack[top--]; //A
			newNode->left = stack[top--]; //B
			stack[++top] = newNode;  // B operator A
			//biar node sebelumnya gak ketimpa jadi harus di ++ dulu 
		} 
		else {
			stack[++top] = createNode(c);
		}
		i++;
	}
	
	return stack[top--];
}

void viewPreOrder(node* root) {
	if (root == NULL) {
		return;
	}
	
	printf("%c", root->item);
	viewPreOrder(root->left);
	viewPreOrder(root->right);
}

void viewInOrder(node* root) {
	if (root == NULL) {
		return;
	}
	
	if (isOperator(root->item) > 0) printf("(");
	viewInOrder(root->left);
	printf("%c", root->item);
	viewInOrder(root->right);
	if (isOperator(root->item) > 0) printf(")");
}


void viewPostOrder(node* root) {
	if (root == NULL) {
		return;
	}
	
	viewPostOrder(root->left);
	viewPostOrder(root->right);
	printf("%c", root->item);
}



int main() {
	
//	char postfix2[] = "ABC*+D/";


	char infix[] = {"((A+(B*C))/D)"};
	
	char postfix1[100];
	infixToPostfix(infix, postfix1);
	
	printf("postfix = %s\n\n", postfix1);
	
	node* root = createBinaryTree(postfix1);
	
	printf("Pre Order: ");
	viewPreOrder(root);
	printf("\n\n");
	
	printf("In Order: ");
	viewInOrder(root);
	printf("\n\n");
	
	printf("Post Order: ");
	viewPostOrder(root);
	printf("\n\n");
	
	
	return 0;
}
