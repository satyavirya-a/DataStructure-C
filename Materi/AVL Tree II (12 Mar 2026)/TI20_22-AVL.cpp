#include<stdio.h>
#include<stdlib.h>

struct node{
    int key;
    int height;
    struct node *left;
    struct node *right;
};

struct node *newNode(int x){
    struct node *curr = (struct node *) malloc(sizeof(struct node));
    curr->key = x;
    curr->height = 1;
    curr->left = NULL;
    curr->right = NULL;
    return curr;
}

int max(int left, int right){
    if(right > left) {
      return right;
    }else {
      return left;
    }
}

int getHeight(struct node *root){
    if(root == NULL) {
      return 0;
    }else {
      return root->height;
    }
}

int getBF(struct node *root){
    if(root == NULL) {
      return 0;
    }else {
      return getHeight(root->left) - getHeight(root->right);
    }
}

/*
        T*              S
       /        =>    /   \
      S*             A     T
     /   \                /  
    A     B*             B    
*/

struct node *rightRotate(struct node *T){
    struct node *S = T->left;
    struct node *B = S->right;

    //rotate
    S->right = T;
    T->left = B;

    T->height = max(getHeight(T->left), getHeight(T->right)) + 1;
    S->height = max(getHeight(S->left), getHeight(S->right)) + 1;

    return S;
}

/*
      T*                  S
       \        =>      /  \
        S*             T    C
       / \              \
      B*  C              B
*/

struct node *leftRotate(struct node *T){
    struct node *S = T->right;
    struct node *B = S->left;

    //rotate
    S->left = T;
    T->right = B;

    T->height = max(getHeight(T->left), getHeight(T->right)) + 1;
    S->height = max(getHeight(S->left), getHeight(S->right)) + 1;

    return S;
}

struct node *insert(struct node *root, int key){
    if(root == NULL) return newNode(key);
    else if(key < root->key){
        root->left = insert(root->left, key);
    }else{
        root->right = insert(root->right, key);
    }

    root->height = max(getHeight(root->left), getHeight(root->right))+1;
    int bFactor = getBF(root);

  /*
      9           5
     /           / \
    5       =>  3   9
   /
  3
  */
    if(bFactor > 1 && key < root->left->key)
        return rightRotate(root);
  /*
    4             6
     \          /   \
      6     =>  4    8 
       \
        8
  */
    if(bFactor < -1 && key > root->right->key){
        return leftRotate(root);
    }

  /*
      9             9           7
     /             /          /   \
    5      =>     7      =>  5     9
     \           /
      7         5
  */
    if(bFactor > 1 && key > root->left->key){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

  /*
    4         4               5
     \         \            /  \
      6   =>    5     =>   4    6
      /          \
     5            6
  */
    if(bFactor < -1 && key < root->right->key){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

// left subtree, get the highest
struct node *predecessor(struct node *root){
    struct node *curr = root->left;
    while(curr->right){
        curr = curr->right;
    }
    return curr;
}

//right subtree, get the smallest
struct node *successor(struct node *root){
    struct node *curr = root->right;
    while(curr->left){
        curr = curr->left;
    }
    return curr;
}

struct node *deleteVal(struct node *root, int key){
    if(root == NULL) return NULL;
    else if(key < root->key)
        root->left = deleteVal(root->left, key);
    else if(key > root->key)
        root->right = deleteVal(root->right, key);
    else{
        if(root->left == NULL || root->right == NULL){
            struct node *temp;
            if(root->left) temp = root->left;
            else temp = root->right;

            if(!temp){//temp == NULL
                temp = root;
                root = NULL;
            }else{
                *root = *temp;
            }
            free(temp);
        }else{
            struct node *temp = predecessor(root);
            root->key = temp->key;
            root->left = deleteVal(root->left, temp->key);
        }
    }

    if(root == NULL) return root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int bFactor = getBF(root);

  /*
         8                 8             5   
        / \               /            /  \
       5   (9)    =>     5       =>   3    8
      /                 /
     3                 3
  */
    if(bFactor > 1 && getBF(root->left) >= 0)
        return rightRotate(root);

  /*
      4            4              6
     / \            \            /  \
   (2)  6     =>     6      =>  4    8
         \            \
          8            8
  */
    if(bFactor < -1 && getBF(root->right) <= 0)
        return leftRotate(root);

  /*
      8              8           8          7
    /  \            /           /          / \
   5    (9)   =>   5      =>   7      =>  5   8
    \               \         /
     7               7       5
  */
    if(bFactor > 1 && getBF(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

  /*
      4          4           4               5
    /  \          \           \            /  \
  (2)   6    =>    6     =>    5      =>  4    6
       /          /             \
      5          5               6
  */
    if(bFactor < -1 && getBF(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void printpre(struct node *root){
    if(root == NULL) return;
    printf("%d ", root->key);
    printpre(root->left);
    printpre(root->right);
}

void print(struct node *root){
    if(root == NULL) return;
    print(root->left);
    printf("%d ", root->key);
    print(root->right);
}

void printpost(struct node *root){
    if(root == NULL) return;
    printpost(root->left);
    printpost(root->right);
    printf("%d ", root->key);
}

struct node *freeAll(struct node *root){
    if(root == NULL) return NULL;
    root->left = freeAll(root->left);
    root->right = freeAll(root->right);
    free(root);
    return NULL;
}

int main(){
    struct node *root = NULL;

    //right rotate
    root = insert(root, 50);
    root = insert(root, 40);
    root = insert(root, 30);
    print(root); //30, 40, 50
    puts("");
    root = freeAll(root);

    //left rotate
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 70);
    print(root); //50, 60, 70
    puts("");
    root = freeAll(root);

    //left right rotate
    root = insert(root, 50);
    root = insert(root, 25);
    root = insert(root, 45);
    print(root); //25, 45, 50
    puts("");
    root = freeAll(root);

    //right left rotate
    root = insert(root, 50);
    root = insert(root, 85);
    root = insert(root, 75);
    print(root); //50, 75, 85
    puts("");
    root = freeAll(root);

/*
        50                50
       /  \              /  \
     35     65          38  65
       \               /  \
       38             35  40
         \
         40
 */
    root = insert(root, 50);
    root = insert(root, 35);
    root = insert(root, 65);
    root = insert(root, 38);
    root = insert(root, 40);
    print(root); //35, 38, 40, 50, 65
    puts("");
    
/*
        50            50           40
       /  \          /            /  \
      38  65        38           38  50
     /  \          /  \          /
    35  40        35  40        35

 */

    root = deleteVal(root, 65);
    print(root);//35, 38, 40, 50
    puts("");

    root = freeAll(root);
    return 0;
}
