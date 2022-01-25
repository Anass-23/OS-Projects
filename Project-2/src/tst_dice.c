/**
 * Author:    Anass Anhari Talib
 **/

#include <stdio.h>
#include "dice.h"

void test_dice(void) {
  for (int i = 0; i < 10; i++)
    printf("Rolling Dice... %c\n", roll_dice());
}

void test_dices(int n_dices) {
  int dices_left = n_dices;
  char dices_list[n_dices];

  roll_dices(dices_list, dices_left);
  
  printf("|*****|");
  for (int dice = 0; dice < dices_left; dice++) {
    printf("%c", dices_list[dice]);
  }
  printf("|*****|\n");
}

int main(void) {
  dice_rand_init();
  test_dice();
  
  for (int n_dices = 5; n_dices > 0; n_dices--)
    test_dices(n_dices);
  
  return 0;
}
