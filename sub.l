%{
#include <stdio.h>
int expected = -1;
int flag = 1;

int yywrap(void) {
    return 1;
}
%}

%%
0  {
    if (expected == -1) {
        expected = 1;
    } else if (expected != 0) {
        flag = 0;
    } else {
        expected = 1;
    }
}

1  {
    if (expected == -1) {
        expected = 0;
    } else if (expected != 1) {
        flag = 0;
    } else {
        expected = 0;
    }
}

[^01\n] {
    printf("Invalid input, not accepted!\n");
    flag = 0;
    yyterminate();
}

\n {
    if (flag == 1) 
        printf("Accepted\n");
    else
        printf("Not Accepted\n");
    expected = -1;
    flag = 1;
}

%%

int main() {
    yylex();
    return 0;
}
