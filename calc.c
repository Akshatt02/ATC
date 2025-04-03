#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char stack[1000];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
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

        if (isdigit(ch)) {  
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        }
        else if (ch == '(') {
            push(ch);
        }
        else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
                postfix[j++] = ' ';
            }
            pop();
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (top != -1 && precedence(stack[top]) >= precedence(ch)) {
                postfix[j++] = pop();
                postfix[j++] = ' ';
            }
            push(ch);
        }
        i++;
    }
    
    while (top != -1) {  
        postfix[j++] = pop();
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

int evaluatePostfix(char *postfix) {
    int stack[1000], top = -1, num;
    int i = 0;

    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {  
            num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i++] - '0');
            }
            stack[++top] = num;
        }
        else if (postfix[i] != ' ') {  
            int b = stack[top--];
            int a = stack[top--];

            switch (postfix[i]) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = a / b; break;
            }
        }
        i++;
    }
    return stack[top];
}

int main() {
    char infix[100], postfix[100];

    printf("Enter an expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = 0;

    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);
    printf("Result: %d\n", evaluatePostfix(postfix));

    return 0;
}
