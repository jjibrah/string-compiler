#ifndef RUNTIME_H
#define RUNTIME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* String operations used by generated code */
char* concat_string(char *s1, char *s2);
char* reverse_string(char *s);
int   string_length(char *s);
char* substring(char *s, int start, int length);
int   is_palindrome(char *s);
int compare_string(char *s1, char *s2);

#endif
