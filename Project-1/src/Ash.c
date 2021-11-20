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

#include <string.h>

#define SHOULD_RUN      1

/* Process list */
typedef struct {
  pid_t pid;
  bool active;
} proc_t;
// static proc_t proc_list[MAX_PROC]; // extern proc_t proc_list[MAX_PROC];


static cmd_t init_cmd(void) {
  cmd_t cmd;
  cmd.cmd[0] = '\0';
  cmd.bg = false;
  return cmd;
}


/* Main Ash shell */
int main(void) {

  cmd_t cmd = init_cmd();
  char *read_in = NULL;
  size_t len = 0;
  ssize_t nread;
  
  while (SHOULD_RUN){ 
    fprintf(stdout, "%s\n", getenv("PWD")); /* Supossing "PWD" is available */
 
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
      // read_in[nread] = '\n';
      printf("<%s>", read_in);
      
      switch (parse(read_in, &cmd)) {
      case none: {
	printf("\n%s\n", "> NONE");
	break;
      }
      case valid: {
	printf("\n%s\n", "> VALID");
	break;
      }
      case invalid: {
	printf("\n%s\n", "> INVALID");
	break;
      }
      default:
	break;
      }

      printf("%s\n", cmd.cmd);
      printf("%s\n", cmd.args);
    }
  }
	
  return 0;
}

