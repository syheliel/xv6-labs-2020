#include "kernel/types.h"
#include "user/user.h"
int
main(int argc, char *argv[])
{
  if(argc >= 2) {
    write(2, "usage: pingdong", sizeof("usage: pingdong"));
    exit(1);
  }
  int pipe2child[2],pipe2father[2];
  char buf[1];
  // open two pipes
  pipe(pipe2child);
  pipe(pipe2father);
  unsigned int bufSize = sizeof(buf);
  if(fork() == 0){ // child logic : read from parent, then write to parent
    close(pipe2father[0]);
    close(pipe2child[1]);
    if(read(pipe2child[0],buf,bufSize) != bufSize){
      printf("child read error");
      exit(1);
    }
    close(pipe2child[0]);
    printf("%d: received ping\n", getpid());

    if(write(pipe2father[1],buf,bufSize) != bufSize){
      printf("child write error");
      exit(1);
    }
    close(pipe2father[1]);
    exit(0);
  }
  // father logic
  close(pipe2father[1]);
  close(pipe2child[0]);
  if(write(pipe2child[1],buf,bufSize) != bufSize){
    printf("parent write error");
    exit(1);
  }
  close(pipe2child[1]);
  if(read(pipe2father[0],buf,bufSize) != bufSize){
    printf("parent read error");
    exit(1);
  }
  close(pipe2father[0]);
  printf("%d: received pong\n", getpid());
  wait(0);
  exit(0);
}
