#include "runtime.h"

/* ========================
   Concatenate two strings
   ======================== */
char* concat_string(char *s1, char *s2) {
    if (!s1) s1 = "";
    if (!s2) s2 = "";
    size_t len = strlen(s1) + strlen(s2) + 1;
    char *result = malloc(len);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

/* ========================
   Reverse a string
   ======================== */
char* reverse_string(char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char *rev = malloc(len + 1);
    for (size_t i = 0; i < len; i++) {
        rev[i] = s[len - 1 - i];
    }
    rev[len] = '\0';
    return rev;
}

/* ========================
   String length
   ======================== */
int string_length(char *s) {
    if (!s) return 0;
    return strlen(s);
}

/* ========================
   Substring
   ======================== */
char* substring(char *s, int start, int length) {
    if (!s) return NULL;
    int s_len = strlen(s);
    if (start < 0 || start >= s_len || length <= 0) return NULL;
    if (start + length > s_len) length = s_len - start;

    char *sub = malloc(length + 1);
    strncpy(sub, s + start, length);
    sub[length] = '\0';
    return sub;
}

/* ========================
   Check if string is palindrome
   ======================== */
int is_palindrome(char *s) {
    if (!s) return 0;
    size_t len = strlen(s);
    for (size_t i = 0; i < len / 2; i++) {
        if (s[i] != s[len - 1 - i])
            return 0;
    }
    return 1;
}
