#include <unistd.h>

int main(){
  char buff[100];
  int n;
  while( (n = read(0, buff, 100)) > 0)
    write(1, buff, n);
  return 0;
}
