/* 
AVL TREE
BST + Balance Factor = |height(left) - height(right)| <= 1
must be balance between left child and right child

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    int height;
    Node* left;
    Node* right;
}Node;

// === BALANCE FACTOR  ===
int getHeight(Node* root){
    if (!root){
        return 0;
    }
    return root->height;    
}
int getBalance(Node* root){
    if (!root) return 0;
    return getHeight(root->left) - getHeight(root->right);
}
int max(int a, int b){
    return (a > b) ? a : b;     //ternary
}
Node* updateHeight(Node* root){
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    return root;
}
// === BALANCE FACTOR  ===  


// === 4 ROTATIONS TO FIX IMBALANCE ===
/* 1. Left-Left(LL) = Right Rotation
    z               y
   / \            /   \
  y   T4   →     x     z
 / \            / \   / \
x   T3         T1 T2 T3 T4
*/
Node* rightRotate(Node* z){
    Node* y = z->left;          //define
    Node* T3 = y->right;        //define 

    y->right = z;               //view from y
    z->left = T3;               //view from z

    updateHeight(z);
    updateHeight(y);
    return y;
}

/*2. Right-Right (RR) = Left Rotation
    z                 y
  /  \               / \
T1    y       →     z   x
    /  \           / \ / \
   T2   x        T1 T2 T3 T4
*/
Node* leftRotate(Node* z){
    Node* y = z->right;             //define
    Node* T2 = y->left;

    y->left = z;                    //view from y
    z->right = T2;                  //view from z

    updateHeight(z);
    updateHeight(y);
    return y;
}

/*3. Left-Right (LR) = Left + Right Rotation
    z           z           x
   / \         / \         / \
  y   T4  →   x   T4  →   y   z
 / \         / \         / \ / \
T1  x       y   T3      T1 T2 T3 T4
   / \     / \
  T2 T3   T1 T2

*/
Node* leftRightRotate(Node* z){
    z->left = leftRotate(z->left);
    return rightRotate(z);              //jadi root
}

/*4. Right-Left(RL) = Right + Left Rotation
z             z               x
 \           / \             / \
  y    →    T1  y     →     z   y
 / \           / \         / \ / \
x   T4        x   T4      T1 T2 T3 T4
*/
Node* rightLeftRotate(Node* z){
    z->right = rightRotate(z->right);
    return leftRotate(z);
}
// === 4 ROTATION TO FIX IMBALANCE ===


Node* createNode(int data){
    Node* newNode = (Node* ) malloc (sizeof(Node));
    newNode->data = data;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* fixImbalance(Node* root, int data){
	updateHeight(root);
    int balance = getBalance(root);

    //LL - Right rotate
    if (balance > 1 && data < root->left->data){
        return rightRotate(root);
    }

    //RR 
    if (balance < -1 && data > root->right->data){
        return leftRotate(root);
    }

    //LR
    if (balance > 1 && data > root->left->data){
        return leftRightRotate(root);
    }

    //RL
    if (balance < -1 && data < root->right->data){
        return rightLeftRotate(root);
    }
    return root;
}

Node* insert(Node* root, int data){
    if (!root)
        return createNode(data);

    if (data < root->data){
        root->left = insert(root->left, data);
    } else if (data > root->data){
        root->right = insert(root->right, data);
    } else {
        return root;
    }
    return fixImbalance(root, data);
}

Node* minVal(Node* root){
	if (root == NULL) return NULL;
	while (root->left != NULL)
		root = root->left;
	return root;
}

Node* deleteNode(Node* root, int key){
    if (!root) return root;
    
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Found - handle cases
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node* temp = minVal(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    
    if (root == NULL) return root;
    
    return fixImbalance(root, key);  
}

int main () {
    Node* root = NULL;
	




    return 0;
}
