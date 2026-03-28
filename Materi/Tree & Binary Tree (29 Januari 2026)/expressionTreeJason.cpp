#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Expression TREE

typedef struct Node{
    char data;
    Node* left;
    Node* right;
    //Node* parent;        //access the parent     
}Node;

void preOrder(Node* root){
    if (!root) return;
    printf("%c ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}


int is_operator(char c) {
    return (c == '+' || c == '-' || 
            c == '*' || c == '/' || 
            c == '^');
}

void inOrder(Node* root){
    if (!root) return;

    if (is_operator(root->data)) putchar('(');

    inOrder(root->left);
    printf("%c ", root->data);
    inOrder(root->right);

    if (is_operator(root->data)) putchar(')');
}

void postOrder(Node* root){
    if (!root) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%c ", root->data);
}

Node* create(char data){
    Node* newNode = (Node* ) malloc (sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;


    return newNode;
}


Node* construct_tree(char* postfix){
    struct Node* stack[100];
    int top = -1;
    int i = 0;

    while (postfix[i]  != '\0'){
        char ch = postfix[i];
        Node* newNode = create(ch);

        if (is_operator(ch)) {            //kalau operator
            if (top < 1) return NULL;
            newNode->right = stack[top--];      //B
            newNode->left = stack[top--];       //A
        }

        stack[++top] = newNode;                 //masukin ke stack
        i++;
    } 

    if (top != 0) return NULL;
    return stack[0];
}

int main () {
    char postfix[] = "ABC*+D/";
    Node* root = construct_tree(postfix);

    postOrder(root);
    preOrder(root);
    inOrder(root);

    return 0;
}