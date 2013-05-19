/*
ID: davidqh1
LANG: C
TASK: friday
*/
#include <stdio.h>

#define is_leap_year(x) ((x % 4 == 0 && x % 100 != 0) || x % 400 == 0 )

static int common_year[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
static int   leap_year[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

// week 1-7   Monday, Tuesday....Sunday
// weeks[0-6] Sunday, Monday.....Sateday

int week, weeks[7];

void friday(int n){
  int i, j, k = 0;

  for(i = 1900; i < 1900 + n; ++i){
    for(j = 1; j <= 12; j++){

      if(i == 1900 && j == 1)
        week = 6;// 1900-1-13 is 6

      weeks[week]++;

      week = (week + (is_leap_year(i) ? leap_year[j - 1] : common_year[j - 1])) % 7;
    }
  }
}

int main(int argc, char const *argv[])
{
  FILE * in = fopen("friday.in", "r");
  FILE * out = fopen("friday.out", "w");

  int n, i;

  fscanf(in, "%d", &n);

  for(i = 0; i < 7; ++i) weeks[i] = 0;

  friday(n);

  fprintf(out, "%d %d %d %d %d %d %d\n", weeks[6], weeks[0], weeks[1], weeks[2], weeks[3], weeks[4], weeks[5]);

  return 0;
}
