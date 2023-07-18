/* header */
enum class Foo {
    one = 1,
    two,  /* comment */
    three
};

int foo(int a, int b, std::vector<int> c);

int foo(int a, int b, FOO c);
