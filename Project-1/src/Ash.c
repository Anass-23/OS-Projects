/**
 * Author:    Anass Anhari Talib
 * Created:   15.11.2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "include/defs.h"
#include "include/parser.h"

#include <string.h>


#include <limits.h>



#define SHOULD_RUN      1

////////////////////////////////////////

/* REVISED */
#include <dirent.h>
static int8_t ic(void) { /* Print directory (ls) */
  DIR *DIR_fd;
  struct dirent *DIR_entry;
    
  DIR_fd = opendir(".");
  if (DIR_fd == NULL) {
    perror("-ANASSsh: ic");
    return -1; // Failed
  } 
  else {
    while ((DIR_entry = readdir(DIR_fd)) != NULL) {
      fprintf(stdout, "%s\n", DIR_entry->d_name);
    }   
    closedir(DIR_fd);
    return 0; // Succeeded
  }
}




/* REVISED */
static int cd(char *path) {
  
  path = path ? strtok(path, " \n") : getenv("HOME");
  
  if (chdir(path) == -1) {
    perror("-Ash: cd");
    return -1;
  }
  
  return 0;
}



/* REVISED */
#include <sys/stat.h>
static int cm(const char *const cm_args) {
  char *args = (char *)cm_args;
  char *path = NULL;
  char *mode = NULL;
  char *token;
  int cm_mode, argc = 0;
  
  token = strtok(args, " ");
  while( token != NULL ) {
    if (argc == 0) {
      path = token;
    } else if (argc == 1) {
      mode = token;
    } else {
      break;
    }
    argc++;
    token = strtok(NULL, " ");
  }
  
  if (argc < 2) {
    perror("-Ash: cm, too few arguments given");
    return -1;
  } else if (argc > 2 && token) {
    perror("-Ash: cm, too much arguments given");
    return -1;
  } else {
    
    mode = strsep(&mode, " \n");
    cm_mode = strtol(mode, 0, 8);

    printf("path: '%s'\n", path);
    printf("mode: '%s'\n", mode);
    printf("Mode -> %d\n", cm_mode);
    
    if (cm_mode < 0) {
      perror("-Ash: cm, negative mode");
      return -1;
    }

    if (chmod(path, cm_mode) == -1) {
      perror("-Ash: cm");
      return -1;
    }
  }

  return 0;
}



/* NOT REVISED */
// #include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>
static int co(const char *const co_args) {
  //const char *path, const char *owner) {

  char *args = (char *)co_args;
  char *path;
  char *owner;  
  char *token;
  int argc = 0;
  
  token = strtok(args, " ");
  while( token != NULL ) {
    if (argc == 0) {
      path = token;
    } else if (argc == 1) {
      owner = token;
    } else {
      break;
    }
    argc++;
    token = strtok(NULL, " ");
  }

  printf("%d\n", argc);
  
  if (argc < 2) {
    perror("-Ash: cm, too few arguments given");
    return -1;
  } else if (argc == 2 && token) {
    perror("-Ash: cm, too much arguments given");
    return -1;
  } else {

    owner = strsep(&owner, " \n");

    printf("path: '%s'\n", path);
    printf("owner: '%s'\n", owner);

    
    uid_t uid;
    struct passwd *pwd;
    char *endptr;
  
    uid = strtol(owner, &endptr, 10);
  
    if (*endptr != '\0') {       /* Was not pure numeric string */
      pwd = getpwnam(owner);     /* Try getting UID for username */
      if (pwd == NULL) {
	perror("-Ash: chown, username not found"); // UID for username not found");
	return -1;
      }

      uid = pwd->pw_uid;
    }

    if (chown(path, uid, -1) == -1) {
      perror("-Ash: chown");
      return -1;
    }
  }
  return 0;
}





static void surt() {
}






////////////////////////////////////////



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



/* Main Ash shell */
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
