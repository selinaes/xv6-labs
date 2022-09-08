#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);

  int p2[2];
  pipe(p2);

  int rc = fork();
  if (rc < 0){ //fork failed, exit
    fprintf(2, "fork failed\n");
    exit(1);
  } else if (rc == 0) { //child
    close(p[1]); //close write end of p
    char x;
    read(p[0], &x, 1);
    fprintf(1, "%d: received ping\n", (int)getpid());
    close(p[0]); //close read end of p

    close(p2[0]); //close read end of p2
    write(p2[1], &x, 1);
    close(p2[1]); //close write end of p2

  } else { //parent
    //parent write & send to child
    close(p[0]); //close read end of p
    write(p[1], "\n", 1);
    close(p[1]); //close write end of p
    wait(NULL);
    //parent receive from child, read & print
    char c;
    close(p2[1]); //close write end of p2
    read(p2[0], &c, 1);
    close(p2[0]); //close read end of p2
    fprintf(1, "%d: received pong\n", (int)getpid());
  }
  exit(0);
}