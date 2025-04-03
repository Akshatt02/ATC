/* sym_tab.c - Source file implementing symbol table functions */
#include "sym_tab.h"

// Initialize a new empty symbol table
SymbolTable* init_table() {
    SymbolTable *table = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (table == NULL) {
        fprintf(stderr, "Memory allocation failed for symbol table\n");
        exit(1);
    }
    table->head = NULL;
    return table;
}

// Initialize a new symbol
Symbol* init_symbol(char *name, char *type, int line_no) {
    Symbol *sym = (Symbol*)malloc(sizeof(Symbol));
    if (sym == NULL) {
        fprintf(stderr, "Memory allocation failed for symbol\n");
        exit(1);
    }
    
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->size = size(type);
    sym->line_no = line_no;
    sym->value = NULL;
    sym->next = NULL;
    
    return sym;
}

// Insert a symbol into the table
void insert_symbol(SymbolTable *table, Symbol *sym) {
    if (check_sym_tab(table, sym->name) != NULL) {
        fprintf(stderr, "Error: Identifier '%s' already declared at line %d\n", 
                sym->name, sym->line_no);
        return;
    }
    
    if (table->head == NULL) {
        table->head = sym;
    } else {
        Symbol *current = table->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = sym;
    }
}

// Update variable values when initialized
void insert_val(SymbolTable *table, char *name, char *value) {
    Symbol *sym = check_sym_tab(table, name);
    if (sym == NULL) {
        fprintf(stderr, "Error: Undeclared identifier '%s'\n", name);
        return;
    }
    
    if (sym->value != NULL) {
        free(sym->value);
    }
    sym->value = strdup(value);
}

// Check if an identifier is declared
Symbol* check_sym_tab(SymbolTable *table, char *name) {
    Symbol *current = table->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Display the symbol table
void display_sym_tab(SymbolTable *table) {
    Symbol *current = table->head;
    
    printf("\n===== SYMBOL TABLE =====\n");
    printf("%-15s %-10s %-5s %-10s %-10s\n", 
           "Name", "Type", "Size", "Line", "Value");
    printf("----------------------------------------\n");
    
    while (current != NULL) {
        printf("%-15s %-10s %-5d %-10d %-10s\n", 
               current->name, 
               current->type, 
               current->size, 
               current->line_no, 
               current->value ? current->value : "NULL");
        current = current->next;
    }
    printf("========================\n\n");
}

// Return the size of the data type
int size(char *type) {
    if (strcmp(type, "int") == 0) return 4;
    if (strcmp(type, "float") == 0) return 4;
    if (strcmp(type, "char") == 0) return 1;
    if (strcmp(type, "double") == 0) return 8;
    return 0; // Unknown type
}