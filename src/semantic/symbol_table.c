#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

static Symbol* head = NULL;

void init_symbol_table() {
    head = NULL;
}

/* Adds a symbol to the table. Returns -1 if it already exists (Redeclaration check) [cite: 251] */
int add_symbol(char* name, DataType type, int lineNo) {
    if (lookup_symbol(name) != NULL) {
        return -1; // Error: Redeclaration
    }

    Symbol* newSym = (Symbol*)malloc(sizeof(Symbol));
    newSym->name = strdup(name);
    newSym->type = type;
    newSym->declaredLine = lineNo;
    newSym->next = head;
    head = newSym;
    return 0;
}

/* Finds a symbol by name. Used to check Undeclared Variables [cite: 250] */
Symbol* lookup_symbol(char* name) {
    Symbol* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void free_symbol_table() {
    Symbol* current = head;
    while (current != NULL) {
        Symbol* temp = current;
        current = current->next;
        free(temp->name);
        free(temp);
    }
}
