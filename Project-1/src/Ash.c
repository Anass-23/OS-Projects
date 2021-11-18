/**
 * Author:    Anass Anhari Talib
 * Created:   15.09.2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "include/defs.h"
#include "include/parser.h"

#define SHOULD_RUN      1

/* Process list */
typedef struct {
  pid_t pid;
  bool active;
} proc_t;
static proc_t proc_list[MAX_PROC]; // extern proc_t proc_list[MAX_PROC];

/* Main Ash shell */
int main(void) {

  char *read_in = NULL;
  size_t len = 0;
  ssize_t nread;
	   
  while (SHOULD_RUN){ 
    fprintf(stdout, "%s\n", getenv("PWD")); // Supossing "PWD" is available
    
    nread = getline(&read_in, &len, stdin);

    if (nread == -1) {
      perror("-Ash: Error: Some error ocurred");
      return(-1);
    }
    else if (nread > MAX_LINE) {
      perror("-Ash: Error: Exceeded line command length");
      return(-1);
    }
    else {
      fprintf(stdout, "%s", read_in);
    }   
  }
	
  return 0;
}

