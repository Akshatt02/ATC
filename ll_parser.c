#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char G[MAX][MAX];  
char NT[MAX], T[MAX], FIRST[MAX][MAX], FOLLOW[MAX][MAX];
int nt = 0, t = 0, cr = 0;

void FIND_FIRST(char *, char);
void FIND_FOLLOW(char *, char);
void add_symbol(char *, char);

void main() {
    char first[MAX] = "", follow[MAX] = "";
    int i, j;
    
    printf("Enter number of production rules: ");
    scanf("%d", &cr);
    
    printf("Enter production rules (e.g., A->aB):\n");
    for (i = 0; i < cr; i++) {
        scanf("%s", G[i]);
        if (strchr(NT, G[i][0]) == NULL) {
            NT[nt++] = G[i][0];  // Collect non-terminals
        }
    }

    // Compute FIRST for all non-terminals
    for (i = 0; i < nt; i++) {
        first[0] = '\0';
        FIND_FIRST(first, NT[i]);
        strcpy(FIRST[i], first);
    }

    // Compute FOLLOW for all non-terminals
    for (i = 0; i < nt; i++) {
        follow[0] = '\0';
        FIND_FOLLOW(follow, NT[i]);
        strcpy(FOLLOW[i], follow);
    }

    // Display FIRST and FOLLOW sets
    printf("\nFIRST Sets:\n");
    for (i = 0; i < nt; i++) {
        printf("FIRST(%c) = { ", NT[i]);
        for (j = 0; FIRST[i][j] != '\0'; j++)
            printf("%c ", FIRST[i][j]);
        printf("}\n");
    }

    printf("\nFOLLOW Sets:\n");
    for (i = 0; i < nt; i++) {
        printf("FOLLOW(%c) = { ", NT[i]);
        for (j = 0; FOLLOW[i][j] != '\0'; j++)
            printf("%c ", FOLLOW[i][j]);
        printf("}\n");
    }

    // Select one production to create a table entry
    char non_terminal = G[0][0]; // Choose first non-terminal
    char terminal = FIRST[0][0]; // Choose first terminal from FIRST set

    // Display LL(1) Table Entry
    printf("\nLL(1) Table Entry for (%c, %c):\n", non_terminal, terminal);
    printf("####################\n");
    printf("#  %c  |  %c  #\n", non_terminal, terminal);
    printf("#     | %s #\n", G[0]);  // Production below the terminal
    printf("####################\n");
}

void FIND_FIRST(char *arr, char ch) {
    int i;
    if (!isupper(ch)) {  // If terminal, add to FIRST set
        add_symbol(arr, ch);
        return;
    }
    for (i = 0; i < cr; i++) {
        if (G[i][0] == ch) {
            if (G[i][3] == '\0' || G[i][3] == '!')  // If epsilon production
                add_symbol(arr, '!');
            else
                FIND_FIRST(arr, G[i][3]);  // Get first of next character
        }
    }
}

void FIND_FOLLOW(char *arr, char ch) {
    int i, j;
    if (G[0][0] == ch) add_symbol(arr, '$');  // Start symbol gets '$'

    for (i = 0; i < cr; i++) {
        for (j = 3; G[i][j] != '\0'; j++) {
            if (G[i][j] == ch) {
                if (G[i][j + 1] != '\0') {
                    FIND_FIRST(arr, G[i][j + 1]);
                } else {
                    FIND_FOLLOW(arr, G[i][0]);
                }
            }
        }
    }
}

void add_symbol(char *arr, char ch) {
    if (strchr(arr, ch) == NULL) {
        int len = strlen(arr);
        arr[len] = ch;
        arr[len + 1] = '\0';
    }
}