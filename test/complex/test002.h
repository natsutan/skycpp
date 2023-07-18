
enum class Baa {
    zero = 3,
    one,
    two
};


struct FFF {
    enum class Foo {
        zero,
        one = 5,
        two  //comment
    };

    int a;
    virtual void f();

};