#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int result;

  if(argc > 1){
    fprintf(2, "No argument needed for countsys\n");
    exit(1);
  }

  result = countsys();
  fprintf(1, "%d\n",result);
  exit(0);
}
