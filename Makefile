CC = gcc
LEX = flex
YACC = bison

CFLAGS = -Wall
CFLAGS += -Isrc/Lexer
all: compiler


compiler:
	$(YACC) -d src/parser/parser.y
	$(LEX) src/Lexer/lexer.l
	$(CC) $(CFLAGS) lex.yy.c parser.tab.c src/main.c src/runtime/string_lib.c -o compiler

run:
	./compiler tests/test1.sp
	gcc output.c src/runtime/string_lib.c -o output
	./output

clean:
	rm -f compiler lex.yy.c parser.tab.c parser.tab.h output output.c
