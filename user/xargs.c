//
// Created by 14976 on 2021/5/10.
//

#include "kernel/types.h"
#include "user/user.h"
int
main(int argc, char *argv[])
{
  char inputBuf[32]; // record the input from previous command
  char charBuf[320]; // buf for the char of all token
  char* charBufPointer = charBuf;
  int charBufSize = 0;

  char *commandToken[32]; // record the token from input spilt by space(' ')
  int tokenSize = argc - 1;// record token number(initial is argc - 1,because xargs will bot be execute)
  int inputSize = -1;

  // first copy initial argv argument to commandToken
  for(int tokenIdx=0;tokenIdx<tokenSize;tokenIdx++)
    commandToken[tokenIdx]=argv[tokenIdx+1];


  while((inputSize = read(0,inputBuf,sizeof(inputBuf))) > 0){
    for(int i = 0; i < inputSize;i++){
      char curChar = inputBuf[i];
      if(curChar == '\n'){// if read '\n', execute the command
        charBuf[charBufSize] = 0; // set '\0' to end of token
        commandToken[tokenSize++] = charBufPointer;
        commandToken[tokenSize] = 0; // set nullptr in the end of array

        if(fork()==0){ // open child to execute
          exec(argv[1],commandToken);
        }
        wait(0);
        tokenSize = argc - 1;// initialize
        charBufSize = 0;
        charBufPointer = charBuf;
      }
      else if(curChar == ' '){
        charBuf[charBufSize++] = 0; // mark the end of string
        commandToken[tokenSize++] = charBufPointer;
        charBufPointer = charBuf+charBufSize; // change to the start of new string
      }else{
        charBuf[charBufSize++] = curChar;
      }

    }
  }
  exit(0);
}
