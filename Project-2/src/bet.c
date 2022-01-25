/**
 * Author:    Anass Anhari Talib
 **/

#include <stdlib.h>
#include <stdbool.h>
#include "dice.h"
#include "dudo.h"
#include "bet.h"

bet_t bet(int amount, char value, bool dudo) {
  bet_t new_bet;
  new_bet.amount = amount;
  new_bet.value = value;
  new_bet.dudo = dudo;
  return new_bet;
}

bet_t generate_bet(bet_t previous_bet, int dices_left, bool is_palifico, bool AI) {
  bet_t new_bet;
  int outbid = rand() % 3;

  if (previous_bet.amount == 0) { /* Starting */
    new_bet.dudo = false;
    new_bet.amount = (rand() % dices_left)/2 + 1;
    if (is_palifico) {
      new_bet.value = roll_dice();
    } else {
      while((new_bet.value = roll_dice()) == 'P');
    }
  }
  else {
    if (dudo(previous_bet.amount, dices_left, is_palifico, AI)) {
      new_bet.dudo = true;
    }
    else if (previous_bet.value == 'P') { /* From Paco bet to a normal bet */
      new_bet.amount = previous_bet.amount * 2 + 1;
      while((new_bet.value = roll_dice()) == 'P');
    }
    else {
      if (outbid == 0) { /* One more dice */
	new_bet.amount = previous_bet.amount + 1;
	new_bet.value = previous_bet.value;
      }
      else if (outbid == 1) { /* Higher value */
	new_bet.amount = previous_bet.amount;
	while(1) {
	  new_bet.value = roll_dice();
	  if (new_bet.value > previous_bet.value && new_bet.value != 'P')
	    break;
	}     
      }
      else { /* Number of Pacos */
	new_bet.amount = previous_bet.amount/2 + (rand()%2 + 1);
	new_bet.value = 'P';
      } 
    }
  }
  return new_bet;
}

/* bool check_bet(bet_t previous_bet, bet_t current_bet, bool is_palifico) { */
/*   if (previous_bet.amount == 0) { /\* Starting *\/ */
/*     return (!is_palifico && current_bet.value == 'P') ? false : true; */
/*   } */
/*   else if (previous_bet.value == 'P') { /\* From Paco bet to a normal bet *\/ */
/*     if (current_bet.amount != previous_bet.value * 2 + 1) { */
/*       return false; */
/*     } else { */
/*       return (current_bet.value == 'P') ? false : true; */
/*     } */
/*   } */
/*   else if (previous_bet.amount >= ) { */
    
/*   }{ */
    
/*   } */
/* } */
