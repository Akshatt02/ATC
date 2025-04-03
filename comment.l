%{
#include <stdio.h>

int state = 0;

int yywrap(void) {
    return 1;
}

%}

%%

"/" {
    if (state == 0) {
        state = 1;
    }
    else if (state == 1) state = 2;
    else if (state == 4) state = 5;
}

"*" {
    if (state == 0) state = 6;
    else if (state == 1) {
        state = 3;
    } else if (state == 4){
        state = 4;
    } else if (state == 3) {
        state = 4;
    }
}

[^/*\n] {
    if (state == 0) state = 6;
    else if (state == 1) state = 6;
    else if (state == 3) state = 3;
    else if (state == 4) state = 3;
}

"\n" {
    if (state == 2) {
        printf("Single line comment!\n");
    } else if (state == 5) {
        printf("Multi line comment!\n");
    } else {
        printf("Not a comment!\n");
    }
    state = 0;
}

%%

int main() {
    yylex();
    return 0;
}
