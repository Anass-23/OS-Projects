/**
 * Author:    Anass Anhari Talib
 * Created:   11.12.2021
 **/

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void surt(void) {
  signal(SIGQUIT, SIG_IGN); /* Ignored by the parent process (Ash) */
  kill(0, SIGQUIT);
}
