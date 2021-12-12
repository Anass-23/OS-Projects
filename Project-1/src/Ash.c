/**
 * Author:    Anass Anhari Talib
 * Created:   15.11.2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../include/defs.h"
#include "../include/built_in.h"

#define SHOULD_RUN 1

static pid_t proc_list[MAX_PROC];
static int proc_indx = 0;

/*
 * Static functions
 */
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
      args = strtok(tmp_read_in, "\n"); /* tmp_read_in will only
					   contain the args part */
  
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
	  break;
	} else { /* External command */
	  
	  int argc = 1;
	  char *argv[MAX_ARGS];
	  char *token;
	  bool background;
	  
	  token = NULL; background = false;
	  
	  if (args == NULL) {
	    if (strchr(cmd, '&') != NULL) {
	      background = true;
	      cmd = strtok(cmd, "&");
	    }
	    argv[1] = NULL;
	  }
	  else {
	    token = strtok(args, " ");
	    while (token != NULL) {
	      argv[argc++] = token;
	      token = strtok(NULL, " ");
	    }
	    argv[argc] = NULL;

	    if (strchr(argv[argc-1], '&') != NULL) {
	      background = true;
	      argv[argc-1] = strtok(argv[argc-1], "&");
	    }
	  }

	  /* if (proc_indx == MAX_PROC && background) { */
	  /*   fprintf(stderr, "-Ash: Process limit reached, use clear to kill all the background processes\n"); */
	  /* } else { */
		    
	  /* Searching external command */
	  if ((cmd_path = find_cmd(cmd, cwd)) == NULL) {
	    fprintf(stderr, "-Ash: %s: command not found\n", cmd);
	  } else {
	    /* Executing the external command */
	    argv[0] = cmd_path;
	    
	    pid_t pid;
	    pid = fork();

	    if (pid < 0) {
	      fprintf(stderr, "-Ash: %s: error", cmd);
	    } else if (pid == 0) {
	      execv(argv[0], argv);
	      fprintf(stderr, "-Ash: %s: ", cmd);
	      perror("");
	      exit(EXIT_FAILURE);
	    } else {
	      if (!background) {
		wait(NULL); // waitpid(pid, NULL, -1);
	      } else {
		proc_list[proc_indx++] = pid;
	      }
	    }
	  }
	    //  }
      	} /* External command */
      }

      clearerr(stderr);     
    }
  }

  return 0;
}
