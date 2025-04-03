%{
#include <stdio.h>
int flag = 0;
int state = 0;
int yywrap(void) {
    return 1;
}
%}

%%
a  {
    if (state == 0) {
        state = 1;
    } else {
        state = 0;
    }
}

b  {
    if (state == 1) {
        state = 2;
    } else if (state == 2) {
        flag = 1;
        state = 0;
    } else {
        state = 0;
    }
}

[^ab\n] {
    state = 0;
}

\n {
    if (flag) {
        printf("Accepted!\n");
    } else {
        printf("Not Accepted!\n");
    }
    flag = 0;
    state = 0;
}

%%

int main() {
    yylex();
    return 0;
}
