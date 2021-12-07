/**
 * Author:    Anass Anhari Talib
 * Created:   5.12.2021
 **/

#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>

static int co(const char *path, const char *owner) {
  uid_t uid;
  struct passwd *pwd;
  char *endptr;

  uid = strtol(owner, &endptr, 10);
  
  if (*endptr != '\0') {         /* Was not pure numeric string */
    pwd = getpwnam(owner);     /* Try getting UID for username */
    if (pwd == NULL) {
      perror("-Ash: chown, username not found"); // UID for username not found");
      return -1;
    }

    uid = pwd->pw_uid;
  }

  if (chown(path, uid, -1) == -1) {
    perror("-Ash: chown");
    return -1;
  }
  
  return 0;
}
