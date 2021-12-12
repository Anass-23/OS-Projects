/**
 * Author:    Anass Anhari Talib
 * Created:   15.11.2021
 **/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../include/built_in.h"

int cd(char *path) {
  
  path = path ? strtok(path, " \n") : getenv("HOME");
  
  if (chdir(path) == -1) {
    perror("-Ash: cd");
    return -1;
  }
  
  return 0;
}
