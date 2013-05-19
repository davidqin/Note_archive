#include<stdio.h>

void foo(int * i){
  printf("sizeof i[] is %ld\n", sizeof(i));
}

int main(){
  char ch, chs[100];
  printf("sizeof char is %ld\n", sizeof(ch));
  printf("sizeof char[100] is %ld\n", sizeof(chs));

  signed char s_ch;
  printf("sizeof signed char is %ld\n", sizeof(s_ch));

  unsigned char us_ch;
  printf("sizeof unsigned char is %ld\n", sizeof(us_ch));

  int i, is[100];
  printf("sizeof int is %ld\n", sizeof(i));
  printf("sizeof int[100] is %ld\n", sizeof(is));
  foo(is);

  signed int s_i;
  printf("sizeof signed int is %ld\n", sizeof(s_i));

  unsigned int us_i;
  printf("sizeof unsigned int is %ld\n", sizeof(us_i));

  short int short_i;
  printf("sizeof short int is %ld\n", sizeof(short_i));

  signed short s_short_i;
  printf("sizeof signed short is %ld\n", sizeof(s_short_i));

  unsigned short us_short_i;
  printf("sizeof unsigned short is %ld\n", sizeof(us_short_i));

  long int long_i;
  printf("sizeof long int is %ld\n", sizeof(long_i));

  signed long s_long_i;
  printf("sizeof signed long is %ld\n", sizeof(s_long_i));

  unsigned long us_long_i;
  printf("sizeof unsigned long is %ld\n", sizeof(us_long_i));

  long long int l_l_i;
  printf("sizeof long long int is %ld\n", sizeof(l_l_i));

  float f;
  printf("sizeof float is %ld\n", sizeof(f));

  double d;
  printf("sizeof double is %ld\n", sizeof(d));

  long double long_d;
  printf("sizeof long double is %ld\n", sizeof(long_d));

  return 0;
}
