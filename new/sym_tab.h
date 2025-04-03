/* sym_tab.h - Header file defining the symbol structure */
#ifndef SYM_TAB_H
#define SYM_TAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbol structure definition
typedef struct symbol {
    char *name;         // Identifier name
    char *type;         // Data type (int, float, char, etc.)
    int size;           // Size of the data type
    int line_no;        // Line number where the identifier is declared
    char *value;        // Value of the identifier (if initialized)
    struct symbol *next; // Pointer to the next symbol in the linked list
} Symbol;

// Symbol table structure
typedef struct {
    Symbol *head;  // Pointer to the first symbol in the linked list
} SymbolTable;

// Function prototypes
SymbolTable* init_table();
Symbol* init_symbol(char *name, char *type, int line_no);
void insert_symbol(SymbolTable *table, Symbol *sym);
void insert_val(SymbolTable *table, char *name, char *value);
Symbol* check_sym_tab(SymbolTable *table, char *name);
void display_sym_tab(SymbolTable *table);
int size(char *type);

#endif /* SYM_TAB_H */