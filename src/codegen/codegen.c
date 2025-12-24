#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

/* ===============================
   GLOBAL OUTPUT FILE
   =============================== */
static FILE *out;

/* ===============================
   FORWARD DECLARATIONS
   =============================== */
void genStatement(ASTNode *node);
void genExpression(ASTNode *node);
void generateCode(ASTNode *root, const char *filename);

/* =====================================================
   CODE GENERATION ENTRY POINT
   ===================================================== */
void generateCode(ASTNode *root, const char *filename) {

    out = fopen(filename, "w");
    if (!out) {
        perror("Cannot open output file");
        exit(1);
    }

    /* Emit headers */
    fprintf(out, "#include <stdio.h>\n");
    fprintf(out, "#include \"runtime.h\"\n\n");
    fprintf(out, "int main() {\n");

    /* Generate all statements */
    for (int i = 0; i < root->childCount; i++) {
        genStatement(root->children[i]);
    }

    fprintf(out, "    return 0;\n");
    fprintf(out, "}\n");

    fclose(out);
}

/* =====================================================
   STATEMENT GENERATION
   ===================================================== */
void genStatement(ASTNode *node) {

    if (!node) return;

    switch (node->type) {

        case AST_VAR_DECL:
            if (node->dataType == TYPE_STRING)
                fprintf(out, "    char *%s;\n", node->name);
            else
                fprintf(out, "    int %s;\n", node->name);
            break;

        case AST_ASSIGN:
            fprintf(out, "    %s = ", node->name);
            genExpression(node->children[0]);
            fprintf(out, ";\n");
            break;

        case AST_PRINT:
            fprintf(out, "    printf(\"%%s\\n\", ");
            genExpression(node->children[0]);
            fprintf(out, ");\n");
            break;

        default:
            fprintf(stderr, "CodeGen Error: Unknown statement\n");
    }
}

/* =====================================================
   EXPRESSION GENERATION
   ===================================================== */
void genExpression(ASTNode *node) {

    if (!node) return;

    switch (node->type) {

        case AST_STRING_LITERAL:
            fprintf(out, "\"%s\"", node->value);
            break;

        case AST_INT_LITERAL:
            fprintf(out, "%d", node->intValue);
            break;

        case AST_IDENTIFIER:
            fprintf(out, "%s", node->name);
            break;

        case AST_FUNC_CALL:
            fprintf(out, "%s(", node->funcName);
            for (int i = 0; i < node->childCount; i++) {
                genExpression(node->children[i]);
                if (i < node->childCount - 1)
                    fprintf(out, ", ");
            }
            fprintf(out, ")");
            break;

        default:
            fprintf(stderr, "CodeGen Error: Unknown expression\n");
    }
}

/* =====================================================
   TEST DRIVER (MAIN)
   ===================================================== */
int main() {

    /* Create AST manually for:
       string s;
       s = reverse_string("madam");
       print(s);
    */

    ASTNode program;
    program.childCount = 3;
    program.children = malloc(sizeof(ASTNode*) * 3);

    /* 1️⃣ string s; */
    ASTNode decl = { AST_VAR_DECL, TYPE_STRING, "s", NULL, 0, NULL, NULL, 0 };

    /* 2️⃣ s = reverse_string("madam"); */
    ASTNode literal = { AST_STRING_LITERAL, TYPE_STRING, NULL, "madam", 0, NULL, NULL, 0 };
    ASTNode *args[] = { &literal };
    ASTNode call = { AST_FUNC_CALL, TYPE_STRING, NULL, NULL, 0, "reverse_string", args, 1 };
    ASTNode assign = { AST_ASSIGN, TYPE_STRING, "s", NULL, 0, NULL, &call, 1 };

    /* 3️⃣ print(s); */
    ASTNode id = { AST_IDENTIFIER, TYPE_STRING, "s", NULL, 0, NULL, NULL, 0 };
    ASTNode print = { AST_PRINT, TYPE_STRING, NULL, NULL, 0, NULL, &id, 1 };

    program.children[0] = &decl;
    program.children[1] = &assign;
    program.children[2] = &print;

    /* Generate C code */
    generateCode(&program, "output/generated.c");

    /* Free memory */
    free(program.children);

    return 0;
}
