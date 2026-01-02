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

Run the full test suite (build the compiler first if needed):

```bash
# build compiler first (if not already built)
make

# preferred: ensure the test runner is executable then run
chmod +x scripts/run_tests.sh
./scripts/run_tests.sh

# or run without changing permissions:
bash scripts/run_tests.sh
```

- Note: If you see `Permission denied` when running `./scripts/run_tests.sh`, either run it with `bash scripts/run_tests.sh` or add execute permission with `chmod +x scripts/run_tests.sh`.
- To persist the executable bit in Git so others receive it too:

```bash
git update-index --chmod=+x scripts/run_tests.sh
git commit -m "Make run_tests.sh executable"
```

- Valid tests should compile successfully and the generated program should run.
- Invalid tests should fail at compilation (the compiler prints errors such as `Syntax error` or `Semantic Error`).

## Files added
- `test/valid/` (multiple non-empty .sp tests)
- `test/invalid/` (several invalid .sp tests)
- `scripts/run_tests.sh` — test runner

If you want, I can add CI integration or expand the test suite further.
