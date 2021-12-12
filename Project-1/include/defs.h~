/**
 * Author:    Anass Anhari Talib
 * Created:   17.09.2021
 **/

#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdbool.h>

#define MAX_PATH        1024
#define MAX_PROC        10
#define MAX_CMD_LEN     10 
#define MAX_ARG_LEN     10 
#define MAX_ARGS	2
#define MAX_LINE        10 // MAX_CMD_LEN + (MAX_ARGS * MAX_ARG_LEN)

typedef struct {
  char cmd[MAX_CMD_LEN];            //*cmd; +1 FOR '/0'
  char argv[MAX_ARGS*MAX_ARG_LEN];
  bool bg;
} cmd_t;

#endif /* _DEFS_H_ */
