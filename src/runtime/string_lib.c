#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_lib.h"

char* concat_string(const char* a, const char* b) {
    int len = strlen(a) + strlen(b) + 1;
    char* result = malloc(len);
    strcpy(result, a);
    strcat(result, b);
    return result;
}



int string_length(const char* s) {
    return strlen(s);
}


char* reverse_string(const char* s) {
    int len = strlen(s);
    char* rev = malloc(len + 1);
    for (int i = 0; i < len; i++)
        rev[i] = s[len - i - 1];
    rev[len] = '\0';
    return rev;
}


int is_palindrome(const char* s) {
    int i = 0, j = strlen(s) - 1;
    while (i < j) {
        if (s[i++] != s[j--])
            return 0;
    }
    return 1;
}


char* substring(const char* s, int start, int length) {
    char* sub = malloc(length + 1);
    strncpy(sub, s + start, length);
    sub[length] = '\0';
    return sub;
}

int compare_string(char *s1, char *s2) {
    if (!s1 && !s2) return 0;
    if (!s1) return -1;
    if (!s2) return 1;
    return strcmp(s1, s2);
}
