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
// static proc_t proc_list[MAX_PROC];


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

  char line[MAX_LINE + 1];
  
  while (SHOULD_RUN){ 
    fprintf(stdout, "%s\n", getenv("PWD")); /* Supossing "PWD" is available */
 
    // nread = getline(&read_in, &len, stdin);

    char c_read;
    while (((c_read = fgetc(stdin)) != EOF) && (c_read != '\n')) {
      /* if (c_read == ' ') { */
      /* 	parse_automata(sp); */
      /* } else if (c_read == '\n') { */
      /* 	parse_automata(nl); */
      /* } else if (c_read == '&') { */
      /* 	parse_automata(bg); */
      /* } else { */
      /* 	parse_automata(ch); */
      /* } */
    }

    if (feof(stdin)) {
      printf("%s\n", "eERROR");
      clearerr(stdin);
    } else {
      printf("%s\n", "NO ERROR");
    }

    
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
      // printf("<%s>", read_in);
      
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
      case exceeded: {
	printf("\n%s\n", "> Exceeded");
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












elkfj lksñjvlñ jd
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

static proc_t proc_list[MAX_PROC];


static cmd_t init_cmd(void) {
  cmd_t cmd;
  cmd.cmd[0] = '\0';
  cmd.bg = false;
  return cmd;
}






/* Main Ash shell */
int main(void) {

  // char read_in[MAX_LINE];
  // cmd_t cmd = init_cmd();

  // char read_in[MAX_LINE]; // \n INCLUDED
  char *read_in = NULL;
  
  // char *cmd = NULL;
  // char *args = NULL;

  
  char cmd[MAX_CMD_LEN];
  char args[MAX_ARGS*MAX_ARG_LEN];
  
  size_t len = 0;
  ssize_t nread;
  
  while (SHOULD_RUN){
    fprintf(stdout, "%% %s> ", getenv("PWD")); /* Supossing "PWD" is available */

    /* if (fgets(read_in, MAX_LINE, stdin) == NULL) { */
    /*   perror("-Ash: Error: Exceeded commnad line length"); */
    /* } else { */
    /*   printf("%s", read_in); */
    /* } */
    
    nread = getline(&read_in, &len, stdin);
    
    if (nread > MAX_LINE) {
      perror("-Ash: Error: Exceeded commnad line length");
    } else {
      printf("%s", read_in);
      
      char *token;

      // token = strsep(&read_in, " ");
      strcpy(cmd, strsep(&read_in, " "));
      strcpy(args, read_in);
      // strcpy(args, strstr(read_in, ));

      printf("CMD -> %s\n", cmd);
      // printf("%s\n", read_in);
      printf("ARGS -> %s\n", args);

      /* printf("%s\n", cmd); */

      /* int arg = 0; */
      /* while (token != NULL) { */
      /* 	printf("%s, %d\n", token, strlen(token)); */
      /* 	token = strtok(NULL, " "); */
      /* 	arg++; */
      /* } */



      
    }
    
  }
	
  return 0;
}









/* strcpy(args[0], "Hola1"); */
/* strcpy(args[1], "Hola2"); */

/* printf("%s\n", args[0]); */
/* printf("%s\n", args[1]); */








      proc_t proc;
      pid_t pid;

      /* fork a child process */
      pid = fork();

      proc.pid = pid;
      proc.pid = true;
      
      proc_list[proc_indx] = proc;
      proc_indx++;
	
      if (pid < 0) { 
	/* error occurred */ 
	fprintf(stderr, "Fork Failed"); 
	return 1;
      }
      else if (pid == 0) { /* child process */
	execl("bin/ls", "ls", "./", NULL);
      }
      else { /* parent process */
	wait(NULL);
      }
