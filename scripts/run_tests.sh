#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
COMPILER="$ROOT_DIR/build/compiler"
OUT_DIR="$ROOT_DIR/output"

mkdir -p "$OUT_DIR"

run_valid() {
  local file="$1"
  echo "Running valid test: $file"
  if [ ! -s "$file" ]; then
    echo "  SKIP (empty)"
    return
  fi
  # capture both stdout and stderr into /tmp/compiler_out
  "$COMPILER" < "$file" 2>&1 | tee /tmp/compiler_out > /dev/null
  if grep -qE "Syntax error|Semantic Error|CodeGen Error" /tmp/compiler_out; then
    echo "  FAIL (compiler reported errors)"
    return 1
  fi
  if ! grep -q "Compilation successful" /tmp/compiler_out; then
    echo "  FAIL (compilation did not report success)"
    return 1
  fi
  gcc -Isrc/runtime "$OUT_DIR/output.c" src/runtime/string_lib.c -o "$OUT_DIR/program"
  echo "  Running generated program:" 
  "$OUT_DIR/program"
  echo "  OK"
}

run_invalid() {
  local file="$1"
  echo "Running invalid test: $file"
  if [ ! -s "$file" ]; then
    echo "  SKIP (empty)"
    return
  fi
  # capture both stdout and stderr into /tmp/compiler_out
  "$COMPILER" < "$file" 2>&1 | tee /tmp/compiler_out > /dev/null
  if grep -qE "Syntax error|Semantic Error|CodeGen Error" /tmp/compiler_out; then
    echo "  OK (properly rejected)"
  else
    echo "  FAIL (unexpected success)"
    return 1
  fi
}

main() {
  echo "=== VALID TESTS ==="
  for f in test/valid/*.sp; do
    run_valid "$f" || true
    echo
  done

  echo "=== INVALID TESTS ==="
  for f in test/invalid/*.sp; do
    run_invalid "$f" || true
    echo
  done

  echo "Done"
}

main "$@"
