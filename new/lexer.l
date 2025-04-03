%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
#include "sym_tab.h"

extern int line_no;
%}

%%
"int"               { yylval.str = strdup(yytext); return INT; }
"float"             { yylval.str = strdup(yytext); return FLOAT; }
"char"              { yylval.str = strdup(yytext); return CHAR; }
"double"            { yylval.str = strdup(yytext); return DOUBLE; }
"="                 { return ASSIGN; }
";"                 { return SEMICOLON; }
","                 { return COMMA; }
[a-zA-Z][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return ID; }
[0-9]+              { yylval.str = strdup(yytext); return NUM; }
[0-9]+\.[0-9]+      { yylval.str = strdup(yytext); return FLOAT_NUM; }
\'[^\']*\'          { yylval.str = strdup(yytext); return CHAR_VAL; }
\"[^\"]*\"          { yylval.str = strdup(yytext); return STRING; }
[ \t]               { /* Ignore whitespace */ }
\n                  { line_no++; }
.                   { /* Ignore other characters */ }
%%

int yywrap() {
    return 1;
}