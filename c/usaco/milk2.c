/*
ID: davidqh1
LANG: C
TASK: milk2
*/
#include <stdio.h>
#include <string.h>

int main(){
  freopen("milk2.in", "r", stdin);
  freopen("milk2.out", "w", stdout);
  int n, i, j, begin, end, max_end, min_begin, r1, r2, max_r1, max_r2;
  unsigned char table[1000001], current;

  memset(table, '0', 1000001);

  scanf("%d", &n);
  max_end = 0;
  min_begin = 1000000;

  if( n == 1){
    scanf("%d %d", &begin, &end);
    printf("%d 0\n", end - begin);
    return 0;
  }

  for(i = 0; i < n; ++i){
    scanf("%d %d", &begin, &end);

    if( begin < min_begin )
      min_begin = begin;

    if( max_end < end )
      max_end = end;

    memset(table + begin, '1', end - begin);
  }

  current = table[min_begin];
  r1 = 0; r2 = 0;
  max_r1 = 0; max_r2 = 0;
  for(i = min_begin; i < max_end; ++i){

    if( table[i] != current ){
      if( current == '1' ){
        if( max_r2 < r2) max_r2 = r2;
        r2 = 0;
        current = '0';
      }
      else if ( current == '0' ){
        if( max_r1 < r1) max_r1 = r1;
        r1 = 0;
        current = '1';
      }
    }

    if( current == '1' ){
      r1++;
    }

    if( current == '0' ){
      r2++;
    }
  }

  if( max_r2 < r2) max_r2 = r2;
  if( max_r1 < r1) max_r1 = r1;

  printf("%d %d\n", max_r1, max_r2);

  return 0;
}
