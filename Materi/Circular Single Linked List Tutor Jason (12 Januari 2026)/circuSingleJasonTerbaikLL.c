#include <stdio.h>
#include <stdlib.h>         //memory
#include <windows.h>

typedef struct Node {
    int value;
    struct Node* next;         

} Node;

Node* tail = NULL;      //global

Node* createNode(int inpValue){
    Node* newNode = (Node* ) malloc (sizeof(Node));         

    newNode->value = inpValue;
    newNode->next = NULL;
    return newNode;     
}

void pushHead(int inpValue){
    Node* newNode = createNode(inpValue);

    if (tail == NULL){          //kondisi pertama kali dibuat
        tail = newNode;         
        tail->next = tail;      //agar circular -> ngarah ke diri sendiri
    } else {                    //setelah udah ada dibuat
        newNode->next = tail->next;     
        tail->next = newNode;       //update circular nya
    }
}

void pushTail(int inpValue){
    Node* newNode = createNode(inpValue);

    if (tail == NULL){
        tail = newNode;
        tail->next = tail;              //circular
    } else {
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;                 //update tail nya
    }

}

void viewList(){
    Node* curr = tail->next;            //anggap aja kaya head
    
    while (curr != tail){
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
    printf("%d\n", curr->value);            //nge print node terakhir
}

//push mid by value         
//push mid by position

void pushByVal(int inpValue){           //besaran value 
    if (tail == NULL || inpValue <= tail->next->value){            //cek value head nya
        pushHead(inpValue);
        return;
    } else if (inpValue >= tail->value){       //cek value tail
        pushTail(inpValue);
        return;
    } else {
        //traversing
        Node* curr = tail->next;        //head
        while (curr != tail && inpValue > curr->next->value){           //cek value setelahnya
            curr = curr->next;
        }
        Node* newNode = createNode(inpValue);

        //nge-wire newNode dan curr dan setelahnya
        newNode->next = curr->next;
        curr->next = newNode;   
    }
}

void pushByPos(int inpVal, int pos){
    if (pos < 1){
        printf("Posisi tidak valid!\n");
        return;
    }
    
    if (pos == 1){
        pushHead(inpVal);
        return;
    }

    Node* curr = tail->next;              //curr nya mulai dari head
    int count = 1;                        //starting position nya di node ke 1
    //traversing
    while (curr != tail && count != pos-1){
        curr = curr->next;                      //jalan kedepan selama belum pos-1 dan belum mentok
        count++;
    }

    if (curr == tail && count != pos-1){         //kalau udah mentok tapi posisinya ga di tempat seharusnya
        printf("Posisi tidak valid!\n");
        return;
    }

    if (curr == tail && count == pos-1){        //udah mentok tapi posisi nya udah bener
        pushTail(inpVal);
        return;
    }

    //wiring
    //insert di mid
    Node* newNode = createNode(inpVal);
    newNode->next = curr->next;
    curr->next = newNode;
}

void popHead(){
    if (tail == NULL){
        printf("List kosong!\n");
        return;
    }

    Node* head = tail->next;            //circular
    tail->next = head->next;
    free(head);
}

void popTail(){
    if (tail == NULL){
        printf("List nya kosong!\n");
        return;
    }

    Node* curr = tail->next;     
    Node *prev = tail;    

    
    while (curr->next != tail){         
        curr = curr->next;
    }

    curr->next = tail->next; 
    
    tail->next = NULL;
    free(tail); 
    tail = curr;
}

void popByVal(int inpVal){
    if (tail == NULL){
        printf("List nya kosong!\n");
        return;
    }

    if (inpVal == tail->value){
        popTail();
        return;
    } 

    Node* head = tail->next;            //variabel lokal
    if (inpVal == head->value){
        popHead();
        return;
    }

    Node* curr = tail->next;            //head
    while (curr != tail && inpVal != curr->next->value){            //selama ga mentok
        curr = curr->next;          //update
    }

    if (curr == tail && inpVal != tail->value){
        printf("Value ga ketemu\n");
        return;
    }

    //kondisi nya ada di tengah
    Node* temp = curr->next;
    curr->next = temp->next;
    free(temp);      
}

void popByPos(int pos){
    if (tail == NULL){
        printf("List nya kosong!\n");
        return;
    }

    if (pos < 1){
        printf("Posisi nya invalid\n");
        return;
    }
        

    if (pos == 1){
        popHead();
        return;
    }
    
    Node* curr = tail->next;           //head
    int count = 1;

    //traverse
    while (curr != tail && count != pos-1){
        curr = curr->next;
        count++;
    }

    if (curr == tail && count != pos-1){
        printf("Tidak ada node di posisi itu\n");
        return;
    }

    if (curr == tail && count == pos-1){
        popTail();
        return;
    }

    //wiring di tengah
    Node* temp = curr->next;            //yang pengen kita delete
    curr->next = temp->next;
    free(temp);
}


int main () {
    pushByVal(10);
    pushByVal(5);
    pushByVal(40);

    pushByPos(8, 2);

    viewList();
    popByVal(8);
    viewList();
    
    popByPos(3);
    viewList();

    return 0;
}