#ifndef _PARSER_H_
#define _PARSER_H_

#include "defs.h"

typedef char arg_t[MAX_ARG_LEN]; 
typedef struct {                // ls -la       co <file_path> <username>
  char cmd[MAX_CMD_LEN];      // "ls"         "co"
  arg_t args[MAX_ARGS];       // ["l", "a"]   ["file_path", "username"]
} cmd_t;

void parse(const char *read_in);

#endif /* _PARSER_H_ */
