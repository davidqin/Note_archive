#include <stdio.h>

unsigned int SDBMHash(char *str)
{
 unsigned int hash = 0;

 while (*str)
 {
  // equivalent to: hash = 65599*hash + (*str++);
  hash = (*str++) + (hash << 6) + (hash << 16) - hash;
 }

 return (hash & 0x7FFFFFFF);
}

int main(){
    printf("%d\n", SDBMHash("asdfwefwefwewefwfwefwefwefwefwefwefweffw12"));
    return 0;
}
