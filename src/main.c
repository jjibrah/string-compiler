#include <stdio.h>

extern int yyparse();

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <source.sp>\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (!input) {
        perror("File error");
        return 1;
    }

    extern FILE* yyin;
    yyin = input;

    if (yyparse() == 0) {
        printf("Compilation successful.\n");
    } else {
        printf("Compilation failed.\n");
    }

    fclose(input);
    return 0;
}
