#include<stdio.h>
#include<stdlib.h>

char * escape(const char chs[]){
  char * result = (char *)malloc(sizeof(char) * 200);
  int i, j;
  for(i = 0, j = 0; chs[i] != '\0'; ++j, ++i){
    switch(chs[i]){
      case '\t':
        result[j++] = '\\'; 
        result[j] = 't'; 
        break;
      case '\n':
        result[j++] = '\\';
        result[j] = 'n';
        break;
      default:
        result[j] = chs[i];
    }
  }

  result[j] = '\0';

  return result;
}

int main(){
  char ch, chs[20];
  int i;

  for(i = 0; (ch = getchar()) != EOF && i < 20; ++i){
    chs[i] = ch;
  }

  chs[i] = '\0';
  char * escape_chars = escape(chs);

  printf("%s\n", escape_chars);

  free(escape_chars);
  return 0;
}
