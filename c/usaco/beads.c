/*
ID: davidqh1
LANG: C
TASK: beads
*/
#include <stdio.h>

int  n, size;
char beads[355];

int pre(int n){
  if(n > 1)
    return n - 1;
  else
    return size;
}

int next(int n){
  if(n < size)
    return n + 1;
  else
    return 1;
}

int main(){
  freopen("beads.in","r",stdin);
  freopen("beads.out","w",stdout);

  scanf("%d %s", &n, beads + 1);
  size = n;

  int i, count, max_count = 0, pre_p, next_p;
  char base, ch;

  ch = beads[1];
  for(i = 1; i <= size; ++i){
    if(ch != beads[i]) break;
  }

  if(i > size){
    printf("%d\n", size);
    return 0;
  }

  for(i = 1; i <= size; ++i){
    if(beads[i] == beads[next(i)]) continue;
    count = 0;

    pre_p = i;
    next_p = next(i);

    base = beads[i];

    while( (base == 'w' || base == beads[pre_p] || beads[pre_p] == 'w') && (pre_p != next_p) ){
      if(base == 'w' && beads[pre_p] != 'w')
        base = beads[pre_p];

      count++;
      pre_p = pre(pre_p);
    }

    base = beads[next(i)];
    while( (base == 'w' || base == beads[next_p] || beads[next_p] == 'w') && (pre_p != next_p) ){
      if(base == 'w' && beads[next_p] != 'w')
        base = beads[next_p];

      count++;
      next_p = next(next_p);
    }

    if(pre_p == next_p)
      count ++;

    if(count > max_count){
      max_count = count;}
  }

  printf("%d\n", max_count);

  return 0;
}
