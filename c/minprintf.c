#include<stdio.h>
#include<string.h>
#include<stdarg.h>

void minprintf(char *fmt, ...){
  va_list ap;
  char *p, *sval;
  double dval;
  int ival;

  va_start(ap, fmt);
  for(p = fmt; *p; ++p){
    if(*p != '%'){
      putchar(*p);
      continue;
    }
    switch(*++p){
      case 'd':
        ival = va_arg(ap, int);
        printf("%d", ival);
        break;
      case 'f':
        dval = va_arg(ap, double);
        printf("%f", dval);
        break;
      case 's':
        for(sval = va_arg(ap, char *); *sval; ++sval){
          putchar(*sval);
        }
        break;
      default:
        putchar(*p);
        break;
    }
  }
  va_end(ap);
}

void minscanf(char *fmt, ...){
  va_list ap;
  char * p, chs[30], ch;
  float f;
  int i;

  va_start(ap, fmt);
  for(p = fmt; *p; ++p){
    if(*p != '%'){
      continue;
    }
    switch(*++p){
      case 'd':
        scanf("%d", &i);
        *(va_arg(ap, int *)) = i;
        break;
      case 'f':
        scanf("%f", &f);
        *(va_arg(ap, double *)) = f;
        break;
      case 's':
        scanf("%s", chs);
        strcpy(va_arg(ap, char *), chs);
        break;
      case 'c':
        scanf("%c", &ch);
        *(va_arg(ap, char *)) = ch;
        break;
      default:
        break;
    }
  }
  va_end(ap);
}

int main(){
  minprintf("%d %f %s\n", 10, 100.2, "Keep going!!");
  return 0;
}
