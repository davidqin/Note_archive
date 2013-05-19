/*
ID: davidqh1
LANG: C
TASK: gift1
*/
#include <stdio.h>
#include <string.h>

#define MAX_NP 10
#define NAME_LENGTH 30

int find_people(char * name, char nps[][NAME_LENGTH], int np){
  int i;
  for(i = 0; i < np; ++i){
    if( strcmp(name, nps[i]) == 0 ){
      return i;
    }
  }
  return -1;
}

int main(){
    FILE * in = fopen("gift1.in", "r");
    FILE * out = fopen("gift1.out", "w");
    int np, i, total, nr, j, avg;
    char nps[MAX_NP][NAME_LENGTH], giver[NAME_LENGTH], recevier[NAME_LENGTH];
    int money[MAX_NP];

    fscanf(in, "%d", &np);
    for(i = 0; i < np; ++i){
        fscanf(in, "%s", nps[i]);
        money[i] = 0;
    }

    for(i = 0; i < np; ++i){
        fscanf(in, "%s", giver);
        fscanf(in, "%d %d", &total, &nr);

        if(nr) avg = total / nr;

        for(j = 0; j < nr; j++){
            fscanf(in, "%s", recevier);
            money[find_people(recevier, nps, np)] += avg;
            money[find_people(giver, nps, np)] -= avg;
        }
    }

    for(i = 0; i < np; ++i){
        fprintf(out, "%s %d\n", nps[i], money[i]);
    }

    return 0;
}
