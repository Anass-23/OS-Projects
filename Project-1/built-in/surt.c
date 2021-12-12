#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void surt(void) {
  signal(SIGQUIT, SIG_IGN);
  kill(0, SIGQUIT);
}
