#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//typedef struct Node {
//	char* name;
//	int isPenutup;	
//}Node;

//kaga bisa pakai 2 stack karena harus real time pakai 1 stack, kalau 
//bisa juga pakai strtok cuma harus paham dulu strtok(null,""), null nya itu dari ketika " "
int main() {
	
	char line[100];
	scanf("%[^\n]", line);
//	printf("line: %s\n", line);
	int n = strlen(line);
	
//	char stackbuka[100];
//	char stacktutup[100];
//	int idxbuka = 0;
//	int idxtutup = 0;
	
	char stack[100][100];
	int top = -1;
	
	int isValid = 1;
	int i = 0;
	while (i <= n) {
		if (line[i] == ' ') {
			i++;
			continue;
		}
		if (line[i] == '<') {

			i++;
			
			//cek apakah closing tag
			int isClosing = 0;
			if (line[i] == '/') {
				isClosing = 1;
				i++;
				
			}
			
			//buat string tag name buat dimasukin di stack
			char tag[50];
			int j = 0;;
			while (line[i] != '>' && line[i] != '\0') {
				tag[j] = line[i];
				i++;
				j++;
			}
			tag[j] = '\0';
			
			//KALAU TAG TUTUP
			if (isClosing == 1) {
				//kalau masih kosong (top = -1) tapi langsung closing
				if (top == -1) {
					isValid = 0;
					break;
				}
				
				//kalau kaga sama dengan yang ada ditop ya salah dong
				if (strcmp(stack[top], tag) != 0) {
					isValid = 0;
					break;
				}
				else {
					top--; //ini POP ketika tag buka = tag tutup
				}
			}
			
			//KALAU TAG BUKA
			else {
				strcpy(stack[++top], tag);
			}
			
		}
		
		i++;
	}
	
//	printf("buka : %s\n", stackbuka);
//	printf("tutup : %s\n", stacktutup);
//	
//	int lenbuka = strlen(stackbuka);
//	int lentutup = strlen(stacktutup);
//	
//	if (lenbuka != lentutup) {
//		isValid = 0;
//	}
//	
//	for (int i = 0; i < lenbuka; i++) {
//		printf("stack buka %c\n",stackbuka[lenbuka - i - 1] );
//		printf("stack tutup %c\n", stacktutup[i]);
//		if (stackbuka[lenbuka - i - 1] != stacktutup[i]) {
//			isValid = 0;
//			break;
//		}
//	}
	
	if (isValid == 0) {
		printf("INVALID");
	}
	else {
		printf("VALID");
	}
	
	return 0;
}



