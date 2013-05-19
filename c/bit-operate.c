#include<stdio.h>
#include<stdlib.h>

void print_bits(const int i){
  int j;
  int bits_length = sizeof(i) * 8;

  for(j = bits_length;j >= 0; --j){
    if((j+1)%4 == 0 && j != bits_length - 1) 
      printf(" ");

    printf("%d", i & (1 << j) ? 1 : 0); 
  }
  printf("\n");
}

unsigned getbits(unsigned x, int p, int n){
  print_bits(x);
  print_bits(x >> (p + 1 - n));
  print_bits(~(~0 << n));
  return (x >> (p+1-n)) & ~(~0 << n);
}

int main(){
  int a = 24;

  print_bits(getbits(a, 4, 2));
  return 0;
}
