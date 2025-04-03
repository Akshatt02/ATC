%{
#include "parser.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t]+      ;
"+"         { return '+'; }
"-"         {return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"("         { return '('; }
")"         { return ')'; }
\n          { return EOL; }
.           { /* Ignore any other character */ }

%%

int yywrap(void) {
return 1;
}
