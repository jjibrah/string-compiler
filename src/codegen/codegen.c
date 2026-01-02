#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../semantic/ast.h"

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
   Helper: map function name to runtime function
   ===================================================== */
static const char* mapRuntimeFn(const char *fn) {
    if (!fn) return fn;

    if (strcmp(fn, "concat") == 0)      return "concat_string";
    if (strcmp(fn, "reverse") == 0)     return "reverse_string";
    if (strcmp(fn, "length") == 0)      return "string_length";
    if (strcmp(fn, "substr") == 0)      return "substring";
    if (strcmp(fn, "palindrome") == 0)  return "is_palindrome";
    if (strcmp(fn, "compare") == 0)     return "compare_string"; /* if implemented */

    /* default: emit as-is */
    return fn;
}

/* =====================================================
   Helper: decide print format based on expression type
   ===================================================== */
static const char* printFormatForExpr(ASTNode *expr) {
    if (!expr) return "%s";

    /* integers */
    if (expr->type == AST_INT_LITERAL) return "%d";

    /* function calls: some return int */
    if (expr->type == AST_FUNC_CALL && expr->funcName) {
        if (strcmp(expr->funcName, "length") == 0) return "%d";
        if (strcmp(expr->funcName, "palindrome") == 0) return "%d"; /* 0/1 */
        if (strcmp(expr->funcName, "compare") == 0) return "%d";    /* <0,0,>0 */
    }

    /* default strings / identifiers assumed string */
    return "%s";
}

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

        case AST_PRINT: {
            ASTNode *expr = node->children[0];
            const char *fmt = printFormatForExpr(expr);
            fprintf(out, "    printf(\"%s\\n\", ", fmt);
            genExpression(expr);
            fprintf(out, ");\n");
            break;
        }

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

        case AST_FUNC_CALL: {
            const char *runtimeFn = mapRuntimeFn(node->funcName);
            fprintf(out, "%s(", runtimeFn);

            for (int i = 0; i < node->childCount; i++) {
                genExpression(node->children[i]);
                if (i < node->childCount - 1) fprintf(out, ", ");
            }

            fprintf(out, ")");
            break;
        }

        default:
            fprintf(stderr, "CodeGen Error: Unknown expression\n");
    }
}

