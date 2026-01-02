#include "ast.h"
#include <stdlib.h>
#include <string.h>

static char *dupstr(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    memcpy(p, s, n + 1);
    return p;
}

ASTNode *createNode(ASTKind kind) {
    ASTNode *n = (ASTNode*)calloc(1, sizeof(ASTNode));
    n->type = kind;
    n->dataType = TYPE_UNKNOWN;
    n->children = NULL;
    n->childCount = 0;
    return n;
}

void addChild(ASTNode *parent, ASTNode *child) {
    if (!parent || !child) return;
    parent->children = (ASTNode**)realloc(parent->children,
        sizeof(ASTNode*) * (parent->childCount + 1));
    parent->children[parent->childCount++] = child;
}

ASTNode *makeDecl(DataType t, const char *id) {
    ASTNode *n = createNode(AST_VAR_DECL);
    n->dataType = t;
    n->name = dupstr(id);
    return n;
}

ASTNode *makeAssign(const char *id, ASTNode *expr) {
    ASTNode *n = createNode(AST_ASSIGN);
    n->name = dupstr(id);
    addChild(n, expr);
    return n;
}

ASTNode *makePrint(ASTNode *expr) {
    ASTNode *n = createNode(AST_PRINT);
    addChild(n, expr);
    return n;
}

ASTNode *makeStringLit(const char *s) {
    ASTNode *n = createNode(AST_STRING_LITERAL);
    n->value = dupstr(s);
    return n;
}

ASTNode *makeIntLit(int v) {
    ASTNode *n = createNode(AST_INT_LITERAL);
    n->intValue = v;
    return n;
}

ASTNode *makeBoolLit(int v) {
    ASTNode *n = createNode(AST_BOOL_LITERAL);
    n->boolValue = v ? 1 : 0;
    return n;
}

ASTNode *makeIdentifier(const char *id) {
    ASTNode *n = createNode(AST_IDENTIFIER);
    n->name = dupstr(id);
    return n;
}

ASTNode *makeFuncCall(const char *fname, ASTNode **args, int argCount) {
    ASTNode *n = createNode(AST_FUNC_CALL);
    n->funcName = dupstr(fname);
    for (int i = 0; i < argCount; i++) addChild(n, args[i]);
    (void)args;
    return n;
}
