#ifndef AST_H
#define AST_H

/* Data types */
typedef enum {
    TYPE_STRING,
    TYPE_INT,
    TYPE_BOOL,
    TYPE_UNKNOWN
} DataType;

/* AST kinds used by parser + codegen */
typedef enum {
    AST_PROGRAM,
    AST_STMT_LIST,

    AST_VAR_DECL,
    AST_ASSIGN,
    AST_PRINT,

    AST_STRING_LITERAL,
    AST_INT_LITERAL,
    AST_BOOL_LITERAL,
    AST_IDENTIFIER,

    AST_FUNC_CALL
} ASTKind;

typedef struct ASTNode {
    ASTKind type;
    DataType dataType;

    char *name;        /* identifier name */
    char *funcName;    /* function name for calls */
    char *value;       /* string literal content */

    int intValue;
    int boolValue;

    struct ASTNode **children;
    int childCount;
} ASTNode;

ASTNode *createNode(ASTKind kind);
void addChild(ASTNode *parent, ASTNode *child);

ASTNode *makeDecl(DataType t, const char *id);
ASTNode *makeAssign(const char *id, ASTNode *expr);
ASTNode *makePrint(ASTNode *expr);

ASTNode *makeStringLit(const char *s);
ASTNode *makeIntLit(int v);
ASTNode *makeBoolLit(int v);
ASTNode *makeIdentifier(const char *id);

ASTNode *makeFuncCall(const char *fname, ASTNode **args, int argCount);

#endif
