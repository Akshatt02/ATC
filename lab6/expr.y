%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int yylex();
void yyerror();
%}

%union
{
	char vname[10];
	int val;
}

%left '+' '-'
%left '*' '/'

%token <vname> NAME
%type <vname> expression

%%

input: line '\n' input   
     | '\n' input
     |
     ;

line : NAME '=' expression {
	printf("MOV %s,AX\n", $1);    
};

expression: NAME '+' NAME {
	printf("MOV AX, %s\n", $1);   
	printf("ADD AX, %s\n", $3);   
}
	| NAME '-' NAME {
	printf("MOV AX, %s\n", $1);
	printf("SUB AX, %s\n", $3);
}
	| NAME '*' NAME {
	printf("MOV AX, %s\n", $1);
	printf("MUL AX, %s\n", $3);
}
	| NAME '/' NAME {
	printf("MOV AX, %s\n", $1);
	printf("DIV AX, %s\n", $3);
}
	| NAME { 
		strcpy($$, $1);  
	}
	;

%%
void yyerror() {
    printf("Syntax Error\n");
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }
    freopen("input.txt", "r", stdin);

    printf("Reading input from file...\n\n");
    yyparse();  
    fclose(file);
    return 0;
}
