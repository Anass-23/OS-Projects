/**
 * Author:    Anass Anhari Talib
 * Created:   17.09.2021
 **/

#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdbool.h>

#define MAX_LINE        10 // MAX_CMD_LEN + (MAX_ARGS * MAX_ARG_LEN)
#define MAX_CMD_LEN     10 
#define MAX_ARG_LEN     10

#define MAX_PATH        1024
#define MAX_PROC        3
#define MAX_ARGS	40

/* typedef struct { */
/*   char cmd[MAX_CMD_LEN];            //\*cmd; +1 FOR '/0' */
/*   char argv[MAX_ARGS*MAX_ARG_LEN]; */
/*   bool bg; */
/* } cmd_t; */


/* typedef char* arg_t; */

#endif /* _DEFS_H_ */


/* argv[argc] = NULL; */
/* arg_t argv[MAX_ARGS]; */

/* char *token = NULL; */
	  
/* token = strtok(args, " "); */
/* int argc = 0; */
/* while (token != NULL) { */
/*   argv[argc] = token; */
/*   argc++; */
/*   token = strtok(NULL, " "); */
/* } */


/* for (int i = 0; i < argc; i++) { */
/*   printf("%s\n", strchr(argv[i], '&')); */
/* } */

	  
	  
/* if ((cmd_path = find_cmd(cmd, cwd)) == NULL) { */
/*   fprintf(stderr, "-Ash: %s: command not found\n", cmd); */
/* } else { */
/*   printf("%s\n", find_cmd(cmd, cwd)); */
	    
/*   pid_t pid; */
	  
/*   /\* fork a child process *\/ */
/*   pid = fork(); */
/*   if (pid < 0) { */
/*     /\* error occurred *\/ */
/*     fprintf(stderr, "-Ash: %s: something went wrong\n", cmd); */
/*     // return 1; */
/*   } */
/*   else if (pid == 0) { /\* child process *\/ */
/*     /\* if (argc == 0) { *\/ */
/*     /\* 	args = {NULL}; *\/ */
/*     /\* } *\/ */
/*     execv(cmd_path, &args); */
/*     perror("-Ash: something went wrong"); */
/*     exit(EXIT_FAILURE); */
/*   } */
/*   else { /\* parent process *\/ */
/*     wait(NULL); */
/*   } */
/* } */
