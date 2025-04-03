#ifndef SYM_TAB_H
#define SYM_TAB_H

typedef struct Symbol {
    char name[50];
    char type[10];
    int size;
    int scope;
    int line_no;
    char value[50];
    struct Symbol* next;
} Symbol;

void insertSymbol(char* name, char* type, int size, int scope, int line_no, char* value);
Symbol* searchSymbol(char* name);
void displaySymbolTable();
void deleteSymbol(char* name);

#endif
 