#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//misal atributnya char id doang
void insert(char* id ) {
	Node* n = create(id);
	int idx = hashFunc(id);
	
	if (hashTable[idx] == NULL) {
		hashTable[idx] = n;
	}
	
	else {
		Node* curr = hashTable[idx];
		while (curr->next != NULL) {
			curr = curr->next;
		}
		
		curr->next = n;
	}
}


void pop(char* id) {
	int idx = hashFunc(id);
	
	if (hashTable[idx] == NULL) {
		printf("Not Found\n");
		return;
	}
	
	Node* prev = NULL;
	Node* curr = hashTable[idx];
	else {
		while(curr != NULL) {
			if (strcmp(curr->id, id) == 0) {
				if (prev == NULL) {
					hashTable[idx] = curr->next;
				}
				
				else {
					prev->next = curr->next;
				}
				
				free(curr);
				return;
			}
			
			prev = curr;
			curr = curr->next;
		}
	}
}

int main() {
	
	
	
	return 0;
}
