#include "parser/parser.tab.h"
#include "codegen/codegen.h"
#include <stdio.h>

extern ASTNode *astRoot;

int main(int argc, char **argv) {
    if (yyparse() == 0 && astRoot != NULL) {
        generateCode(astRoot, "output/output.c");
        printf("Compilation successful. C code generated.\n");
    } else {
        printf("Compilation failed.\n");
    }
    return 0;
}

