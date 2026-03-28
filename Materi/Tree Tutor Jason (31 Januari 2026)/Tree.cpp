#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char data;
	Node* left;
	Node* right;
}Node;


Node* createNode(char a) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = a;
	newNode->right = NULL;
	newNode->left = NULL;
	
	return newNode;
}

//BST kalau kecil kiri, kalau besar kanan
Node* insert_BST(Node* root, char data) {
	Node* curr = root;
	
	if (curr == NULL) {//kalau kosong
		return createNode(data);
	}
	
	//kalau udah ada data
	Node* newNode = createNode(data);

	if (newNode->data < curr->data) {
		curr->left = insert_BST(curr->left, data);
	}
	else if (newNode->data > curr->data) {
		curr->right = insert_BST(curr->right, data);
	}
	
	return curr; //karena curr nya yang jalan
	//kalau tanpa curr baru return root; 
}

int isOperator(char data) {
	return data == '+' || data == '-' || data == '*' || data == '/' || data == '^';

	//return 1 kalau karakternya salah satu dari ini
}


Node* constructTree_postfix(const char postfix[]) {
	Node* stack[100];
	int top = -1; //pake top, karena cuma bisa akses top doang
	int i = 0; 
	while (postfix[i] != '\0') {
		char c = postfix[i];
		if (c == ' ') continue;
		
		//masukin huruf ke stack
			//karena c awalnya huruf, kita harus buat dia jadi node dulu
			// baru bisa masuk ke array of node
		Node* newNode = createNode(c);
		
		if (isOperator(c)) {
			//buat validasi kalau dia masih kosong
			if (top < 1) return NULL; //expressionnya tidak valid
			//ambil dulu elemen yang paling top, trus di pop
			newNode->right = stack[top--];
			newNode->left = stack[top--];
			
		}
		
		stack[++top] = newNode;
		i++;
	}
	if (top != 0) return NULL; //expressionnya tidak valid
	return stack[top]; //return root, 
}

Node* constructTree_prefix(const char prefix[]) {
	
	Node* stack[100];
	int top = -1;
	//mulainya dari paling ujung tapi;
	int i = strlen(prefix) - 1;
	
	while (i >= 0) {
		char c = prefix[i];
		
		Node* newNode = createNode(c);
		
		if (isOperator(c)) {
			newNode->left = stack[top--];
			newNode->right = stack[top--];
		}
		
		stack[++top] = newNode;
		i--;
	}
	
	if (top != 0) return NULL;
	return stack[top];
}

int precedence(char c) {
	switch (c) {
		case '+': return 1;
		case '-': return 1;
		case '*': return 2;
		case '/': return 2;
		case '^': return 3;
		default : return 0;
	}
}


void convert_infix_to_postfix(char infix[], char postfix[]) {
	
	int i = 0;
	char stack[100];
	int top = -1;
	int postIdx = 0;
	
	while (infix[i] != '\0') {
		char c = infix[i];
		
		//kalau dia operand -> langsung masuk postfix
		if (!(isOperator(c)) && c != '(' && c != ')') {
			postfix[postIdx++] = c;
		}
		
		//kalau ( masuk ke stack
		else if (c == '(') {
			stack[++top] = c;
		}
		
		//kalau ), pop stack sampai ketemu (, delete (
		else if (c == ')') {
			while (top != -1 && stack[top] != '(') { //top == -1 supaya tidak outof boud
				//pop terus masukin ke postfix 
				postfix[postIdx++] = stack[top--];
			}
			top--;
		}
		
		//kalau misal yang ada di stack >= c, pop dan masuk ke postfix
		else if (isOperator(c) ) {
			while (top != -1
				&& precedence(stack[top]) >= precedence(c)
				&& stack[top] != '(') {
				
				postfix[postIdx++] = stack[top--];
				
			}
			stack[++top] = c;
		}
		i++; //JANGAN LUPA i++, kalau buat while, buat i++ dulu biar gak lupa
		
	}
	
	while (top != -1) {
		postfix[postIdx++] = stack[top--];
	}
	
}



//cek kiri dulu karena menggunakan metode DFS
void viewPre(Node* root) {
	if (root == NULL) return;
	
	printf("%c", root->data);
	viewPre(root->left);
	viewPre(root->right);
}


void viewIn(Node* root) {
	if (root == NULL) return;
	
	//kalau dia operator dia munculin ( dulu baru dfs
	if (isOperator(root->data)) {
		printf("(");
	}
	viewIn(root->left);
	printf("%c", root->data);
	viewIn(root->right);
	if (isOperator(root->data)) {
		printf(")");
	}
}

void viewPost(Node* root) {
	if (root == NULL) return;
	
	viewPost(root->left);
	viewPost(root->right);
	printf("%c", root->data);
}

int main() {
	
	Node* root = NULL;
//	root = insert_BST(root, 'C');
//	root = insert_BST(root, 'A');
//	root = insert_BST(root, 'E');

	root = constructTree_postfix("AB+");
//	
	printf("Pre: "); viewPre(root);
	printf("\n");
	printf("In: "); viewIn(root);
	printf("\n");
	printf("Post: "); viewPost(root);
	printf("\n");
	
	printf("==========================\n");
	Node* root2 = NULL;
	root2 = constructTree_prefix("*+CAB");
	
	printf("Pre: "); viewPre(root2);
	printf("\n");
	printf("In: "); viewIn(root2);
	printf("\n");
	printf("Post: "); viewPost(root2);
	printf("\n");
	
	
	printf("==========================\n");
	Node* root3 = NULL;
	char infix[] = "(A+((B^C)*D))";
	char postfix2[100] = {NULL};
	convert_infix_to_postfix(infix, postfix2);
	printf("postifix : %s\n", postfix2);
	root3 = constructTree_postfix(postfix2);
	
	printf("Pre: "); viewPre(root3);
	printf("\n");
	printf("In: "); viewIn(root3);
	printf("\n");
	printf("Post: "); viewPost(root3);
	printf("\n");
	
	
	
	return 0;
}
