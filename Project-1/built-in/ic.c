/**
 * Author:    Anass Anhari Talib
 * Created:   15.11.2021
 **/

#include <stdio.h>
#include <dirent.h>
#include "../include/built_in.h"

int ic(void) {
  DIR *DIR_fd;
  struct dirent *DIR_entry;
    
  DIR_fd = opendir(".");
  if (DIR_fd == NULL) {
    perror("-ANASSsh: ic");
    return -1;
  } 
  else {
    while ((DIR_entry = readdir(DIR_fd)) != NULL) {
      fprintf(stdout, "%s\n", DIR_entry->d_name);
    }   
    closedir(DIR_fd);
  }
  return 0;
}
