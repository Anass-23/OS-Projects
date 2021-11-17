/**
 * Author:    Anass Anhari Talib
 * Created:   17.09.2021
 **/

#include <stdio.h>
#include "include/defs.h"
#include "include/parser.h"

static cmd_t cmd;

void parse(const char *read_in) {
    int indx = 0;
    char c;
    while ((c = read_in[indx]) != '\n') {    
        fprintf(stdout, "%c", c);
        indx++;
    }
} 