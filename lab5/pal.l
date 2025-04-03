%{
#include "pal.tab.h"
%}

%%

a   { return A; }
b   { return B; }
c   {return C; }
\n  { return END; }
.   { return INVALID; }

%%

int yywrap() { return 1; }
