/**
 * Author:    Anass Anhari Talib
 * Created:   17.09.2021
 **/

#include <stdio.h>
#include <string.h>
#include "include/defs.h"
#include "include/parser.h"

typedef enum {INIT, CMD, ARGS, BG} parse_s_t;
typedef enum {ch, sp, nl, bg} parse_e_t;

static char c_read;
static bool parsing;
static parse_s_t state;
static cmd_type_t cmd_type;
static int cmd_indx, args_indx;

static void init_parsing(void) {
  parsing = true;
  state = INIT;
  cmd_type = none;
  cmd_indx = 0;
  args_indx = 0;
}

static void cmd_append(cmd_t *cmd, char c, int *indx) {
  cmd->cmd[*indx] = c;
  *indx += 1;
}

static void args_append(cmd_t *cmd, char c, int *indx) {
  cmd->args[*indx] = c;
  *indx += 1;
}


static void parse_automata(parse_e_t event, cmd_t *cmd) {
  switch (state) {
  case INIT: {
    cmd_indx = 0;
    args_indx = 0;
    if (event == nl) {
      parsing = false;
      cmd_type = none;
    } else if (event == bg) {
      parsing = false;
      cmd_type = invalid;
    } else if (event == ch) {
      cmd_append(cmd, c_read, &cmd_indx);
      state = CMD;
    }
    break;
  }
  case CMD: {
    if (event == ch) {
      cmd_append(cmd, c_read, &cmd_indx);
    } else if (event == nl) {
      parsing = false;
      cmd_append(cmd, '\0', &cmd_indx);
      cmd_type = valid;
      state = INIT;
    } else if (event == bg) {
      state = BG;
    } else if (event == sp) {
      state = ARGS;
    } 
    break;
  }
  case ARGS: {
    if (event == ch || event == sp) {
      args_append(cmd, c_read, &args_indx);
    } else if (event == nl) {
      parsing = false;
      args_append(cmd, '\0', &args_indx);
      cmd_type = valid;
      state = INIT;
    } else if (event == bg) {
      args_append(cmd, '\0', &args_indx);
      state = BG;
    }
    break;
  }
  case BG: {
    if (event == nl) {
      parsing = false;
      cmd->bg = true;
      cmd_type = valid;
      state = INIT;
    } else if (event == ch || event == bg) {
      parsing = false;
      cmd_type = invalid;
      state = INIT;
    }
    break;
  }
  default:
    state = INIT;
    break;
  }
}

cmd_type_t parse(const char *const read_in, cmd_t *const cmd) {

  int indx = 0;
  init_parsing();
  
  while (parsing) {
    c_read = read_in[indx];
    if (c_read == ' ') {
      parse_automata(sp, cmd);
    } else if (c_read == '\n') {
      parse_automata(nl, cmd);
    } else if (c_read == '&') {
      parse_automata(bg, cmd);
    } else {
      parse_automata(ch, cmd);
    }
    indx++;
  }
  
  return cmd_type;
}
