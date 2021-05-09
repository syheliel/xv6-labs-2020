#include "kernel/types.h"
#include "user/user.h"
int
main(int argc, char *argv[])
{
  if(argc != 2) {
    write(2, "usage:sleep time(clock num)", sizeof("sleep time(clock num)"));
    exit(1);
  }
  int x = atoi(argv[1]);
  sleep(x);
  exit(0);
}
