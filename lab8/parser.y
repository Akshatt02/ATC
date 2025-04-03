%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sym_tab.h"

extern int yylineno;
int yylex();
void yyerror(const char* msg);
%}

/* Define YYSTYPE to store string values */
%union {
    char* str;
}

/* Token Declarations */
%token <str> INT FLOAT CHAR ID NUMBER
%token ASSIGN SEMICOLON

%type <str> type

%%

stmt_list: stmt stmt_list
         | /* empty */
         ;

stmt:
      type ID SEMICOLON { 
          /* Determine correct size based on data type */
          int size = (!strcmp($1, "int")) ? 4 : (!strcmp($1, "float")) ? 4 : 1;
          insertSymbol($2, $1, size, 0, yylineno, ""); 
      }
    | type ID ASSIGN NUMBER SEMICOLON { 
          int size = (!strcmp($1, "int")) ? 4 : (!strcmp($1, "float")) ? 4 : 1;
          insertSymbol($2, $1, size, 0, yylineno, $4); 
      }
    ;

type: INT   { $$ = strdup("int"); }
    | FLOAT { $$ = strdup("float"); }
    | CHAR  { $$ = strdup("char"); }
    ;

%%

void yyerror(const char* msg) {
    printf("Error: %s at line %d\n", msg, yylineno);
}

int main() {
    yyparse();
    displaySymbolTable();
    return 0;
}
