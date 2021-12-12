#ifndef _BUILT_IN_H_
#define _BUILT_IN_H_

#include <sys/types.h>

int ic(void);
int cd(char *path);
int cm(const char *const cm_args);
int co(const char *const co_args);
void surt(void);
// void surt(pid_t proc_list[], int prc_indx);

#endif /* _BUILT_IN_H_ */
