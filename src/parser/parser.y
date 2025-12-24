%{
#include <stdio.h>
#include <stdlib.h>

static int hadSyntaxError = 0;


/* Flex functions */
int yylex(void);
extern char *yytext;

/* If your lexer provides yylineno, this will work; if not, we'll fallback gracefully */
extern int yylineno;

void yyerror(const char *s);
%}

/* Tell Bison the start symbol */
%start program

/* Tokens (must match tokens.h names) */
%token T_PROGRAM T_END
%token T_STRING T_INT T_BOOL
%token T_PRINT
%token T_TRUE T_FALSE

%token T_CONCAT T_SUBSTR T_LENGTH T_REVERSE T_PALINDROME T_COMPARE

%token T_ID T_STRING_LIT T_NUMBER

%token T_ASSIGN T_SEMICOLON T_LPAREN T_RPAREN T_COMMA

%%

program
    : T_PROGRAM stmt_list T_END
        {
          if (hadSyntaxError) printf("Parse completed with syntax errors ⚠️\n");
          else printf("Parse successful ✅\n");
        }
    ;


stmt_list
    : /* empty */
    | stmt_list stmt
    ;

stmt
    : declaration
    | assignment
    | print_stmt
    | error T_SEMICOLON   { yyerror("Recovered from syntax error"); yyerrok; }
    ;


declaration
    : type T_ID T_SEMICOLON
    ;

type
    : T_STRING
    | T_INT
    | T_BOOL
    ;

assignment
    : T_ID T_ASSIGN expr T_SEMICOLON
    ;

print_stmt
    : T_PRINT T_LPAREN expr T_RPAREN T_SEMICOLON
    ;

expr
    : T_STRING_LIT
    | T_NUMBER
    | bool_lit
    | T_ID
    | func_call
    ;

bool_lit
    : T_TRUE
    | T_FALSE
    ;

func_call
    : T_CONCAT     T_LPAREN expr T_COMMA expr T_RPAREN
    | T_SUBSTR     T_LPAREN expr T_COMMA expr T_COMMA expr T_RPAREN
    | T_LENGTH     T_LPAREN expr T_RPAREN
    | T_REVERSE    T_LPAREN expr T_RPAREN
    | T_PALINDROME T_LPAREN expr T_RPAREN
    | T_COMPARE    T_LPAREN expr T_COMMA expr T_RPAREN
    ;

%%

extern int yylineno;
extern char *yytext;

void yyerror(const char *s) {
    hadSyntaxError = 1;
    fprintf(stderr, "Syntax error at line %d near '%s'\n", yylineno, yytext);
}




