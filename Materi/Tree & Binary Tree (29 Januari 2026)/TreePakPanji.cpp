#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char item;
    struct node* left;
    struct node* right;
}node;

node* create(char value) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->item = value;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

node* construct_tree_postfix(char postfix[]) { //DARI POST ORDER
    struct node* stack[100];
    int top = -1;
    int i = 0;
    while (postfix[i] != '\0') {
        char ch = postfix[i];
        if (ch >= 'A' && ch <= 'Z') {
            node* newNode = create(ch);
            stack[++top] = newNode;
        } else {
            node* newNode = create(ch);
            newNode->right = stack[top--]; //GAK BOLEH KETUKER LEFT dan RIGHT nya, RIGHT = B
            newNode->left = stack[top--];	//LEFT = A
            stack[++top] = newNode;			//A operator B
        }
        i++;
    }
    return stack[top--];
}

node* construct_tree_prefix(char prefix[]) { //INI prefix
    struct node* stack[100];
    int top = -1;
//    int i = 0;
    int i = strlen(prefix) - 1;
    while (i >= 0) {
        char ch = prefix[i];
        if (ch >= 'A' && ch <= 'Z') {
            node* newNode = create(ch);
            stack[++top] = newNode;		//++top, karena mulai dari -1 dan kita mau ke idx 0
        } else {
            node* newNode = create(ch);
            newNode->left = stack[top--];
            newNode->right = stack[top--];
            stack[++top] = newNode;
        }
        i--;
    }
    return stack[top--];
}

int is_operator(char data){
    switch (data) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 1;
        case '/': return 1;
        case '^': return 1;
        default : return 0;
    } 
}

void inorderTraversal(node* root) {
    if (root == NULL) return;
    
    if(is_operator(root->item)) putchar('(');
    inorderTraversal(root->left);
    printf("%c", root->item);
    inorderTraversal(root->right);
    if(is_operator(root->item)) putchar(')');
}

void preorderTraversal(node* root) {
    if (root == NULL) return;
    printf("%c", root->item);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(node* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%c", root->item);
}

int main() {
    char postfix[] = "ABC*+D/";
    char prefix[] = "/+A*BCD";
//    node* root = construct_tree_postfix(postfix);
    node* root = construct_tree_prefix(prefix);
    
    printf("Inorder traversal of expression tree:\n");
    inorderTraversal(root);
    
    printf("\n\nPreorder traversal of expression tree:\n");
    preorderTraversal(root);
    
    printf("\n\nPostorder traversal of expression tree:\n");
    postorderTraversal(root);
    return 0;
}
