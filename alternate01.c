#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    int dfa = 0;
    char str[1000];
    printf("Enter the string: ");
    scanf("%s",str);
    int flag = 1;

    for (int i=0; i< strlen(str); i++) {
        if (str[i] != '0' && str[i] != '1') {
            printf("Invalid Input!");
            exit(0);
        }
    }

    for (int i=0; i < strlen(str); i++) {
        if (str[i] == '0' && dfa == 0) dfa = 1;
        else if (str[i] == '1' && dfa == 0) dfa = 2;
        else if (str[i] == '0' && dfa == 1) dfa = 5;
        else if (str[i] == '1' && dfa == 1) dfa = 3;
        else if (str[i] == '1' && dfa == 2) dfa = 5;
        else if (str[i] == '0' && dfa == 2) dfa = 4;
        else if (str[i] == '0' && dfa == 3) dfa = 1;
        else if (str[i] == '1' && dfa == 3) dfa = 5;
        else if (str[i] == '1' && dfa == 4) dfa = 2;
        else if (str[i] == '0' && dfa == 4) dfa = 5;
    }

    if (dfa != 5) printf("Accepted!");
    else printf("Not Accepted!");
}