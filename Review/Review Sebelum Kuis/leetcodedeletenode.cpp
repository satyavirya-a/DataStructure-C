#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definition for singly-linked list.
struct ListNode {
     int val;
     struct ListNode *next;
};

struct ListNode* removeElements(struct ListNode* head, int val) {
    if (head == NULL) {
        return NULL;
    }
    if (head->val == val && head->next == NULL) {
        free(head);
        head = NULL;
        return head;
    }

    if (head->val == val) {
        struct ListNode* del = head;
        head = head->next;
        free(del);
        return head;
    }

    struct ListNode* curr = head;
    while (curr->next != NULL) {
        if (curr->next->val == val) {
           struct ListNode* del = curr->next;
            curr->next = del->next;
            free(del);
        }
        curr = curr->next;
    }

    return head;
    
}

int main() {
	return 0;
}
