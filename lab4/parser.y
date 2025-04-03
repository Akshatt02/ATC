%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex(void);
    void yyerror(const char *s);
%}

%token NUMBER EOL

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%%

input:
    /*empty*/
    | input line
    ;

line:
    expr EOL {printf("Result: %d\n", $1); }
    | EOL /*Handle empty lines*/
    ;

expr:
    expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr {
        if ($3 == 0) {
            fprintf(stderr, "Division by zero error\n");
            exit(EXIT_FAILURE);
        } else {
            $$ = $1/$3;
        }
    }
    | '-' expr %prec UMINUS { $$ = -2; }
    | '(' expr ')' { $$ = $2; }
    | NUMBER        { $$ = $1; }
    ;

%%

int main(void) {
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}