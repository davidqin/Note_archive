#include <stdio.h>

void file_copy(FILE *ifp, FILE *ofp);

int main(int argc, char * argv[]){

  FILE *fp = NULL;

  if(argc == 1){
    file_copy(stdin, stdout);
  }

  while(--argc){
    if( (fp = fopen(*++argv, "r")) == NULL ){
      printf("cat: can't open %s\n", *argv);
      return 1;
    } else {
      file_copy(fp, stdout);
      fclose(fp);
    }
  }

  return 0;
}

void file_copy(FILE *ifp, FILE *ofp){
  int c;

  while( (c = getc(ifp)) != EOF )
    putc(c, ofp);
}
