#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main () {
    int dfa = 0;
    char str[1000];

    printf("Enter the string: ");
    scanf("%s",str);

    for (int i=0; str[i] !='\0'; i++) {
        if (isalpha(str[i])) {
            if (str[i] == 'a' && dfa == 0) dfa = 1;
            else if (str[i] == 'b' && dfa == 0) dfa = 0;
            else if (str[i] == 'a' && dfa == 1) dfa = 1;
            else if (str[i] == 'b' && dfa == 1) dfa = 2;
            else if (str[i] == 'a' && dfa == 2) dfa = 1;
            else if (str[i] == 'b' && dfa == 2) dfa = 3;
            if (dfa == 3) break;
        } else {
            printf("Invalid Input!");
            exit(0);
        }
    }

    if (dfa == 3) printf("Accepted!");
    else printf("Not Accepted!");
}