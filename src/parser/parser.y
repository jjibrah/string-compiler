%{
#include <stdio.h>
#include <stdlib.h>


#include "../semantic/ast.h"

extern int yylex(void);
extern int yylineno;
extern char *yytext;

ASTNode *astRoot = NULL;
static int hadSyntaxError = 0;

void yyerror(const char *s);
%}

%code requires {
    #include "../semantic/ast.h"
}


/* Bison value types */
%union {
    int ival;
    char *str;
    ASTNode *node;
    DataType dtype;
}

/* Tokens (from your tokens.h / lexer) */
%token T_PROGRAM T_END
%token T_STRING T_INT T_BOOL
%token T_PRINT
%token T_TRUE T_FALSE

%token T_CONCAT T_SUBSTR T_LENGTH T_REVERSE T_PALINDROME T_COMPARE

%token T_ASSIGN T_SEMICOLON T_LPAREN T_RPAREN T_COMMA

%token <str>  T_ID T_STRING_LIT
%token <ival> T_NUMBER

/* Nonterminal types */
%type <node> program stmt_list stmt declaration assignment print_stmt expr func_call bool_lit
%type <dtype> type

%%

program
    : T_PROGRAM stmt_list T_END
      {
          astRoot = createNode(AST_PROGRAM);
          /* move children from list into program */
          for (int i = 0; i < $2->childCount; i++) addChild(astRoot, $2->children[i]);
          $$ = astRoot;
      }
    ;

stmt_list
    : /* empty */
      {
          $$ = createNode(AST_STMT_LIST);
      }
    | stmt_list stmt
      {
          $$ = $1;
          addChild($$, $2);
      }
    ;

stmt
    : declaration { $$ = $1; }
    | assignment  { $$ = $1; }
    | print_stmt  { $$ = $1; }
    | error T_SEMICOLON { yyerror("Recovered from syntax error"); yyerrok; $$ = createNode(AST_STMT_LIST); }
    ;

declaration
    : type T_ID T_SEMICOLON
      {
          $$ = makeDecl($1, $2);
      }
    ;

type
    : T_STRING { $$ = TYPE_STRING; }
    | T_INT    { $$ = TYPE_INT; }
    | T_BOOL   { $$ = TYPE_BOOL; }
    ;

assignment
    : T_ID T_ASSIGN expr T_SEMICOLON
      {
          $$ = makeAssign($1, $3);
      }
    ;

print_stmt
    : T_PRINT T_LPAREN expr T_RPAREN T_SEMICOLON
      {
          $$ = makePrint($3);
      }
    ;

expr
    : T_STRING_LIT { $$ = makeStringLit($1); }
    | T_NUMBER     { $$ = makeIntLit($1); }
    | bool_lit     { $$ = $1; }
    | T_ID         { $$ = makeIdentifier($1); }
    | func_call    { $$ = $1; }
    ;

bool_lit
    : T_TRUE  { $$ = makeBoolLit(1); }
    | T_FALSE { $$ = makeBoolLit(0); }
    ;

func_call
    : T_CONCAT T_LPAREN expr T_COMMA expr T_RPAREN
      {
          ASTNode *args[2] = { $3, $5 };
          $$ = makeFuncCall("concat", args, 2);
      }
    | T_SUBSTR T_LPAREN expr T_COMMA expr T_COMMA expr T_RPAREN
      {
          ASTNode *args[3] = { $3, $5, $7 };
          $$ = makeFuncCall("substr", args, 3);
      }
    | T_LENGTH T_LPAREN expr T_RPAREN
      {
          ASTNode *args[1] = { $3 };
          $$ = makeFuncCall("length", args, 1);
      }
    | T_REVERSE T_LPAREN expr T_RPAREN
      {
          ASTNode *args[1] = { $3 };
          $$ = makeFuncCall("reverse", args, 1);
      }
    | T_PALINDROME T_LPAREN expr T_RPAREN
      {
          ASTNode *args[1] = { $3 };
          $$ = makeFuncCall("palindrome", args, 1);
      }
    | T_COMPARE T_LPAREN expr T_COMMA expr T_RPAREN
      {
          ASTNode *args[2] = { $3, $5 };
          $$ = makeFuncCall("compare", args, 2);
      }
    ;

%%

void yyerror(const char *s) {
    hadSyntaxError = 1;
    fprintf(stderr, "Syntax error at line %d near '%s'\n", yylineno, yytext);
}
