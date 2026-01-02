#ifndef CODEGEN_H
#define CODEGEN_H

#include "../semantic/ast.h"

/*
  generateCode()
  --------------
  Generates a C source file from the AST.
  filename: path of the output .c file (e.g., "output/output.c")
*/
void generateCode(ASTNode *root, const char *filename);

#endif

