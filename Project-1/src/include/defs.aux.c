/**
 * Author:    Anass Anhari Talib
 * Created:   17.09.2021
 **/

#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdbool.h>

#define MAX_PROC        10              /* Max nº of background processes */
// #define MAX_LINE	10              /* 80 chars per line, per command */
#define MAX_CMD_LEN     80 // MAX_LINE -  2   /* Max command length % ~/path/a.out   &  \n */
#define MAX_ARG_LEN     80 // MAX_LINE / 2    /* Max command length */
#define MAX_ARGS	2  /* 80 chars per line, per command */


typedef char arg_t[MAX_ARG_LEN];
typedef struct {
  // arg_t args[MAX_ARGS]; // cmd[MAX_LINE];
  char cmd[MAX_CMD_LEN + 1]; //*cmd; +1 FOR '/0'
  // arg_t args[MAX_ARGS];
  char args[MAX_ARG_LEN + 1];
  bool bg;
} cmd_t;

/* 0        9 */
/* ---------- */
/* mkdirlklkl */

typedef enum {
	      valid,   /* Valid "syntax" */
	      invalid, /* Invalid "syntax" */
	      exceeded, /* Exeeded cmd or arg length */
	      none     /* Nonde, empty*/
} cmd_type_t;


#endif /* _DEFS_H_ */
