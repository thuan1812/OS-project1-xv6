#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char * argv[]) {

  //int status;
  if (argc != 1) {
    printf("error!\n");
    exit(1);
  }
  else {
   char buf[] = "a";
   int p1[2], p2[2]; 
   if (pipe(p1) == -1) {
    printf("error creating pipe from parent to child\n");
    exit(1);
   }
   if (pipe(p2) == -1) {
    printf("error creating pipe from child to parent\n");
    exit(1);
   }
   int PID = fork();
   if (PID < 0) {
    printf("error fork");
    exit(1);
   }
   else if (PID == 0) { //child process
    close(p1[1]);
    close(p2[0]);
    //printf("%d", wait(0));
    if (read(p1[0], buf, 1) == 1) {
      printf("%d: received ping\n",getpid());
		  write(p2[1], buf, 1);
    }
    else {
      printf("receiving error!");
      exit(0);
    }
    exit(0);
   } 
   else {  //parent process (PID > 0)
      
      close(p1[0]);
      close(p2[1]);
      write(p1[1], buf, 1);
      wait(0);
      if(read(p2[0], buf, 1) == 1){
		    printf("%d: received pong\n", getpid());
	    }
	    else {
	  	  printf("receiving error parent.");
		    exit(1);
	    }
   }
   exit(0);
 }
}
