/**
 * Author:    Anass Anhari Talib
 * Created:   3.12.2021
 **/

#include <sys/stat.h>

int cm(const char *path, const char *mode) {

  int cm_mode = strtol(mode, 0, 8);

  printf("Mode -> %d\n", cm_mode);
  
  if (cm_mode < 0 || cm_mode == LONG_MIN || cm_mode == LONG_MAX) {
    perror("-Ash: cm mode incorrect");
    return -1;
  }
  
  /* if ((cm_mode = strtol(mode, 0, 8)) == 0) { */
  /*   perror("-Ash: cm"); */
  /*   return -1; */
  /* } */
  
  if (chmod(path, cm_mode) == -1) {
    perror("-Ash: cm");
    return -1;
  }
}
