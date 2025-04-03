%{
#include <stdio.h>

int yywrap(void) {
    return 1;
}
%}

%%
"#include"               { printf("Preprocessor Directive: %s\n", yytext); }
"<"[a-zA-Z0-9]+".h">     { printf("Header File: %s\n", yytext); }
"int"|"return"|"char"    { printf("Keyword: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*   { printf("Identifier: %s\n", yytext); }
[0-9]+                   { printf("Integer: %s\n", yytext); }
"\""([^\"\n])*"\""       { printf("String Literal: %s\n", yytext); }
[ \t\n]+                 { /* Ignore whitespace */ }
.                        { printf("Other: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}
