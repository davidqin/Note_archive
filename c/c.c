#include<stdio.h>
// #define W 5
// #define H 3
char cube[5][7] = {{"&&*---*"},{"&/   /|"},{"*---* *"},{"|   |/&"},{"*---*&&"}};
char map[50][50];

void draw(int x, int y)
{
  int i,j;
  x -= 2;
  for(i=0;i<5;i++)
    for(j=0;j<7;j++){
      if(cube[i][j] == '&')continue;
      map[x+i][y+j] = cube[i][j];
    }
}

int main()
{
  int i,j,row, col, tmp, k;

  int h,w;

  int matixe[50][50];

  while(scanf("%d%d", &row, &col)){

    for(i=0;i<row;i++)
      for(j=0;j<col;j++)
        scanf("%d", &matixe[i][j]);


    w = 1 + 4 * col + 2 * row;
    h = 0;
    for(i=0;i<row;i++){
      tmp = 0;
      for(j=0;j<col;j++){
        if(matixe[i][j] > tmp) tmp = matixe[i][j];
      }
      tmp = 1 + tmp * 2 + 2 + (row - i - 1) * 2;
      if(tmp > h) h = tmp;
    }

    for(i=0;i<h;i++)
      for(j=0;j<w;j++){
        map[i][j] = ' ';
      }

    for(i=0;i<row;i++)
      for(j=0;j<col;j++)
        for(k=0;k<matixe[i][j];k++){
          draw(h - 1 - 2 - (row - i - 1) * 2 - k * 2, j * 4 + (row - i - 1) * 2);
      }

    for(i=0;i<h;i++,printf("\n"))
      for(j=0;j<w;j++){
        printf("%c", map[i][j]);

      }
  }
  return 0;
}