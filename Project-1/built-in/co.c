/**
 * Author:    Anass Anhari Talib
 * Created:   5.12.2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include "../include/built_in.h"

int co(const char *const co_args) {
  char *args = (char *)co_args;
  char *path = NULL, *owner, *token;
  int argc = 0;

  uid_t uid;
  struct passwd *pwd;
  char *endptr;
    
  token = strtok(args, " ");
  while( token != NULL ) {
    if (argc == 0) {
      path = token;
    } else if (argc == 1) {
      owner = token;
    } else {
      break;
    }
    argc++;
    token = strtok(NULL, " ");
  }
  
  if (argc < 2) {
    fprintf(stderr, "-Ash: co: %s\n", "Too few arguments given");
    return -1;
  } else if (argc == 2 && token) {
    fprintf(stderr, "-Ash: co: %s\n", "Too much arguments given");
    return -1;
  } else {

    owner = strsep(&owner, " \n");    
    uid = strtol(owner, &endptr, 10);
  
    if (*endptr != '\0') {       /* Was not pure numeric string */
      pwd = getpwnam(owner);     /* Try getting UID for username */
      if (pwd == NULL) {         /* UID for username not found */
	perror("-Ash: co, username not found"); 
	return -1;
      }

      uid = pwd->pw_uid;
    }

    if (chown(path, uid, -1) == -1) {
      perror("-Ash: co");
      return -1;
    }
  }
  return 0;
}
