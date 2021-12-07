/**
 * Author:    Anass Anhari Talib
 * Created:   15.11.2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "include/defs.h"

// #include <limits.h>
// #include <stdbool.h>
// #include "include/parser.h"

#define SHOULD_RUN 1

static void surt() {
}



/* Process list */
/* typedef struct { */
/*   pid_t pid; */
/*   bool active; */
/* } proc_t; */

/* static proc_t proc_list[MAX_PROC]; */
/* static int proc_indx; */



static void display_prompt(void) {
  char cwd[MAX_PATH];
  if (getcwd(cwd, MAX_PATH) == NULL) {
    fprintf(stdout, "%% %s> ", getenv("PWD"));
  } else {
    fprintf(stdout, "%% %s> ", cwd); 
  }
}


/*
 * Main Ash shell
 */

int main(void) {

  char *read_in = NULL;
  char *tmp_read_in = NULL;
  char *cmd = NULL;
  char *args = NULL;
  
  size_t len = 0;
  ssize_t nread;
  
  while (SHOULD_RUN) {
    
    display_prompt();
    
    nread = getline(&read_in, &len, stdin);
    if (nread == -1) {
      perror("-Ash: some internal error ocurred");
    } else {
      
      tmp_read_in = read_in;
      cmd = strsep(&tmp_read_in, " ");
      cmd = strtok(cmd, "\n");
      args = tmp_read_in; /* tmp_read_in will only contain the args
			     part */

      // printf("cmd: '%s'\n", cmd);
      // printf("args: '%s'\n", args);
      // printf("args: '%s'\n", strtok(args, " \n"));
      
      if (cmd) {
	if (strcmp(cmd, "ic") == 0) {
	  if (args == NULL) {
	    ic();
	  } else {
	    perror("-Ash: ic, does not accept arguments");
	  }	
	} else if (strcmp(cmd, "cd") == 0) {
	  cd(args);
	} else if (strcmp(cmd, "cm") == 0) {
	  cm(args);
	} else if (strcmp(cmd, "co") == 0) {
	  co(args);
	} else if (strcmp(cmd, "surt") == 0) {
	  surt();
	} else { /* External command or */
	}	
      }

      clearerr(stderr);     
    }
  }

  return 0;
}
