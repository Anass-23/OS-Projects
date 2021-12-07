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





static int cd(char *path) {
  if (strlen(path) == 0) { // to home directory
    if (chdir(getenv("HOME")) == -1) {
      perror("-Ash: cd");
      return -1; // Failed
    }
  } else {
    if (chdir(path) == -1) {
      perror("-Ash: cd");
      return -1; // Failed
    }
  }
  return 0; // Succeeded
}




#include <sys/stat.h>
static int cm(const char *path, const char *mode) {

  int cm_mode = strtol(mode, 0, 8);

  printf("Mode -> %d\n", cm_mode);
  
  if (cm_mode < 0 || cm_mode == LONG_MIN || cm_mode == LONG_MAX) {
    perror("-Ash: cm mode incorrect");
    return -1;
  }
  
  /* if ((cm_mode = strtol(mode, 0, 8)) == 0) { */
  /*   perror("-Ash: cm"); */
  /*   return -1; */
  /* } */
  
  if (chmod(path, cm_mode) == -1) {
    perror("-Ash: cm");
    return -1;
  }
}





// #include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>
static int co(const char *path, const char *owner) {
  uid_t uid;
  struct passwd *pwd;
  char *endptr;

  uid = strtol(owner, &endptr, 10);
  
  if (*endptr != '\0') {         /* Was not pure numeric string */
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
  
  return 0;
}





static void surt() {
}


////////////////////////////////////////



/* Process list */
typedef struct {
  pid_t pid;
  bool active;
} proc_t;

static proc_t proc_list[MAX_PROC];


static cmd_t init_cmd(void) {
  cmd_t cmd;
  cmd.cmd[0] = '\0';
  cmd.bg = false;
  return cmd;
}


static void display_prompt(void) {
  char cwd[MAX_PATH];
  if (getcwd(cwd, MAX_PATH) == NULL) {
    fprintf(stdout, "%% %s> ", getenv("PWD")); /* Supossing "PWD" is available */
  } else {
    fprintf(stdout, "%% %s> ", cwd); 
  }
}



/* Main Ash shell */
int main(void) {

  char *read_in = NULL;
  
  // char cmd[MAX_CMD_LEN];
  cmd_t cmd = init_cmd();
  char args[MAX_ARGS][MAX_CMD_LEN];

  
  size_t len = 0;
  ssize_t nread;
    


  while (SHOULD_RUN) {
    
    display_prompt();
    
    nread = getline(&read_in, &len, stdin);
    if (nread > MAX_LINE) {
      perror("-Ash: Error: Exceeded commnad line length");
    } else {
      read_in[nread] = '\0';
      printf("%s", read_in);


      /*
       * ic & cd
       */
      // ic();
      // cd(getenv("HOME"));
      // ic();

      /*
       * cm
       */
      //cm("tst/file2", "0700");
      
      /*
       * co
       */
      co("tst/fileJH8", "anassanhari");
      co("tst/file2", "anassanhari");
      co("tst/file2", "casa");
      
      /*
       * surt
       */
      // surt();
      
      //parse(read_in, &cmd);
    }
  }
	
  return 0;
}
