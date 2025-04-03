%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sym_tab.h"

extern int yylex();
extern FILE *yyin;
extern char *yytext;
void yyerror(const char *s);

int line_no = 1;
SymbolTable *symbol_table;

FILE *output_file;
%}

%union {
    char *str;
}

%token <str> ID NUM FLOAT_NUM CHAR_VAL STRING
%token <str> INT FLOAT CHAR DOUBLE
%token ASSIGN SEMICOLON COMMA

%type <str> type

%%

program: declarations
       ;

declarations: declarations declaration
            | declaration
            ;

declaration: type ID SEMICOLON 
           {
               Symbol *sym = init_symbol($2, $1, line_no);
               insert_symbol(symbol_table, sym);
           }
           | type ID ASSIGN NUM SEMICOLON 
           {
               Symbol *sym = init_symbol($2, $1, line_no);
               insert_symbol(symbol_table, sym);
               insert_val(symbol_table, $2, $4);
           }
           | type ID ASSIGN FLOAT_NUM SEMICOLON 
           {
               Symbol *sym = init_symbol($2, $1, line_no);
               insert_symbol(symbol_table, sym);
               insert_val(symbol_table, $2, $4);
           }
           | type ID ASSIGN CHAR_VAL SEMICOLON 
           {
               Symbol *sym = init_symbol($2, $1, line_no);
               insert_symbol(symbol_table, sym);
               insert_val(symbol_table, $2, $4);
           }
           | type ID ASSIGN STRING SEMICOLON 
           {
               Symbol *sym = init_symbol($2, $1, line_no);
               insert_symbol(symbol_table, sym);
               insert_val(symbol_table, $2, $4);
           }
           | type ID ASSIGN ID SEMICOLON 
           {
               Symbol *sym1 = check_sym_tab(symbol_table, $4);
               if (sym1 == NULL) {
                   yyerror("Undeclared identifier");
               } else {
                   Symbol *sym2 = init_symbol($2, $1, line_no);
                   insert_symbol(symbol_table, sym2);
                   insert_val(symbol_table, $2, sym1->value);
               }
           }
           ;

type: INT    { $$ = $1; }
    | FLOAT  { $$ = $1; }
    | CHAR   { $$ = $1; }
    | DOUBLE { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", line_no, s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Cannot open input file %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }
    
    output_file = fopen("output1.txt", "w");
    if (output_file == NULL) {
        fprintf(stderr, "Cannot open output file\n");
        return 1;
    }
    
    // Initialize symbol table
    symbol_table = init_table();
    
    // Parse the input
    yyparse();
    
    // Display the symbol table
    display_sym_tab(symbol_table);
    
    // Close files
    if (yyin != stdin) fclose(yyin);
    fclose(output_file);
    
    return 0;
}