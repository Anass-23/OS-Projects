/**
 * Author:    Anass Anhari Talib
 * Created:   15.09.2021
 **/

#include <stdio.h>
#include <stdlib.h> // malloc
#include <unistd.h> // getcwd
#include <stdbool.h>
#include "include/defs.h"

#define SHOULD_RUN      1

/* Reading input */
static char read_in[MAX_LINE];
static int nread;  

/* Process list (active) */
typedef struct {
    pid_t pid;
    bool active;
} proc_t;
static proc_t proc_list[MAX_PROC];
// extern proc_t proc_list[MAX_PROC];

/* Main Ash shell */
int main(void) {

	while (SHOULD_RUN){ 
        fprintf(stdout, "%s\n", getenv("PWD")); // Supossing "PWD" is available

        nread = read(fileno(stdin), read_in, MAX_LINE);

        if (nread == -1) {
            perror("-ANASSsh: Error: Some error ocurred");
            break;
        }
        else if (nread == MAX_LINE) {
            perror("-ANASSsh: Error: Exceeded line command");
            break;
        } 
        else {
            read_in[nread] = '\0';
            parse(read_in);
        }
	}
	return 0;
}

