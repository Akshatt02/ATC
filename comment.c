#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[1024];
    printf("Enter the line to check for comment: ");
    fgets(str,1024,stdin);

    int dfa = 0;

    for (int i=0; i<strlen(str); i++) {
        if (dfa == 0 && str[i] == '/') dfa = 1;
        else if (dfa == 0 && str[i] != '/') dfa = 6;

        else if (dfa == 1 && str[i] == '/') dfa = 2;
        else if (dfa == 1 && str[i] == '*') dfa = 3;
        else if (dfa == 1) dfa = 6;

        else if (dfa == 3 && str[i] == '*') dfa = 4;
        else if (dfa == 3) dfa = 3;

        else if (dfa == 4 && str[i] == '/') dfa = 5;
        else if (dfa == 4 && str[i] == '*') dfa = 4;
        else if (dfa == 4) dfa = 3;

    }
 
    if (dfa == 2) {
        printf("Single line comment!");
    } else if (dfa == 5) {
        printf("Multi Line comment!");
    } else {
        printf("Not a comment!");
    }

}