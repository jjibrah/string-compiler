# STRON – STRing OperatioN Language
Language Specification

## 1. Introduction
STRON (STRing OperatioN Language) is a simple source language designed to demonstrate
basic compiler construction concepts. The language focuses on string processing
operations such as concatenation, substring extraction, length computation,
string reversal, palindrome checking, and string comparison.

## 2. Program Structure
A STRON program must begin with the keyword `program` and end with the keyword `end`.
All statements are written between these two keywords.

Syntax:
program
    <statements>
end

## 3. Data Types
STRON supports the following data types:

- string : sequence of characters
- int    : integer numbers
- bool   : boolean values (true or false)

## 4. Keywords
The following keywords are reserved and cannot be used as identifiers:

program, end, string, int, bool, print,
true, false,
concat, substr, length, reverse, palindrome, compare

## 5. Operators and Symbols

- Assignment operator      : =
- Statement terminator     : ;
- Parentheses              : ( )
- Comma                    : ,

## 6. Variable Declaration
Variables must be declared before they are used.

Syntax:
<type> <identifier> ;

Example:
string name;
int count;
bool result;

## 7. Assignment Statement
Assignment assigns the value of an expression to a variable.

Syntax:
<identifier> = <expression> ;

Example:
name = "Hello";
count = length(name);

## 8. Print Statement
The print statement outputs the value of an expression.

Syntax:
print(<expression>);

Example:
print(name);
print(length(name));

## 9. Supported String Operations

- concat(s1, s2)
  Concatenates two strings and returns a string.

- substr(s, start, length)
  Extracts a substring from string s starting at index start with the given length.

- length(s)
  Returns the length of string s as an integer.

- reverse(s)
  Returns the reverse of string s.

- palindrome(s)
  Returns true if string s is a palindrome, otherwise false.

- compare(s1, s2)
  Compares two strings and returns true if they are equal, otherwise false.

## 10. Expressions
Expressions can be:

- string literals
- integer numbers
- boolean values
- identifiers
- function calls

## 11. Constraints and Rules

- All variables must be declared before use
- Type mismatches are not allowed
- Function arguments must match the required number and types
- String literals must be enclosed in double quotes
- Every statement must end with a semicolon

## 12. Target Language
The STRON compiler translates source programs into C code.
