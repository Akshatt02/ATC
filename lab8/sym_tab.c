#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sym_tab.h"

Symbol* head = NULL;

void insertSymbol(char* name, char* type, int size, int scope, int line_no, char* value) {
    if (searchSymbol(name) != NULL) {
        printf("Error: Identifier %s already declared!\n", name);
        return;
    }

    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));
    strcpy(newSymbol->name, name);
    strcpy(newSymbol->type, type);
    newSymbol->size = size;
    newSymbol->scope = scope;
    newSymbol->line_no = line_no;
    if (value != NULL)
        strcpy(newSymbol->value, value);
    else
        newSymbol->value[0] = '\0';
    newSymbol->next = head;
    head = newSymbol;
}

// Search for a symbol
Symbol* searchSymbol(char* name) {
    Symbol* current = head;
    while (current) {
        if (strcmp(current->name, name) == 0) return current;
        current = current->next;
    }
    return NULL;
}

void displaySymbolTable() {
    Symbol* temp = head;
    printf("\nSymbol Table:\n");
    printf("----------------------------------------------------------\n");
    printf("Name       Type    Size    Scope    Line No    Value      \n");
    printf("----------------------------------------------------------\n");
    while (temp) {
        printf("%-10s %-7s %-7d %-7d %-7d %-10s\n", temp->name, temp->type, temp->size, temp->scope, temp->line_no, temp->value);
        temp = temp->next;
    }
    printf("----------------------------------------------------------\n");
}

// Delete a symbol
void deleteSymbol(char* name) {
    Symbol* temp = head, *prev = NULL;

    while (temp && strcmp(temp->name, name) == 0) {
        head = temp->next;
        free(temp);
        return;
    }

    while (temp && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) return;
    
    prev->next = temp->next;
    free(temp);
}
