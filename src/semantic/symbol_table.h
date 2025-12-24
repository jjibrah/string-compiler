#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "../parser/ast.h"

/* Structure to hold symbol information [cite: 246] */
typedef struct Symbol {
    char* name;
    DataType type;
    int declaredLine;
    struct Symbol* next;
} Symbol;

/* Operations */
void init_symbol_table();
int add_symbol(char* name, DataType type, int lineNo); // Returns 0 on success, -1 on redeclaration
Symbol* lookup_symbol(char* name); // Returns NULL if not found [cite: 250]
void free_symbol_table();

#endif
