%{
#include "anb2n.tab.h"
%}

%%

a   { return A; }
b   { return B; }
\n  { return END; }
.   { return INVALID; }

%%

int yywrap() { return 1; }
