#include<stdio.h>

int main(int argc,char *argv[]){
  char *file_name = argv[1];
  FILE *fp = NULL;
  if(!file_name){
    printf("No file given!");
    return 1;
  }
  
  if((fp = fopen(file_name, "rb")) == NULL){
    printf("Open File Failed!\n");
  }

  while(!feof(fp)){
    putchar(fgetc(fp));
  }

  return 0;
}
