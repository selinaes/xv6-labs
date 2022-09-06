#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);

  int rc = fork();
  if (rc < 0){ //fork failed, exit
    fprintf(2, "fork failed\n");
    exit(1);
  } else if (rc == 0) { //child
    fprintf(1, "%d: received ping\n", (int)getpid());
    char x;
    read(p[0], &x, 1);
    close(p[0]); //close read end
    write(p[1], x, 1);
    close(p[1]);
  } else { //parent
    //parent write & send to child
    write(p[1], "\n", 1);
    close(p[1]);
    wait(NULL);
    //parent read & print
    char c;
    read(p[0], &c, 1);
    close(p[0]);
    fprintf(1, "%d: received pong\n", (int)getpid());
  }
  exit(0);
}