#include<stdio.h>

#define STACK_SIZE 20

static int stack[STACK_SIZE];
static int stack_end = 0;

void push(int num){
  if(stack_end < STACK_SIZE)
    stack[stack_end++] = num;
  else
    printf("Error: stack full, cant't push %d\n", num);
}

int pop(){
  if(stack_end > 0)
    return stack[--stack_end];
  else
    printf("Error: stack empty!\n");
}

int atoi(char *num){
  int i, result = 0;
  for(i = 0; num[i] != '\0'; ++i){
    result = result * 10 + num[i] - '0';
  }
  return result; 
}

int main(int argc, char *argv[]){

  int i;
  if(argc <= 1){
    printf("Use case expr x x x !");
    return 1;
  }
  
  char *ch;
  int tmp;

  for(++argv; argv[0]; ++argv){
    ch = argv[0];
    switch(*ch){
      case '+':
        push(pop() + pop());
        break;
      case '-':
        tmp = pop(); 
        push(pop() - tmp);
        break;
      case '*':
        push(pop() * pop());
        break;
      case '/':
        tmp = pop();
        if(!tmp){
          printf("Error: zero divesor\n");
          return 1;
        }
        push(pop() / tmp);
        break;
      default: //I think all number here
        push(atoi(ch));
    }
  }

  printf("Result is %d\n", pop());
  return 0;
}
