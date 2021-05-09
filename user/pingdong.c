#include "kernel/types.h"
#include "user/user.h"
int
main(int argc, char *argv[])
{
  if(argc >= 2) {
    write(2, "usage: pingdong", sizeof("usage: pingdong"));
    exit(1);
  }
  int childPid = fork();
  int pid = getPid();
  if(childPid > 0)
  {

  }else{

  }
  exit(0);
}
