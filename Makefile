CC := gcc
YACC := bison
LEX := flex

BUILD_DIR := build
OUT_DIR := output

CFLAGS := -Wall -Wextra -g -I$(BUILD_DIR) -Isrc -Isrc/Lexer -Isrc/parser -Isrc/semantic -Isrc/codegen -Isrc/runtime
LDFLAGS := -lfl

PARSER_C := $(BUILD_DIR)/parser.tab.c
PARSER_H := $(BUILD_DIR)/parser.tab.h
LEXER_C  := $(BUILD_DIR)/lex.yy.c

COMPILER := $(BUILD_DIR)/compiler

# Sources for the compiler executable (semantic disabled)
COMPILER_SRCS := \
	src/main.c \
	src/codegen/codegen.c \
	src/semantic/ast.c \
	src/runtime/string_lib.c

all: $(COMPILER)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Generate parser (bison)
$(PARSER_C) $(PARSER_H): src/parser/parser.y | $(BUILD_DIR)
	$(YACC) -d -o $(PARSER_C) src/parser/parser.y

# Generate lexer (flex) - depends on parser header for tokens/union
$(LEXER_C): src/Lexer/lexer.l $(PARSER_H) | $(BUILD_DIR)
	$(LEX) -o $(LEXER_C) src/Lexer/lexer.l

# Build compiler
$(COMPILER): $(LEXER_C) $(PARSER_C) $(COMPILER_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(COMPILER) $(LEXER_C) $(PARSER_C) $(COMPILER_SRCS) $(LDFLAGS)

# Run full pipeline:
# 1) parse + generate output/output.c
# 2) compile generated C with runtime header+lib
# 3) run output program
run: $(COMPILER) | $(OUT_DIR)
	$(COMPILER) < test/test1.sp
	$(CC) -Isrc/runtime $(OUT_DIR)/output.c src/runtime/string_lib.c -o $(OUT_DIR)/program
	./$(OUT_DIR)/program

# Optional: run a different input file
# Usage: make runfile FILE=test/test2.sp
runfile: $(COMPILER) | $(OUT_DIR)
	$(COMPILER) < $(FILE)
	$(CC) -Isrc/runtime $(OUT_DIR)/output.c src/runtime/string_lib.c -o $(OUT_DIR)/program
	./$(OUT_DIR)/program

clean:
	rm -rf $(BUILD_DIR) $(OUT_DIR)/output.c $(OUT_DIR)/program

.PHONY: all run runfile clean

