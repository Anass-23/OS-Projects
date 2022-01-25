/**
 * Author:    Anass Anhari Talib
 **/

#include <stdlib.h>
#include <time.h>
#include "dice.h"

static dice_t dice = {'1', '2', '3', '4', '5', 'P'};

void dice_rand_init(void) {
  srand(time(NULL));
}

char roll_dice(void) {
  return dice[rand() % 6];
}

void roll_dices(char *const dices_list, int dices_left) {
  int n_dice;
  for (n_dice = 0; n_dice < dices_left; n_dice++) {
    dices_list[n_dice] = roll_dice();
  }
  dices_list[n_dice] = '\0';
}
