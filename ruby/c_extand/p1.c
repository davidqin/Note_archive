#include "p.h"

VALUE method_test1(VALUE self);

// Our 'test1' method.. it simply returns a value of '10' for now.
VALUE method_test1(VALUE self) {
    int x = 10;
    return INT2NUM(x);
}