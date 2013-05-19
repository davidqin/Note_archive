#include<stdio.h>

typedef struct {
  int i;
  char c;
  char chs[10];
} Node;

int main(){

  Node n;

  printf("sizeof a node is: %ld\n", sizeof(n));
  printf("sizeof i c chs[10] is: %ld\n", sizeof(n.i) + sizeof(n.c) + sizeof(n.chs) );
  
  return 0;
}
