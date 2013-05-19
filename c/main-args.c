#include <stdio.h>
int main(int argc, char** argv){
  printf("参数个数：%d\n", argc);
  printf("第一个参数：%s\n", argv[0]);
  printf("第二个参数：%s\n", argv[1]);
  printf("第三个参数：%s\n", argv[2]);

  return 0;
}
