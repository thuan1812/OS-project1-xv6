#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int 
main(int argc, char * argv[]) {

  if (argc != 2)  {
    printf("error!\n");
    exit(1);
  }
  else {
    int ticks = atoi(argv[1]);
    sleep(ticks);
  }
  exit(0);
}