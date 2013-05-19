#include<stdio.h>

int main(){
  char *name[]     = {"Illegal month", "January", "February", "March"};
  char aname[][15] = {"Illegal month", "January", "February", "March"};

  char **p = name;

  printf("Sizeof name      %10lu\n", sizeof(name));
  printf("Sizeof name + 0  %10lu\n", sizeof(name + 0));

  printf("**name is        %10c\n",  *(*++p));
  printf("**name is        %10c\n",  (*++p)[0]);
  printf("**name is        %10c\n",  *p[0]);
  printf("**name is        %10c\n",  *++p[0]);

  printf("Sizeof aname     %10lu\n", sizeof(aname));

  return 0;
}
