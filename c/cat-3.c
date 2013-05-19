#include <unistd.h>
#include <fcntl.h>

void file_copy(int ifp, int ofp);

int main(int argc, char * argv[]){

  int ifp, ofp;

  if(argc == 1){
    file_copy(0, 1);
  }

  while(--argc){
    if( (ifp = open(*++argv, O_RDONLY, 0)) == -1 ){
      // white(2, "cat: can't open %s\n", *argv);
      return 1;
    } else {
      file_copy(ifp, 1);
      close(ifp);
    }
  }

  return 0;
}

void file_copy(int ifp, int ofp){
  int c;
  char buffer[100];

  while( (c = read(ifp, buffer, 100)) > 0 )
    write(ofp, buffer, c);
}
