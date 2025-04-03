#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

char opStack[MAX];
int opTop = -1;

void pushOp(char c) {
    opStack[++opTop] = c;
}

char popOp() {
    return opStack[opTop--];
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char ch = infix[i];

        if (isalnum(ch)) {
            while (isalnum(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        }
        else if (ch == '(') {
            pushOp(ch);
        }
        else if (ch == ')') {
            while (opTop != -1 && opStack[opTop] != '(') {
                postfix[j++] = popOp();
                postfix[j++] = ' ';
            }
            popOp();
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (opTop != -1 && precedence(opStack[opTop]) >= precedence(ch)) {
                postfix[j++] = popOp();
                postfix[j++] = ' ';
            }
            pushOp(ch);
        }
        i++;
    }
    while (opTop != -1) {
        postfix[j++] = popOp();
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

void generateAssembly(char *postfix) {
    char regStack[MAX][10];
    int regTop = -1;
    int regCount = 0;

    char op[MAX];
    int i = 0, j = 0;

    while (postfix[i] != '\0') {
        if (isalnum(postfix[i])) {
            j = 0;
            while (isalnum(postfix[i])) {
                op[j++] = postfix[i++];
            }
            op[j] = '\0';
            strcpy(regStack[++regTop], op);
        }
        else if (postfix[i] != ' ') {
            char b[10], a[10];
            strcpy(b, regStack[regTop--]);
            strcpy(a, regStack[regTop--]);

            printf("MOV R%d, %s\n", regCount, a);

            switch (postfix[i]) {
                case '+': printf("ADD R%d, %s\n", regCount, b); break;
                case '-': printf("SUB R%d, %s\n", regCount, b); break;
                case '*': printf("MUL R%d, %s\n", regCount, b); break;
                case '/': printf("IDIV R%d, %s\n", regCount, b); break;
            }

            char regName[10];
            sprintf(regName, "R%d", regCount++);
            strcpy(regStack[++regTop], regName);
        }
        i++;
    }
    char word[100];
    int xx = 0;
    for (int i = 0; postfix[i] != ' '; i++) {
        word[xx++] = postfix[i];
    }
    word[xx] = '\0';
    printf("MOV %s, %s\n",word, regStack[regTop]);
}
 
int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter an expression: ");
    fgets(infix, sizeof(infix), stdin);

    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    printf("\nGenerated Assembly Code:\n");
    generateAssembly(postfix);

    return 0;
}
