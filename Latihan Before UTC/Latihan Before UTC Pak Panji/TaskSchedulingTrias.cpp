#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
    int data;
    int time;
    node* next;
}node;

node* makeNode(int data, int time){
    node* add = (node*)malloc(sizeof(node));
    
    add->data = data;
    add->time = time;
    add->next = NULL;
    
    return add;
}


node* push(node* head, int data, int time){
    if(head == NULL){
        head = makeNode(data,time);
        head->next = head;
        return head;
    }
    
    node* curr = head;
    
    while(curr->next != head){
        curr = curr->next;
    }
    
    if(curr->next == head){
        curr->next = makeNode(data,time);
        curr->next->next = head;
        return head;
    }
    
//    else{
//        node* add = makeNode(data,time);
//        add->next = curr->next;
//        curr->next = add;
//        return head;
//    }
}

void pop(node* head, int max, int n){
    node* curr = head;
    node* start = head;
    int node_processed = 0;
    while(head != NULL && node_processed < n){
        if(curr->time <= max){ 
            node_processed++;
//            printf("%d",node_processed);
            if(curr == start){
                node* prev = head;
                while(prev->next != head){
                    prev = prev->next;
                }
                
                head = head->next;
                printf("%d ",curr->data);
                free(curr);
                prev->next = head;
                // update ke head baru
                curr = head;
                start = head;
                continue;
            }
            
            if(curr->next == start){
                node* prev = head;
                while(prev->next != curr){
                    prev = prev->next;
                }
                prev->next = head;
                printf("%d ",curr->data);
                free(curr);
                continue;
            }
            else{
                node* prev = head;
                while(prev->next != curr){
                    prev = prev->next;
                }
                prev->next = curr->next;
                printf("%d ",curr->data);
                free(curr);
                //update curr
                curr = prev->next;
            }
        }
        
        else{
            curr->time -= max;
            curr = curr->next;
        }
    }
}

int main(){

    node* head = NULL;
    
    int n,max;
    scanf("%d %d",&n,&max);
    
    for(int i = 0;i<n;i++){
        int data,time;
        scanf("%d %d",&data,&time);
        head = push(head,data,time);
    }
    
    pop(head,max,n);

	return 0;
}
