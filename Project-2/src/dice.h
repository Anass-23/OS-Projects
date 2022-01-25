/**
 * Author:    Anass Anhari Talib
 **/

#ifndef _DICE_H_
#define _DICE_H_

typedef char dice_t[6]; /* '\0' included for easy printing (%s) */

void dice_rand_init(void);

char roll_dice(void);

void roll_dices(char *const dice_list, int dices_left);

#endif /* _DICE_H_ */
