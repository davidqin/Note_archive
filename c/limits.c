#include<stdio.h>
#include<limits.h>

int main(int argc, char const *argv[]){
  printf("CHAR_BIT  %30d\n", CHAR_BIT);
  printf("CHAR_MAX  %30d\n", CHAR_MAX);
  printf("CHAR_MIN  %30d\n", CHAR_MIN);
  printf("INT_MAX   %30d\n", INT_MAX);
  printf("INT_MIN   %30d\n", INT_MIN);
  printf("LONG_MAX  %30ld\n", LONG_MAX);
  printf("LONG_MIN  %30ld\n", LONG_MIN);
  printf("SCHAR_MAX %30d\n", SCHAR_MAX);
  printf("SCHAR_MIN %30d\n", SCHAR_MIN);
  printf("SHRT_MAX  %30d\n", SHRT_MAX);
  printf("SHRT_MIN  %30d\n", SHRT_MIN);
  printf("UCHAR_MAX %30d\n", UCHAR_MAX);
  printf("UINT_MAX  %30ld\n", UINT_MAX);
  printf("ULONG_MAX %30lu\n", ULONG_MAX);
  printf("USHRT_MAX %30d\n", USHRT_MAX);

  return 0;
}
