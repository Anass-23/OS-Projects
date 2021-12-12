/**
 * Author:    Anass Anhari Talib
 * Created:   15.11.2021
 **/

#ifndef _BUILT_IN_H_
#define _BUILT_IN_H_

#include <sys/types.h>

/** @brief It prints on stdin fd the contents of the directory. It
 *         returns -1 on error and 0 on success. 
 *  @return int
 */
int ic(void);

/** @brief Changes the directory, with arguments it goes to the path
 *         specified, otherwise, it will go to the user $HOME. It
 *         returns -1 on error and 0 on success. 
 *  @param path[char*]: Arguments string char pointer.
 *  @return int
 */
int cd(char *path);

/** @brief Changes the file permissions to the mode bits. The file and
 *         mode bits are located on cm_args. It returns -1 on error
 *         and 0 on success. 
 *  @param cm_args[char*]: Arguments string char pointer.
 *  @return int
 */
int cm(const char *const cm_args);

/** @brief Changes the file owner to username. The file and
 *         username are located on co_args. It returns -1 on error and
 *         0 on success. 
 *  @param cm_args[char*]: Arguments string char pointer.
 *  @return int
 */
int co(const char *const co_args);

/** @brief Exits the shell, in other words, it only kills all the
 *         background processes (no alive processes are
 *         left)
 * 
 *         NOTE: Afterwards, from main Ash parent process we should
 *         finish the execution!.
 *  @return void
 */
void surt(void);

#endif /* _BUILT_IN_H_ */
