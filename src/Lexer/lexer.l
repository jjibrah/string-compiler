%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
%}

%%
program        { return T_PROGRAM; }
end            { return T_END; }
string         { return T_STRING; }
int            { return T_INT; }
bool           { return T_BOOL; }
print          { return T_PRINT; }
true           { return T_TRUE; }
false          { return T_FALSE; }

concat         { return T_CONCAT; }
substr         { return T_SUBSTR; }
length         { return T_LENGTH; }
reverse        { return T_REVERSE; }
palindrome     { return T_PALINDROME; }
compare        { return T_COMPARE; }

\"[^\"]*\"     {
                  int len = yyleng;              /* includes quotes */
                  char *s = (char*)malloc(len-1); /* remove 2 quotes, keep null */
                  strncpy(s, yytext+1, len-2);
                  s[len-2] = '\0';
                  yylval.str = s;
                  return T_STRING_LIT;
               }


[0-9]+         {
                  yylval.ival = atoi(yytext);
                  return T_NUMBER;
               }

[a-zA-Z_][a-zA-Z0-9_]* {
                  yylval.str = strdup(yytext);
                  return T_ID;
               }

"="            { return T_ASSIGN; }
";"            { return T_SEMICOLON; }
"("            { return T_LPAREN; }
")"            { return T_RPAREN; }
","            { return T_COMMA; }

[ \t\r\n]+     ;
"//".*         ;

.              { printf("Lexical error: %s\n", yytext); }
%%

