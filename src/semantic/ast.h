#ifndef AST_H
#define AST_H

/* Supported Data Types [cite: 165-168] */
typedef enum {
    TYPE_VOID,
    TYPE_INT,
    TYPE_STRING,
    TYPE_BOOL
} DataType;

/* Node Types based on Grammar [cite: 38-41] */
typedef enum {
    NODE_PROGRAM,
    NODE_VAR_DECL,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_LITERAL_STRING,
    NODE_LITERAL_INT,
    NODE_LITERAL_BOOL,
    NODE_VAR_REF,
    NODE_FUNC_CONCAT,
    NODE_FUNC_SUBSTR,
    NODE_FUNC_LENGTH,
    NODE_FUNC_REVERSE,
    NODE_FUNC_PALINDROME,
    NODE_FUNC_COMPARE
} NodeType;

/* Abstract Syntax Tree Node */
typedef struct ASTNode {
    NodeType type;
    DataType dataType;      // For type checking result
    char* stringValue;      // For identifiers or string literals
    int intValue;           // For int literals
    int lineNo;             // For error reporting

    struct ASTNode* left;   // Children (arguments, expressions)
    struct ASTNode* right;
    struct ASTNode* next;   // For lists of statements
} ASTNode;

#endif
