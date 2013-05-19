#include<stdio.h>

int main(){
  char ch;
  
  while(ch = getchar() != EOF);
  printf("The EOF is \"%c\"\n", ch);
  return 0; 
}
