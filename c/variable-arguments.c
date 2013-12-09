#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include "sys/syscall.h"


// void error(const char *, ...);

void error(const char * fmt, ...){
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);

    // exit(1);
}


int main(int argc, char * argv[]){
    int f1, f2, n;
    char buf[1024];

    error("Usage: cp from to ");
    error("cp: can't open %s", argv[1]);
    error("cp: can't create %s, mode %03o", argv[2], 0666);
}
