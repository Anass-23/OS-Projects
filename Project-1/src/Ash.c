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

/* static void surt() { */
/* } */

/* Process list */
/* typedef struct { */
/*   pid_t pid; */
/*   bool active; */
/* } proc_t; */


// static pid_t proc_list[MAX_PROC];
// static int proc_indx;





static void handler (int signum) {
  pid_t pid;
  // int wstatus;
  // while ((pid = waitpid(-1, &wstatus, WNOHANG)) > 0);

  while ((pid = waitpid(-1, NULL, WNOHANG)) > 0);

}


// static struct sigaction act = { 0 };

/* static int init_sigaction(void) { */
/*   act.sa_flags = SA_RESTART; */
/*   act.sa_handler = &handler; */
/*   // sigemptyset(&sa.sa_mask); */
/*   if (sigaction(SIGCHLD, &act, NULL) == -1) { */
/*     /\* SIGNAL when a child process terminates *\/ */
/*     perror("-Ash: sigaction"); */
/*     return -1; */
/*   } */

/*   return 0; */
/* } */



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

  // init_sigaction();
  
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
      	} else { /* External command */

	  // signal(SIGCHLD, SIG_IGN); 
	  signal(SIGCHLD, handler); /* No zoombie process, deleted from PCB */
	  
	  /* Parsing cmd and args */
	  // char *argv[] = {"/bin/mvv", "hola2", "hola22", NULL};
	  int argc = 1;
	  char *argv[MAX_ARGS];
	  char *token = NULL;
	  bool background = false;

	  if (args == NULL) {
	    if (strchr(cmd, '&') != NULL) {
	      background = true;
	      cmd = strtok(cmd, "&");
	    }
	    // argv[0] = cmd;
	    argv[1] = NULL;
	  }
	  else {
	    // argv[0] = cmd;
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
		wait(NULL);
		// waitpid(pid, NULL, -1);
	      } else {
		waitpid(pid, NULL, WNOHANG);
	      }

	      
	    }
	  }
 
      	} /* External command */
      }

      clearerr(stderr);     
    }
  }

  return 0;
}
