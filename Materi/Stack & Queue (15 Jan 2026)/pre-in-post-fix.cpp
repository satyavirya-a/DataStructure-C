#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100
#define MAX_STRING_SIZE 1000

// Stack implementation for characters
typedef struct {
    char items[MAX_STACK_SIZE];
    int top;
} CharStack;

// Stack implementation for strings
typedef struct {
    char items[MAX_STACK_SIZE][MAX_STRING_SIZE];
    int top;
} StringStack;

void initCharStack(CharStack *s) {
    s->top = -1;
}

void initStringStack(StringStack *s) {
    s->top = -1;
}

int isCharStackEmpty(CharStack *s) {
    return s->top == -1;
}

int isStringStackEmpty(StringStack *s) {
    return s->top == -1;
}

void charPush(CharStack *s, char ch) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->items[++(s->top)] = ch;
    }
}

char charPop(CharStack *s) {
    if (!isCharStackEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

char charTop(CharStack *s) {
    if (!isCharStackEmpty(s)) {
        return s->items[s->top];
    }
    return '\0';
}

void stringPush(StringStack *s, const char *str) {
    if (s->top < MAX_STACK_SIZE - 1) {
        strcpy(s->items[++(s->top)], str);
    }
}

void stringPop(StringStack *s, char *result) {
    if (!isStringStackEmpty(s)) {
        strcpy(result, s->items[(s->top)--]);
    } else {
        result[0] = '\0';
    }
}

void stringTop(StringStack *s, char *result) {
    if (!isStringStackEmpty(s)) {
        strcpy(result, s->items[s->top]);
    } else {
        result[0] = '\0';
    }
}

int precedence(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return -1;
}

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void INFIX_POSTFIX(const char *s, char *result) {
    CharStack st;
    initCharStack(&st);
    int idx = 0;
    
    for (int i = 0; s[i] != '\0'; i++) {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || 
            (s[i] >= '0' && s[i] <= '9')) {
            result[idx++] = s[i];
        } else if (s[i] == '(') {
            charPush(&st, '(');
        } else if (s[i] == ')') {
            while (!isCharStackEmpty(&st) && charTop(&st) != '(') {
                result[idx++] = charPop(&st);
            }
            charPop(&st); // Remove '('
        } else {
            while (!isCharStackEmpty(&st) && precedence(s[i]) <= precedence(charTop(&st))) {
                result[idx++] = charPop(&st);
            }
            charPush(&st, s[i]);
        }
    }
    
    while (!isCharStackEmpty(&st)) {
        result[idx++] = charPop(&st);
    }
    
    result[idx] = '\0';
}

void INFIX_PREFIX(const char *s, char *result) {
    char reversed[MAX_STRING_SIZE];
    strcpy(reversed, s);
    reverseString(reversed);
    
    // Swap parentheses
    for (int i = 0; reversed[i] != '\0'; i++) {
        if (reversed[i] == ')') reversed[i] = '(';
        else if (reversed[i] == '(') reversed[i] = ')';
    }
    
    CharStack st;
    initCharStack(&st);
    int idx = 0;
    char tempResult[MAX_STRING_SIZE];
    
    for (int i = 0; reversed[i] != '\0'; i++) {
        if ((reversed[i] >= 'a' && reversed[i] <= 'z') || 
            (reversed[i] >= 'A' && reversed[i] <= 'Z') || 
            (reversed[i] >= '0' && reversed[i] <= '9')) {
            tempResult[idx++] = reversed[i];
        } else if (reversed[i] == '(') {
            charPush(&st, '(');
        } else if (reversed[i] == ')') {
            while (!isCharStackEmpty(&st) && charTop(&st) != '(') {
                tempResult[idx++] = charPop(&st);
            }
            charPop(&st); // Remove '('
        } else {
            while (!isCharStackEmpty(&st) && precedence(reversed[i]) < precedence(charTop(&st))) {
                tempResult[idx++] = charPop(&st);
            }
            charPush(&st, reversed[i]);
        }
    }
    
    while (!isCharStackEmpty(&st)) {
        tempResult[idx++] = charPop(&st);
    }
    
    tempResult[idx] = '\0';
    reverseString(tempResult);
    strcpy(result, tempResult);
}

void PREFIX_INFIX(const char *s, char *result) {
    StringStack st;
    initStringStack(&st);
    
    for (int i = strlen(s) - 1; i >= 0; i--) {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || 
            (s[i] >= '0' && s[i] <= '9')) {
            char temp[2] = {s[i], '\0'};
            stringPush(&st, temp);
        } else {
            char op1[MAX_STRING_SIZE], op2[MAX_STRING_SIZE];
            stringPop(&st, op1);
            stringPop(&st, op2);
            
            char temp[MAX_STRING_SIZE];
            snprintf(temp, sizeof(temp), "(%s%c%s)", op1, s[i], op2);
            stringPush(&st, temp);
        }
    }
    
    stringPop(&st, result);
}

void POSTFIX_INFIX(const char *s, char *result) {
    StringStack st;
    initStringStack(&st);
    
    for (int i = 0; s[i] != '\0'; i++) {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || 
            (s[i] >= '0' && s[i] <= '9')) {
            char temp[2] = {s[i], '\0'};
            stringPush(&st, temp);
        } else {
            char op1[MAX_STRING_SIZE], op2[MAX_STRING_SIZE];
            stringPop(&st, op1);
            stringPop(&st, op2);
            
            char temp[MAX_STRING_SIZE];
            snprintf(temp, sizeof(temp), "(%s%c%s)", op2, s[i], op1);
            stringPush(&st, temp);
        }
    }
    
    stringPop(&st, result);
}

void PREFIX_POSTFIX(const char *s, char *result) {
    StringStack st;
    initStringStack(&st);
    
    for (int i = strlen(s) - 1; i >= 0; i--) {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || 
            (s[i] >= '0' && s[i] <= '9')) {
            char temp[2] = {s[i], '\0'};
            stringPush(&st, temp);
        } else {
            char op1[MAX_STRING_SIZE], op2[MAX_STRING_SIZE];
            stringPop(&st, op1);
            stringPop(&st, op2);
            
            char temp[MAX_STRING_SIZE];
            snprintf(temp, sizeof(temp), "%s%s%c", op1, op2, s[i]);
            stringPush(&st, temp);
        }
    }
    
    stringPop(&st, result);
}

void POSTFIX_PREFIX(const char *s, char *result) {
    StringStack st;
    initStringStack(&st);
    
    for (int i = 0; s[i] != '\0'; i++) {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || 
            (s[i] >= '0' && s[i] <= '9')) {
            char temp[2] = {s[i], '\0'};
            stringPush(&st, temp);
        } else {
            char op1[MAX_STRING_SIZE], op2[MAX_STRING_SIZE];
            stringPop(&st, op1);
            stringPop(&st, op2);
            
            char temp[MAX_STRING_SIZE];
            snprintf(temp, sizeof(temp), "%c%s%s", s[i], op2, op1);
            stringPush(&st, temp);
        }
    }
    
    stringPop(&st, result);
}

int main() {
    char result[MAX_STRING_SIZE];
    
    printf("INFIX_POSTFIX: ");
    INFIX_POSTFIX("(3-2+1/8)-(4+6/3*(5^8))", result);
    printf("%s\n", result);
    
    printf("INFIX_PREFIX: ");
    INFIX_PREFIX("(3-2+1/8)-(4+6/3*(5^8))", result);
    printf("%s\n", result);
    
    printf("PREFIX_INFIX: ");
    PREFIX_INFIX("-+-32/18+4*/63^58", result);
    printf("%s\n", result);
    
    printf("POSTFIX_INFIX: ");
    POSTFIX_INFIX("32-18/+463/58^*+-", result);
    printf("%s\n", result);
    
    printf("PREFIX_POSTFIX: ");
    PREFIX_POSTFIX("-+-32/18+4*/63^58", result);
    printf("%s\n", result);
    
    printf("POSTFIX_PREFIX: ");
    POSTFIX_PREFIX("32-18/+463/58^*+-", result);
    printf("%s\n", result);
    
    printf("===============\n");
     printf("INFIX_POSTFIX: ");
    INFIX_POSTFIX("4+6*(5-2)/3", result);
    printf("%s\n", result);
    
    return 0;
}
