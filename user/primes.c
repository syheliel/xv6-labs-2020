//
// Created by 14976 on 2021/5/10.
//

#include "kernel/types.h"
#include "user/user.h"
int isprime(int p){
  for(int i=2;i<p;i++)
    if(p % i == 0)
      return 0;
  return 1;
}
/**
 *
 * @param pipeline : record the prime of previous call of printPrime and pass current prime to next call
 * @param maxNum : print prime with condition:
 * 1. prime <= maxNum
 */
void printPrime(int pipeline[2],int maxNum){
  int prime = -1;
  read(pipeline[0],&prime,sizeof(prime));
  do prime++; while(!isprime(prime));
  if(prime > maxNum) return;
  printf("prime %d\n",prime);
  write(pipeline[1],&prime,sizeof(prime)); // pass current prime to next call
  if(fork() == 0){ // child logic, call for next prime
    printPrime(pipeline,maxNum);
  }
  wait(0);
  return;
}
int
main(int argc, char *argv[])
{
  int pipeline[2];
  int lowBound = 1;
  pipe(pipeline);
  write(pipeline[1],&lowBound,sizeof(lowBound));
  printPrime(pipeline,35);
  close(pipeline[0]);
  close(pipeline[1]);
  exit(0);
  return 0;
}
