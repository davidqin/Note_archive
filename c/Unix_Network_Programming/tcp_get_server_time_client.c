#include "unp.h"
#include <arpa/inet.h>

int main(int argc, char **argv){
  int sockfd, n;
  char recvline[MAXLINE + 1];
  struct sockaddr_in servaddr;

  if(argc != 2)
    err_quit("usage: a.out <IPaddress>");

  if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    err_quit("socket_error");
  
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port   = htons(3000);
  
  if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0 )
    err_quit("inet_pton error for %s", argv[1]);

  if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    err_quit("connect error");

  while( (n = read(sockfd, recvline, MAXLINE)) > 0){
    recvline[n] = 0;

    if( fputs(recvline, stdout) == EOF)
      err_quit("fputs error");
  }

  if(n<0)
    err_quit("read error");
  
  exit(0);
}
