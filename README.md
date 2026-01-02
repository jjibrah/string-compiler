# STRON Compiler

This repository contains a small compiler for the STRON (STRing OperatioN) language. The compiler parses STRON source files (`.sp`), generates C code into `output/output.c`, then you can compile that generated C with the runtime to produce an executable.

## Quick setup / prerequisites
- gcc
- make
- bison
- flex

On Debian/Ubuntu:

```bash
sudo apt-get update
sudo apt-get install build-essential bison flex
```

## Build

From the project root:

```bash
make
```

This generates `build/compiler`.

## Run

- Run the sample pipeline:

```bash
make run
```

- Run a specific file:

```bash
make runfile FILE=test/valid/concat.sp
```

- Or run manually:

```bash
./build/compiler < test/valid/concat.sp
gcc -Isrc/runtime output/output.c src/runtime/string_lib.c -o output/program
./output/program
```

## Tests

Added several test cases in `test/valid/` and `test/invalid/`.
Use the provided test runner script to run all tests:

```bash
./scripts/run_tests.sh
```

- Valid tests should compile successfully and the generated program should run.
- Invalid tests should fail in the compilation step (the compiler prints `Compilation failed.`).

## Files added
- `test/valid/` (multiple non-empty .sp tests)
- `test/invalid/` (several invalid .sp tests)
- `scripts/run_tests.sh` — test runner

If you want, I can add CI integration or expand the test suite further.
