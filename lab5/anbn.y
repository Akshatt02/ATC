%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token A B END INVALID

%%

Input : S END { printf("Valid string\n"); return 0; }
      ;

S : A S B
  | A B
  ;

%%

int main() {
    printf("Enter a string: ");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Invalid string\n");
    exit(1);
}
