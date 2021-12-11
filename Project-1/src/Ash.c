/**
 * Author:    Anass Anhari Talib
 * Created:   15.11.2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// #include <stdio.h>
// #include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

#include "../include/defs.h"
#include "../include/built_in.h"


#define SHOULD_RUN 1

/* static void surt() { */
/* } */



/* Process list */
/* typedef struct { */
/*   pid_t pid; */
/*   bool active; */
/* } proc_t; */

/* static proc_t proc_list[MAX_PROC]; */
/* static int proc_indx; */


static char cwd[MAX_PATH];
static void display_prompt(void) {
  if (getcwd(cwd, MAX_PATH) == NULL) {
    fprintf(stdout, "%% %s> ", getenv("PWD"));
  } else {
    fprintf(stdout, "%% %s> ", cwd); 
  }
}



static char* find_cmd(char *cmd, char* cwd) {
  /* DO NOT MODIFY PATH STRING! */
  char *PATH = strcat(strcat(cwd, ":"), getenv("PATH"));
  char *token = NULL, *cmd_path = NULL;
  DIR *DIR_fd;
  struct dirent *DIR_entry;
 
  token = strtok(strdup(PATH), ":");
  while (token != NULL) {
    DIR_fd = opendir(token);
    if (DIR_fd == NULL) { /* If error continue */
    }
    else {
      while ((DIR_entry = readdir(DIR_fd)) != NULL) {	
	if (DIR_entry->d_type == DT_REG) {		  
	  if (strcmp(DIR_entry->d_name, cmd) == 0) {
	    // trobat
	    // fprintf(stdout, "%s\n", DIR_entry->d_name);
	    // fprintf(stdout, "%s\n", token);
	    cmd_path = strcat(strcat(token, "/"), cmd);
	    return cmd_path;	    
	  }
	}
		
      }
      closedir(DIR_fd);
    }
    token = strtok(NULL, ":");
  }

  return NULL;
}


/*
 * Main Ash shell
 */
int main(void) {

  char *read_in = NULL, *tmp_read_in = NULL;
  char *cmd = NULL, *cmd_path = NULL;
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
      /* tmp_read_in will only contain the args part */
      args = strtok(tmp_read_in, " \n");

      printf("> cmd: '%s'\n", cmd);
      printf("> args: '%s'\n", args);
     
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

	  if ((cmd_path = find_cmd(cmd, cwd)) == NULL) {
	    fprintf(stderr, "-Ash: %s: command not found\n", cmd);
	  } else {
	    printf("%s\n", find_cmd(cmd, cwd));
	    
	    pid_t pid;
	  
	    /* fork a child process */
	    pid = fork();
	    if (pid < 0) {
	      /* error occurred */
	      fprintf(stderr, "-Ash: %s: something went wrong\n", cmd);
	      // return 1;
	    }
	    else if (pid == 0) { /* child process */
	      execve(cmd_path, &args, NULL);
	    }
	    else { /* parent process */
	      wait(NULL);
	    }
	    
	  }
      	}
      }

      clearerr(stderr);     
    }
  }

  return 0;
}
