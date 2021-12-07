/**
 * Author:    Anass Anhari Talib
 * Created:   3.12.2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "include/built_in.h"

int cm(const char *const cm_args) {
  char *args = (char *)cm_args;
  char *path = NULL;
  char *mode = NULL;
  char *token;
  int cm_mode, argc = 0;
  
  token = strtok(args, " ");
  while( token != NULL ) {
    if (argc == 0) {
      path = token;
    } else if (argc == 1) {
      mode = token;
    } else {
      break;
    }
    argc++;
    token = strtok(NULL, " ");
  }
  
  if (argc < 2) {
    fprintf(stderr, "-Ash: cm: %s\n", "Too few arguments given");
    return -1;
  } else if (argc > 2 && token) {
    fprintf(stderr, "-Ash: cm: %s\n", "Too much arguments given");
    return -1;
  } else {
    
    mode = strsep(&mode, " \n");
    cm_mode = strtol(mode, 0, 8);

    printf("path: '%s'\n", path);
    printf("mode: '%s'\n", mode);
    printf("Mode -> %d\n", cm_mode);
    
    if (cm_mode < 0) {
      perror("-Ash: cm, negative mode");
      return -1;
    }

    if (chmod(path, cm_mode) == -1) {
      perror("-Ash: cm");
      return -1;
    }
  }

  return 0;
}











/* int cm(const char *path, const char *mode) { */

/*   int cm_mode = strtol(mode, 0, 8); */

/*   printf("Mode -> %d\n", cm_mode); */
  
/*   if (cm_mode < 0 || cm_mode == LONG_MIN || cm_mode == LONG_MAX) { */
/*     perror("-Ash: cm mode incorrect"); */
/*     return -1; */
/*   } */
  
/*   /\* if ((cm_mode = strtol(mode, 0, 8)) == 0) { *\/ */
/*   /\*   perror("-Ash: cm"); *\/ */
/*   /\*   return -1; *\/ */
/*   /\* } *\/ */
  
/*   if (chmod(path, cm_mode) == -1) { */
/*     perror("-Ash: cm"); */
/*     return -1; */
/*   } */
/* } */
