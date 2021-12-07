/**
 * Author:    Anass Anhari Talib
 * Created:   15.11.2021
 **/

#include <stdio.h>
#include <string.h>

int cd(char *path) {
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
