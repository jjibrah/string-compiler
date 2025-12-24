#ifndef TOKENS_H
#define TOKENS_H

/* Keywords */
#define T_PROGRAM     256
#define T_END         257
#define T_STRING      258
#define T_INT         259
#define T_BOOL        260
#define T_PRINT       261
#define T_TRUE        262
#define T_FALSE       263

/* String operations */
#define T_CONCAT      264
#define T_SUBSTR      265
#define T_LENGTH      266
#define T_REVERSE     267
#define T_PALINDROME  268
#define T_COMPARE     269

/* Identifiers & literals */
#define T_ID          270
#define T_STRING_LIT  271
#define T_NUMBER      272

/* Operators & symbols */
#define T_ASSIGN      273   /* = */
#define T_SEMICOLON   274   /* ; */
#define T_LPAREN      275   /* ( */
#define T_RPAREN      276   /* ) */
#define T_COMMA       277   /* , */

#endif
