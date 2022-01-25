/**
 * Author:    Anass Anhari Talib
 **/

#ifndef _BET_H_
#define _BET_H_

#include <stdbool.h>

typedef struct {
  int amount;
  char value;
  bool dudo;
} bet_t;

bet_t bet(int amount, char value, bool dudo);

bet_t generate_bet(bet_t prev_bet, int dices_left, bool is_palifico, bool AI);

#endif /* _BET_H_ */
