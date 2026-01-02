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

### Troubleshooting ⚠️

If running `./scripts/run_tests.sh` prints `Permission denied`, the script is not executable. Quick fixes:

- Run without changing permissions:

```bash
bash scripts/run_tests.sh
```

- Make it executable and run:

```bash
chmod +x scripts/run_tests.sh
./scripts/run_tests.sh
```

- To preserve the executable bit in Git for others:

```bash
# mark executable in the index and commit
git update-index --chmod=+x scripts/run_tests.sh
git commit -m "Make run_tests.sh executable"
```

Note: The script already has a proper shebang (`#!/usr/bin/env bash`), so making it executable is the recommended fix.

## Files added
- `test/valid/` (multiple non-empty .sp tests)
- `test/invalid/` (several invalid .sp tests)
- `scripts/run_tests.sh` — test runner

If you want, I can add CI integration or expand the test suite further.
