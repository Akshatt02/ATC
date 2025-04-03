%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   // Include string.h for strdup

int yylineno = 1;  // Define yylineno
%}

%%

"int"   { return INT; }
"float" { return FLOAT; }
"char"  { return CHAR; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return ID; }
[0-9]+  { yylval.str = strdup(yytext); return NUMBER; }
"="     { return ASSIGN; }
";"     { return SEMICOLON; }
\n      { yylineno++; }
[ \t]   { /* Ignore spaces and tabs */ }
.       { printf("Unknown character: %s\n", yytext); }
%%

int yywrap() { return 1; }
