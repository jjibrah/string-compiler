Member 6 — Runtime, Build & Testing (45s Presentation Script)

Hello — I'm Member Six, and I worked on runtime support, build integration, and testing for the STRON compiler.

I implemented the runtime string functions: concat_string, reverse_string, and string_length, and added them to the runtime library so generated C can call them directly.

I fixed Makefile issues and integrated the runtime with the code generation step so the pipeline produces a complete C program.

I ran the test suite (including `test/test1.sp`), debugged segmentation faults, and verified correct outputs end-to-end.

Files I worked on:
- `src/runtime/string_lib.c` — implements runtime string functions (e.g., `concat_string`, `reverse_string`, `substring`, `string_length`, `is_palindrome`, `compare_string`).
- `src/runtime/runtime.h` — runtime function declarations and includes used by generated C.
- `Makefile` — fixed build rules to generate parser/lexer, build `build/compiler`, and integrate runtime with generated C.
- `test/*` — added valid and invalid `.sp` tests (including `test/test1.sp`) to exercise the compiler pipeline.

Run steps (commands and brief description):
- `sudo apt-get install build-essential bison flex`  # install prerequisites
- `make`                                              # build `build/compiler`
- `make run`                                          # run sample pipeline (compile `test/test1.sp`, compile generated C, run program)
- `make runfile FILE=test/valid/concat.sp`            # compile & run a specific test file
- `./scripts/run_tests.sh`                            # run all valid/invalid tests and report results
- (optional) `bison -d -o build/parser.tab.c src/parser/parser.y`  # regenerate parser
- (optional) `flex -o build/lex.yy.c src/Lexer/lexer.l`            # regenerate lexer

In short: I integrated runtime support, resolved build problems, and validated the full compiler pipeline — ready for demonstration. Thank you.