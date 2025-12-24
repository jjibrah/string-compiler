#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"
#include "symbol_table.h"

/* Helper to report errors clearly [cite: 259] */
void sem_error(int line, const char* msg) {
    fprintf(stderr, "Semantic Error at line %d: %s\n", line, msg);
    // In a real compiler, we might exit(1) or increment an error counter
}

/* Recursive function to check expressions and return their type */
DataType check_expr(ASTNode* node) {
    if (!node) return TYPE_VOID;

    switch (node->type) {
        case NODE_LITERAL_INT:
            return TYPE_INT;
        case NODE_LITERAL_STRING:
            return TYPE_STRING;
        case NODE_LITERAL_BOOL:
            return TYPE_BOOL;

        case NODE_VAR_REF: {
            // Check if variable is declared [cite: 52]
            Symbol* sym = lookup_symbol(node->stringValue);
            if (!sym) {
                char buf[100];
                snprintf(buf, 100, "Undeclared variable '%s'", node->stringValue);
                sem_error(node->lineNo, buf);
                return TYPE_VOID; // Error recovery type
            }
            return sym->type;
        }

        /* String Operation: Concat [cite: 170, 255] */
        case NODE_FUNC_CONCAT: {
            DataType t1 = check_expr(node->left);
            DataType t2 = check_expr(node->right);
            if (t1 != TYPE_STRING || t2 != TYPE_STRING) {
                sem_error(node->lineNo, "Type Mismatch: 'concat' requires two strings.");
            }
            return TYPE_STRING;
        }

        /* String Operation: Substr [cite: 171] */
        case NODE_FUNC_SUBSTR: {
            // substr(s, start, len) - AST assumes structure: left=s, right=start (which has sibling len)
            // Implementation depends on exact AST shape, assuming 3 args
            DataType tStr = check_expr(node->left);
            // Assuming simplified AST for demo: right child is 'start', right->next is 'length'
            DataType tStart = check_expr(node->right);
            DataType tLen = check_expr(node->right->next);

            if (tStr != TYPE_STRING) sem_error(node->lineNo, "Arg 1 of 'substr' must be string.");
            if (tStart != TYPE_INT) sem_error(node->lineNo, "Arg 2 of 'substr' must be int.");
            if (tLen != TYPE_INT) sem_error(node->lineNo, "Arg 3 of 'substr' must be int.");

            return TYPE_STRING;
        }

        /* String Operation: Length [cite: 172, 254] */
        case NODE_FUNC_LENGTH: {
            DataType t1 = check_expr(node->left);
            if (t1 != TYPE_STRING) {
                sem_error(node->lineNo, "Type Mismatch: 'length' requires a string.");
            }
            return TYPE_INT; // Validates requirement that length returns int
        }

        /* String Operation: Reverse [cite: 173] */
        case NODE_FUNC_REVERSE: {
            if (check_expr(node->left) != TYPE_STRING) {
                sem_error(node->lineNo, "'reverse' requires a string.");
            }
            return TYPE_STRING;
        }

        /* String Operation: Palindrome [cite: 174] */
        case NODE_FUNC_PALINDROME: {
            if (check_expr(node->left) != TYPE_STRING) {
                sem_error(node->lineNo, "'palindrome' requires a string.");
            }
            return TYPE_BOOL;
        }

        /* Extra Operation: Compare [cite: 175] */
        case NODE_FUNC_COMPARE: {
            DataType t1 = check_expr(node->left);
            DataType t2 = check_expr(node->right);
            if (t1 != TYPE_STRING || t2 != TYPE_STRING) {
                sem_error(node->lineNo, "'compare' requires two strings.");
            }
            return TYPE_BOOL; // Returns true/false for equality
        }

        default:
            return TYPE_VOID;
    }
}

/* Recursive traversal of statements */
void check_stmt(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_VAR_DECL:
            // Check Redeclarations [cite: 251]
            if (add_symbol(node->stringValue, node->dataType, node->lineNo) == -1) {
                char buf[100];
                snprintf(buf, 100, "Redeclaration of variable '%s'", node->stringValue);
                sem_error(node->lineNo, buf);
            }
            break;

        case NODE_ASSIGN: {
            // Check LHS existence
            Symbol* sym = lookup_symbol(node->stringValue);
            if (!sym) {
                char buf[100];
                snprintf(buf, 100, "Assignment to undeclared variable '%s'", node->stringValue);
                sem_error(node->lineNo, buf);
                break;
            }

            // Check Type Compatibility [cite: 51]
            DataType rhsType = check_expr(node->left); // Assuming left child is the expression
            if (sym->type != rhsType && rhsType != TYPE_VOID) {
                sem_error(node->lineNo, "Type Mismatch in assignment.");
            }
            break;
        }

        case NODE_PRINT:
            check_expr(node->left);
            break;

        default:
            break;
    }

    // Process next statement in the list
    check_stmt(node->next);
}

void semantic_analysis(ASTNode* root) {
    init_symbol_table();

    // The root is usually NODE_PROGRAM which points to a list of statements
    if (root && root->type == NODE_PROGRAM) {
        check_stmt(root->left); // Assuming left holds the statement list
    }

    // Symbol table can be kept for CodeGen or freed if purely single-pass
    // free_symbol_table();
}
