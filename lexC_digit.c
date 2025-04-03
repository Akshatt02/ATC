#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while"
};
int num = sizeof(keywords) / sizeof(keywords[0]);

int isKeyword(char *word) {
    for (int i = 0; i < num; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void tokenize(char *str) {
    char buffer[100];
    int index = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];
        if (isalnum(ch) || ch == '_') {
            buffer[index++] = ch;
        } else {
            if (index > 0) {
                buffer[index] = '\0';
                index = 0;
                if (isKeyword(buffer)) {
                    printf("Keyword: %s\n", buffer);
                } else if (isdigit(buffer[0])) {
                    printf("Number: %s\n", buffer);
                } else {
                    printf("Identifier: %s\n", buffer);
                }
            }
            if (strchr("+-*/=",ch)) {
                printf("Operator: %c\n", ch);
            } else if (strchr("=<>!", ch) && strchr("=<>!", str[i + 1])) {
                printf("Operator: %c%c\n", ch, str[i + 1]);
                i++;
            } else if (ispunct(ch) && ch != ' ') {
                printf("Symbol: %c\n", ch);
            }
        }
    }
}

int main() {
    char str[1000];
    printf("Enter source code: ");
    fgets(str, sizeof(str), stdin);
    tokenize(str);
    return 0;
}
