/*
ID: davidqh1
LANG: C
TASK: transform
*/
#include <stdio.h>

int n;
char t1[10][10], t2[10][10], tt[10][10];

void right90(){
  int i,j;
  for(i = 0; i < n; ++i)
    for(j = 0; j < n; ++j)
      tt[j][n-i-1] = t1[i][j];

  for(i = 0; i < n; ++i)
    for(j = 0; j < n; ++j)
      t1[i][j] = tt[i][j];
}

void image(){
  int i,j;
  for(i = 0; i < n; ++i)
    for(j = 0; j < n; ++j)
      tt[i][n-j-1] = t1[i][j];

  for(i = 0; i < n; ++i)
    for(j = 0; j < n; ++j)
      t1[i][j] = tt[i][j];
}

int equal(){
  int i,j;
  for(i = 0; i < n; ++i)
    for(j = 0; j < n; ++j)
      if(tt[i][j] != t2[i][j])
        return 0;

  return 1;
}

int main(){
  freopen("transform.in", "r", stdin);
  freopen("transform.out", "w", stdout);
  int i, j, flag;

  scanf("%d", &n);

  for(i = 0; i < n; ++i){
    scanf("%s", t1[i]);
  }

  for(i = 0; i < n; ++i){
    scanf("%s", t2[i]);
  }

  if( equal() ){
    printf("6\n");
    return 0;
  }

  for(i = 1; i < 4; ++i){
    right90();
    if( equal() ){
      printf("%d\n", i);
      return 0;
    }
  }

  right90();
  image();

  if( equal() ){
    printf("4\n");
    return 0;
  }

  for(i = 1; i < 4; ++i){
    right90();
    if( equal() ){
      printf("5\n");
      return 0;
    }
  }

  printf("7\n");
  return 0;
}
