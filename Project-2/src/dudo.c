/**
 * Author:    Anass Anhari Talib
 **/

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "dudo.h"

/*
 * DUDO AI
 */
static long int factorial(int number) {
  return (number == 0) ? 1 : (number * factorial(number-1));
}

static double nCr(int n, int r) {
  return factorial(n) / (factorial(n - r) * factorial(r));
}

bool dudo(int prev_bet_amount, int dices_left, bool is_palifico, bool AI) {
  /* 
     Using a simple binomial probability, where we define:
     - n -> Number of trials
     - r -> Number of success we want
     - p -> Probability of success in 'n' trials
     
     So, with the previous bet we can calculate the probability, ex:
     - Exactly 5 threes in 7 dices: 
     -> P(5 3 in 7 dices) = nCr(7, 5) * (1/6)^5 * (5/6)^(7-5)

     But we should also take into account than 5 threes in 7 dices (at
     least 5), ex:
     -> At least 5 threes in 7 dices:
     -> P(X >= 5) = P(X = 5) + P(X = 6) + P(X = 7)
     -> P(X >= 5) = SUM(5..7, P(X))
  */
  
  int n = dices_left;
  int r = prev_bet_amount; /* Ex: 5P -> r = 5 */ 
  double p_succes = 0.0;
  double p_failure = 0.0;
  double p_dudo = 0.0;

  /* Random (not smart)*/
  if (!AI)
    return ((rand() % 3) == 0) ? true : false;  /* P(dudo) = 1/3 */

  /* With "AI" */
  if (r >= n)
    return true;
 
  if (!is_palifico) { /* Pacos also counts (as a Joker) */
    p_succes = 2/6;
    p_failure = 4/6;
  } else {            /* Pacos are not Jokers */
    p_succes = 1/6;
    p_failure = 5/6;
  }
 
  for (int num = r; num <= n; num++) {
    p_dudo += nCr(n, num) * pow(p_succes, num) * pow(p_failure, n-num);
  }
      
  return (int)(p_dudo*100) > 50 ? false : true;
}
