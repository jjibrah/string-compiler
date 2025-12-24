program
// -------------------------------
// 1) Declarations
// -------------------------------
string s1;
string s2;
string s3;

int i;
int n;

s1 = "Hello";
s2 = "World";

// -------------------------------
// 2) Basic printing + concatenation
// -------------------------------
print(s1);
print(s2);
print(concat(concat(s1, " "), s2));
print(concat(concat(concat("Literal concat: ", "A"), "B"), "C"));

// -------------------------------
// 3) Reassignment
// -------------------------------
s3 = concat(concat(concat(s1, ", "), s2), "!");
print(s3);

s1 = "Hi";
print(concat(concat("After reassignment: ", s1), concat(" ", s2)));

// -------------------------------
// 4) Integers + strings (if supported)
// -------------------------------
i = 5;
n = 3;

// NOTE: implicit int->string concatenation is NOT supported in this language.
// The following prints are removed or commented out:
// print("i = " + i);
// print("n = " + n);

// -------------------------------
// 5) If / else (string comparison)
// -------------------------------
// Not supported by current grammar; skipped.
// if (s2 == "World") { ... }

// -------------------------------
// 6) While loop (repeat building a string) - skipped
// -------------------------------
// while (i < 5) { ... }

// -------------------------------
// 7) Nested conditions - skipped
// -------------------------------

// -------------------------------
// 8) (Optional) string library calls (ONLY if your grammar supports them)
// -------------------------------
// print("len(s2) = " + len(s2));
// print(substr("abcdef", 1, 3));   // expected: "bcd" (depending indexing rules)

// -------------------------------
// 9) (Optional) functions (ONLY if supported)
// -------------------------------

// -------------------------------
// 10) Done
// -------------------------------
print("ALL TESTS DONE");
end
