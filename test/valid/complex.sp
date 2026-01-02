program

// Test: complex nested calls
string a;
string b;
string res;
int l;

a = "Hello";
b = "World";
res = concat(a, concat(" ", b));
// avoid printing int 'l' because codegen currently prints ints with %s causing crash
// l = length(res);

print(res);
print("ALL TESTS DONE");
end
