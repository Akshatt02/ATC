%{
#include "expr.tab.h"
#include <string.h>
%}

%%
[a-zA-Z][a-zA-Z0-9]*   { 
    yylval.vname[0] = '\0'; 
    strcpy(yylval.vname, yytext); 
    return NAME; 
}

[ \t]+                 { /* Ignore Whitespace */ }
"="                    { return '='; }
"+"                    { return '+'; }
"-"                    { return '-'; }
"*"                    { return '*'; }
"/"                    { return '/'; }
"\n"                   { return '\n'; }
.                      { return yytext[0]; }
%%

int yywrap() {
    return 1; // Indicates end of input
}
