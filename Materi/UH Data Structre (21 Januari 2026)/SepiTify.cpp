#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//kalau [^\n] dikasi spasi aja sebelumnya " %[^\n]" 

typedef struct song{
	int time;
	char* title;
	char* name;
	char* id;
}Info;

typedef struct Node {
	Info data
	Node* next;
	Node* prev;
} Node;

Node* createNode(Info data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
}

Node* pushTail(Node* head, Info data) {
	Node* newNode = createNode(data);
	
	if (head == NULL) {
		head = newNode;
		return head;
	}
	
	Node* curr = head;
	while(curr->next != NULL) {
		curr = curr->next;
	}
	
	newNode->prev = curr;
	curr->next = newNode;
	return head;
	
	
}

void free_data(Node *del){
	free(del->name);
	free(del->id);
	free(del->title);
	free(del);
}

Node* popbyTitle(Node* head, const char* title) {
	if (head == NULL) {
		printf("kaga ada woi");
		getchar();
		return head;
	}
	
	if (strcmp(head->title, title) == 0) {
		Node* del = head; //JANGAN LUPA WOI, BUAT VARIABEL DEL DULU SUPAYA KAGA hilang pas null
		head = head->next;
		free_data(del);
		return head;
	}
	
	if (head->next == NULL && strcmp(head->title, title) == 0) { //KALAU CUMA 1 NODE dan itu yang ingin di apus
		Node* del = head;
		free_data(del);
		head = NULL;
		return head;
		
	}
	
	Node* curr = head;
	while (curr != NULL && strcmp(curr->title, title) != 0) {
		curr = curr->next;
	}
	
	if (curr == NULL ){
		printf("value tidak ditemukan");
		getchar();
		return head;
	}
	
	Node* del = curr;
	curr->prev->next = del->next;
	curr->next->prev = del->prev;
	free_data(del);
	
	return head;
}

Node* addNext(Node* head, Node* curr, Info data) {
	Node* newNode = createNode(data);
	
	newNode->prev = curr;
	newNode->next = curr->next;
	if (curr->next != NULL) {
		curr->next->prev = newNode;
	}
	curr->next = newNode;
	return head;
}



void view(Node* head) {
	if (head == NULL) {
		printf("There are no song\n");
		return;
	}
	
	Node* curr = head;
	int i = 1;
	while (curr != NULL) {
		printf("%d. Title: %s\n   Artist: %s\n", i++, curr->title, curr->name);
		curr = curr->next;
	}
	
	
}

Node* menuAdd(Node* head) {
//	system("cls");
	Info b;
	printf("Input song title: ");
	scanf(" %[^\n]", b.nama);
	printf("Input artis: ");
	scanf(" %[^\n]", b.artis); 
	printf("Input duration: ");
	scanf("%d", &b.dur);	getchar();
	printf("Input song id: ");
	scanf(" %[^\n]", b.id); 
	
	head = pushTail(head, b);
	return head;
}

//yang di return nilai curr nanti
Node* menuChange(Node* head, Node* curr) {
	int ops;
	if (curr == NULL) {
		curr = head;
	}
	
	printf("Current song: \"%s\" by %s\n\n", curr->title, curr->name);
	printf("1. Previous song\n");
	printf("2. Next song\n");
	printf("3. Exit\n");
	printf("Input: ");
	scanf("%d", &ops);
	switch (ops) {
		case 1: 
			if (curr->prev == NULL) {
				printf("Kaga ada\n");
				return curr;
			}
			else {
				curr = curr->prev;
				printf("Current song: \"%s\" by %s", curr->title, curr->name);
			}
			break;
		case 2:
			if (curr->next == NULL) {
				printf("Kaga ada\n");
				return curr;
			}
			else {
				curr = curr->next;
				printf("Current song: \"%s\" by %s", curr->title, curr->name);
			}
			break;
		case 3: return curr;
			break;
	}
	
	
	getchar();
	return curr;
}

Node* menuPop(Node* head) {
	char str[100];
	view(head);
	printf("Input song title: ");
	scanf(" %[^\n]", str);
	head = popbyTitle(head, str );
	return head;
}

Node* menuNext(Node* head, Node* curr) {
//	char str[100];
	printf("Current song: \"%s\" by %s", curr->title, curr->name);
	printf("Input song title: ");
	char nama[100];
	char id[6];
	char artis[100];
	int dur;
	printf("Input song title: ");
	scanf(" %[^\n]", nama);
	printf("Input artis: ");
	scanf(" %[^\n]", artis); 
	printf("Input duration: ");
	scanf("%d", &dur);	getchar();
	printf("Input song id: ");
	scanf(" %[^\n]", id); 
	addNext(head, curr, nama, artis, id, dur);
	return head;
	
}



int main() {
	
	int opt;
	Node* head = NULL;
	Node* now = NULL;
	
	do {
		//system("cls");
		printf("====================\n");
		printf("Playlist song:\n");
		view(head);
		printf("=====================\n");
		printf("1. Add song\n");
		printf("2. Change song\n");
		printf("3. Remove song\n");
		printf("4. Add to Up Next\n");
		printf("5. Exit\n");
		printf("Input: ");
		scanf("%d", &opt); getchar();
		
		switch (opt) {
			case 1: head = menuAdd(head);
				break;
			case 2: now = menuChange(head, now);
				break;
			case 3: head = menuPop(head);
				break;
			case 4: head = menuNext(head, now);
				break;
			case 5: printf("Exiting...");
				break;
			default:
				break;
		}
	}  while(opt != 5);
	
	
	
	return 0;
}
