// Include the Ruby headers and goodies
#include "p.h"

// Defining a space for information and references about the module to be stored internally
VALUE MyTest = Qnil;

// Prototype for the initialization method - Ruby calls this, not you
void Init_mytest();

// The initialization method for this module
void Init_mytest() {
    MyTest = rb_define_module("MyTest");
    rb_define_method(MyTest, "test1", method_test1, 0);
}
