#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  
  // while(1);
  
  for (int i = 1; i < 11; i++) {
    sleep(1);
    printf("Time: %d\n", i);
  }

  exit(EXIT_SUCCESS);
}
