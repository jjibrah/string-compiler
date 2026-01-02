# STRON Compiler Test Cases

## Overview
This document contains test programs for validating the STRON compiler.
Each test case includes the source code, expected behavior, and what it tests.

---

## ✅ Valid Test Cases

### Test 1: String Concatenation
**File:** `tests/valid/concat.sp`

**Purpose:** Tests basic string concatenation operation

**Source Code:**
```stron
program
    string a;
    string b;
    string c;
    
    a = "Hello ";
    b = "World";
    c = concat(a, b);
    
    print(c);
end
```

**Expected Output:**
```
Hello World
```

**Tests:**
- Variable declaration
- String literals
- Assignment statements
- concat() function
- print() statement

---

### Test 2: Substring Extraction
**File:** `tests/valid/substring.sp`

**Purpose:** Tests substring extraction with start index and length

**Source Code:**
```stron
program
    string text;
    string sub;
    
    text = "Programming";
    sub = substr(text, 3, 4);
    
    print(sub);
end
```

**Expected Output:**
```
gram
```

**Tests:**
- substr() function with three parameters
- Integer literals as function arguments
- String indexing (0-based)

---

### Test 3: String Length
**File:** `tests/valid/length.sp`

**Purpose:** Tests length computation and int variable assignment

**Source Code:**
```stron
program
    string message;
    int len;
    
    message = "Compiler";
    len = length(message);
    
    print(len);
end
```

**Expected Output:**
```
8
```

**Tests:**
- length() function returning int
- int variable declaration and assignment
- Mixed type operations (string to int)

---

### Test 4: String Reversal
**File:** `tests/valid/reverse.sp`

**Purpose:** Tests string reversal operation

**Source Code:**
```stron
program
    string original;
    string reversed;
    
    original = "STRON";
    reversed = reverse(original);
    
    print(reversed);
end
```

**Expected Output:**
```
NORTS
```

**Tests:**
- reverse() function
- String manipulation

---

### Test 5: Palindrome Check
**File:** `tests/valid/palindrome.sp`

**Purpose:** Tests palindrome checking (returns boolean)

**Source Code:**
```stron
program
    string word;
    bool result;
    
    word = "racecar";
    result = palindrome(word);
    
    print(result);
end
```

**Expected Output:**
```
true
```

**Tests:**
- palindrome() function returning bool
- bool variable declaration
- Boolean value printing

---

### Test 6: String Comparison
**File:** `tests/valid/compare.sp`

**Purpose:** Tests string comparison operation (additional operation)

**Source Code:**
```stron
program
    string str1;
    string str2;
    bool same;
    
    str1 = "test";
    str2 = "test";
    same = compare(str1, str2);
    
    print(same);
end
```

**Expected Output:**
```
true
```

**Tests:**
- compare() function (additional operation)
- Boolean comparison result

---

### Test 7: Complex Expression
**File:** `tests/valid/complex.sp`

**Purpose:** Tests nested function calls and multiple operations

**Source Code:**
```stron
program
    string a;
    string b;
    string result;
    int len;
    
    a = "Hello";
    b = "World";
    result = concat(a, concat(" ", b));
    len = length(result);
    
    print(result);
    print(len);
end
```

**Expected Output:**
```
Hello World
11
```

**Tests:**
- Nested function calls
- Multiple statements
- Multiple print statements

---

### Test 8: All Operations
**File:** `tests/valid/all_operations.sp`

**Purpose:** Comprehensive test using all string operations

**Source Code:**
```stron
program
    string text;
    string reversed;
    string sub;
    int len;
    bool isPalin;
    
    text = "madam";
    len = length(text);
    reversed = reverse(text);
    sub = substr(text, 1, 3);
    isPalin = palindrome(text);
    
    print(text);
    print(len);
    print(reversed);
    print(sub);
    print(isPalin);
end
```

**Expected Output:**
```
madam
5
madam
ada
true
```

**Tests:**
- All data types
- All operations in one program
- Multiple variable declarations

---

### Test 9: Empty String Handling
**File:** `tests/valid/empty_string.sp`

**Purpose:** Tests handling of empty strings

**Source Code:**
```stron
program
    string empty;
    string result;
    int len;
    
    empty = "";
    len = length(empty);
    result = concat("Hello", empty);
    
    print(len);
    print(result);
end
```

**Expected Output:**
```
0
Hello
```

---

### Test 10: String with Special Characters
**File:** `tests/valid/special_chars.sp`

**Purpose:** Tests strings with special characters

**Source Code:**
```stron
program
    string special;
    
    special = "Hello\nWorld!@#";
    print(special);
end
```

**Expected Output:**
```
Hello
World!@#
```

---


## ❌ Invalid Test Cases

### Error Test 1: Undeclared Variable
**File:** `tests/invalid/undeclared_var.sp`

**Purpose:** Tests semantic error handling for undeclared variables

**Source Code:**
```stron
program
    string a;
    
    a = "Hello";
    print(b);
end
```

**Expected Error:**
```
Semantic Error: Variable 'b' used before declaration
```

**Error Type:** Semantic Error

---

### Error Test 2: Type Mismatch
**File:** `tests/invalid/type_error.sp`

**Purpose:** Tests type checking

**Source Code:**
```stron
program
    string text;
    int num;
    
    text = "Hello";
    num = text;
end
```

**Expected Error:**
```
Semantic Error: Type mismatch - cannot assign string to int variable
```

**Error Type:** Semantic Error

---

### Error Test 3: Missing Semicolon
**File:** `tests/invalid/syntax_error.sp`

**Purpose:** Tests syntax error detection

**Source Code:**
```stron
program
    string a
    
    a = "Hello";
    print(a);
end
```

**Expected Error:**
```
Syntax Error: Expected ';' after variable declaration
```

**Error Type:** Syntax Error

---

### Error Test 4: Wrong Number of Arguments
**File:** `tests/invalid/wrong_args.sp`

**Purpose:** Tests function argument validation

**Source Code:**
```stron
program
    string result;
    
    result = concat("Hello");
end
```

**Expected Error:**
```
Semantic Error: Function 'concat' expects 2 arguments, got 1
```

**Error Type:** Semantic Error

---

### Error Test 5: Invalid Token
**File:** `tests/invalid/lexical_error.sp`

**Purpose:** Tests lexical error handling

**Source Code:**
```stron
program
    string text;
    
    text = "Hello";
    @ invalid;
end
```

**Expected Error:**
```
Lexical Error: Invalid token '@' at line 5
```

**Error Type:** Lexical Error

---

### Error Test 6: Missing Program Keyword
**File:** `tests/invalid/missing_program.sp`

**Purpose:** Tests program structure validation

**Source Code:**
```stron
string a;
a = "Hello";
print(a);
end
```

**Expected Error:**
```
Syntax Error: Program must begin with 'program' keyword
```

**Error Type:** Syntax Error

---

### Error Test 7: Missing End Keyword
**File:** `tests/invalid/missing_end.sp`

**Purpose:** Tests program termination validation

**Source Code:**
```stron
program
    string a;
    a = "Hello";
    print(a);
```

**Expected Error:**
```
Syntax Error: Program must end with 'end' keyword
```

**Error Type:** Syntax Error

---

### Error Test 8: Reserved Keyword as Identifier
**File:** `tests/invalid/keyword_as_var.sp`

**Purpose:** Tests keyword reservation

**Source Code:**
```stron
program
    string string;
    
    string = "Hello";
end
```

**Expected Error:**
```
Lexical Error: Cannot use reserved keyword 'string' as identifier
```

**Error Type:** Lexical Error


### Error Test 9: Substr Out of Bounds
**File:** `tests/invalid/substr_bounds.sp`

**Purpose:** Tests runtime boundary checking (if implemented)

**Source Code:**
```stron
program
    string text;
    string sub;
    
    text = "Short";
    sub = substr(text, 10, 5);
    
    print(sub);
end
```

**Expected Error:**
```
Runtime Error: Substring index out of bounds
```

**Error Type:** Runtime Error (or Semantic Warning)

---

### Error Test 10: Function as Statement
**File:** `tests/invalid/function_not_assigned.sp`

**Purpose:** Tests that function calls must be assigned or printed

**Source Code:**
```stron
program
    string a;
    string b;
    
    a = "Hello";
    b = "World";
    concat(a, b);
end
```

**Expected Error:**
```
Syntax Error: Function call result must be assigned or printed
```

**Error Type:** Syntax Error
