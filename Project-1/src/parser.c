/**
 * Author:    Anass Anhari Talib
 * Created:   17.09.2021
 **/

#include <stdio.h>
#include "include/defs.h"
#include "include/parser.h"

static cmd_t cmd; // cmd[MAX_LEN], args[MAX...] 

void parse(const char *read_in) {
  char c;
  int args = 0;
  int indx = 0;
  int indx_arg = 0;

  while ((c = read_in[indx]) != ' ') {
    cmd.cmd[indx] = c;
    indx++;
  }
  cmd.cmd[indx] = '\0';   // ic\n -> ic\0 -> cmd = "ic\0" 
  // args=["\0", "\0"]

  if (indx > MAX_CMD_LEN) {
    perror("-Ash: Exceeded command length");
  } 
  else {
    while ((c = read_in[indx_arg]) != '\n') {
      if (c == ' ') {
	args++;
	indx++;
	indx_arg = 0;
      } else {
	cmd.args[args][indx_arg] = c;
	indx++;
	indx_arg++;
      }
    }
  }
}
