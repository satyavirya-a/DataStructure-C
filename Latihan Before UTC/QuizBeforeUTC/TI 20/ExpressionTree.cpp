#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char a;
	node* left;
	node* right;
}node;

node* createNode(char a) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->a = a;
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

char* infixToPostFix(char* infix) {
	char postfix[100];
	char stack[100];
	int top = -1;
	int i =0; 
	while (infix[i] != '\0') {
		char c = infix[i];
		if (c == ' ') {
			continue;
		}
		if (c >= 'A' && c <= 'Z') {
			postfix[++top] = c;
		}
		
		if (c == '(') {
			stack[]
		}
		
		
		i++;
	}
}

int main() {
	
	char infix[] = {"A × ((B + C) × (D - E)) / (F + G)"}
	
	return 0;
}
