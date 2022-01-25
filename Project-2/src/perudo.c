/**
 * Author:    Anass Anhari Talib
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include "dice.h"
#include "bet.h"
#include "dudo.h"

#define TEST false

/*
 * Definitions
 */

/* Threads runner function */
void *dealer(void *none);
void *user(void *none);
void *player(void *player_id);

/* Players */
typedef struct {
  int player_id;
  int previous_player, next_player;
  int dices_left;
  char dice_list[5];
  pthread_t player_tid;
  pthread_mutex_t player_mutex;
} player_t;

int n_players;       /* Number of players selected */ 
player_t players[6]; /* User is always (Player 0) */
bool AI;             /* For thread players */

/* Dealer */
pthread_attr_t attr; /* Common also for User and Players threads */
pthread_t dealer_tid;
pthread_mutex_t dealer_start_mutex;
pthread_mutex_t dealer_wait_mutex;

int current_player; /* Current player_id playing */
int player_wrong;
int player_correct;
int previous_player;
int dices_left;
int current_round;

bet_t previous_bet, current_bet;

bool AI = false;
volatile bool player_playing = false;
volatile bool player_end = false;
volatile bool is_palifico = false;
volatile bool end_game = false;



/*
 * Threads creation
 */
void dealer_create(void) {
  /* Initialize and lock the mutex for Dealer thread */
  pthread_mutex_init(&dealer_start_mutex, NULL);
  pthread_mutex_lock(&dealer_start_mutex);
  
  /* Dealer Thread */
  pthread_create(&dealer_tid, &attr, dealer, NULL);
}

void user_create(void) {
  /* Initialize and lock the mutex for User thread */
  pthread_mutex_init(&players[0].player_mutex, NULL);
  pthread_mutex_lock(&players[0].player_mutex);
  
  /* User thread */
  pthread_create(&players[0].player_tid, &attr, user, NULL);
}

void players_create(void) {
  for (int player_id = 1;  player_id < n_players; player_id++) {
    /* Initialize and lock the mutex for Player thread */
    pthread_mutex_init(&players[player_id].player_mutex, NULL);
    pthread_mutex_lock(&players[player_id].player_mutex);
    
    /* Player (player_self_id) thread */
    pthread_create(&players[player_id].player_tid, &attr, player, &player_id);
    sleep(1); /* Just for simplicity (raceconditions reading
		 player_id), we should use also mutex syncing */
  }
  /* 
     (**) All player threads (& user thread) are created.
     So, Dealer will start managing the game play.
  */
  pthread_mutex_unlock(&dealer_start_mutex); /* (**) Sync with Dealer */
}

void threads_create(void) {
  pthread_attr_init(&attr);
  dealer_create();
  user_create();
  players_create();
}



/* 
 * Players operations
 */
void init_players(void) {
  /* Also User (Player 0) */
  for (int player = 0; player < n_players; player++) {
    players[player].dices_left = 5;
    players[player].player_id = player;
    players[player].previous_player = (player - 1 + n_players) % n_players;
    players[player].next_player = (player + 1) % n_players;
  }
}

void roll_players_dices() {
  roll_dices(players[0].dice_list, players[0].dices_left);
  for (int player = 0; player < n_players; player++) {
    roll_dices(players[player].dice_list, players[player].dices_left);
  }
}

void test_players_defs(void) {
  for (int player = 0; player < n_players; player++) {
    printf("\n(Player: %d)\n", player);
    printf("(Player %d) -> (Player %d)\n", players[player].previous_player, players[player].player_id);
    printf("(Player %d) -> (Player %d)\n", players[player].player_id, players[player].next_player);
  }
}

void remove_player(int player_id) {
  /* Example
   () -> A -> B -> C -> ()
   Remove A:
   -> C is prev_player & B is next_player
   - C.next = B
   - B.prev = C
  */
  int prev_player, next_player;
  
  n_players--;

  prev_player = players[player_id].previous_player;
  next_player = players[player_id].next_player;

  players[prev_player].next_player = next_player;
  players[next_player].previous_player = prev_player;

  players[player_id].previous_player = -1;
  players[player_id].next_player = -1;
  

  if (TEST) {
    printf("\nREMOVED (Player %d)\n", player_id);
    test_players_defs();
  }
}



/*
 * Dealer (Manages the display, decides the end of the game)
 */
void print_results(bool hidden) {
  printf("[ |%s|", players[0].dice_list); /* User results shown */
  for (int player = 1; player < n_players; player++) { /* Results of other players hidden */
    for (int dices = 0; dices < players[player].dices_left; dices++) {
      if (hidden) {
	printf("*");
      } else {
	printf("%c", players[player].dice_list[dices]);
      }
    }
    printf("|");
  }
  printf(" ]\n");
}

int count_player(int player, char value) {
  char value_ref;
  int amount = 0;

  for (int dice = 0; dice < players[player].dices_left; dice++) {
    value_ref = players[player].dice_list[dice];
    if ((!is_palifico && value_ref == 'P') || value_ref == value) {
      amount++;
    }
  }
  return amount;
}

void end_player(int player) {
  player_end = true;
  pthread_mutex_unlock(&players[player].player_mutex);
  pthread_join(players[player].player_tid, NULL);
  player_end = false;
}

void end_players(void) {
  /* Also User player */  
  for (int player = 0; player < n_players; player++)
    end_player(player);
}

bool check_dudo() {
  /* 
     Only used for Dealer
     >> Always counting from the current player! <<
  */
  int total_amount = 0;
  int player = current_player;

  for (int i = 0; i < n_players; i++) {
    total_amount += count_player(player, current_bet.value);
    player = players[player].next_player;
  }

  printf("> Bet: {%d, %c} | ", previous_bet.amount, previous_bet.value);
  printf("Count: {%d, %c}\n", total_amount, previous_bet.value);
  
  return total_amount < previous_bet.amount ? true : false;
}

void *dealer(void *none) {
  /* Waits to Sync while creating the players threads */
  pthread_mutex_lock(&dealer_start_mutex);
  
  /* Init the players definitions "players linked list" */
  init_players();
  
  if (TEST)
    test_players_defs();

  /* Starting game, Dealer starts managing */
  current_round = 0;
  current_player = rand() % n_players;
  
  is_palifico = false;
  dices_left = n_players * 5;
  
  previous_bet = bet(0, '0', false);
  current_bet = bet(0, '0', false);

  printf("\n*** Round (%d) ***\n", current_round);
  printf("> Starts (Player %d)\n", current_player);

  roll_players_dices();
  
  while (1) {
    /* Rolls the dices and shows the results */
    print_results(true);

    /* Gives turn to the current player */
    if (current_player == 0) 
      printf("> Enter 1 for Bet, 2 for Dudo or 3 for Ending Game): ");
    
    player_playing = true;
    pthread_mutex_unlock(&players[current_player].player_mutex);

    /* Waits until player finishes */
    while(player_playing);
    pthread_mutex_lock(&players[current_player].player_mutex);

    sleep(5);

    /* Analysis of the players answers */
    if (end_game) {
      end_players();
      printf("\n> Game ended\n");
      break;
    }

    if (!current_bet.dudo) { /* Plays next player */
      printf("- Player %d: Announces %d %c\n\n", current_player, current_bet.amount, current_bet.value);
      previous_bet = current_bet;
      current_player = players[current_player].next_player;
    }
    else { /* Current player called DUDO! */
      bool is_dudo;
      
      printf("- Player %d: Announces DUDO!\n\n", current_player);
      print_results(false);
      is_dudo = check_dudo();
      
      player_wrong = is_dudo ? players[current_player].previous_player : current_player;
      player_correct = !is_dudo ? players[current_player].previous_player : current_player;
      players[player_wrong].dices_left--;

      if (is_dudo)
	printf("- Player %d was right!\n", current_player);
      else
	printf("- Player %d wasn't right!\n", current_player);
      
      
      if (players[player_wrong].dices_left == 0) { /* Player lost, remove it */
	if (player_wrong == 0 || n_players == 2) {
	  /* User player lost -> end game */
	  end_game = true;
	  end_players();
	  if (n_players == 2) {
	    printf("- Player %d won!\n", player_correct);
	  } else {
	    printf("\n> Game ended\n");
	  }
	  break;
	}
	else { /* More players left */
	  remove_player(player_wrong);
	  current_round++;
	  current_player = player_correct;

	  is_palifico = false;
	  
	  previous_bet = bet(0, '0', false);
	  current_bet = bet(0, '0', false);

	  printf("\n*** Round (%d) ***\n", current_round);
	  printf("> Starts (Player %d)\n", current_player);
	  roll_players_dices();
	}
      }
      else { /* Player wrong didn't died */
	current_round++;
	current_player = player_wrong;
  
	is_palifico = players[player_wrong].dices_left == 1;
	  
	previous_bet = bet(0, '0', false);
	current_bet = bet(0, '0', false);

	printf("\n*** Round (%d) ***\n", current_round);
	printf("> Starts (Player %d)\n", current_player);
	roll_players_dices();
      }
    }
      
  }

  pthread_exit(0);
}



/*
 * User
 */
void *user(void *none) { /* User is always (Player 0) */

  if (TEST)
    printf("> Created (Player %d)\n", 0);

  while (1) {
    /* Player thread waiting for it's turn */
    pthread_mutex_lock(&players[0].player_mutex);

    if (end_game)
      break;

    char *option = NULL, *amount = NULL;
    char value;
    size_t len = 0;
    ssize_t nread;
    
    while (1) { /* No checking */
      nread = getline(&option, &len, stdin);
      if (option[0] == '1') {
	printf("> Enter your amount: ");
	nread = getline(&amount, &len, stdin);
	
	printf("> Enter your value: ");
	value = getc(stdin);

	current_bet.amount = atoi(amount);
	current_bet.value = value;
	current_bet.dudo = false;
	
	break;
      } else if (option[0] == '2') {
	current_bet.dudo = true;
	break;
      } else if (option[0] == '3') {
	end_game = true;
	break;
      }
    }
    
    player_playing = false;
    pthread_mutex_unlock(&players[0].player_mutex);
   
    sleep(2);
  }
  
  pthread_exit(0);
}



/* 
 * Player (Each computer player)
 */
void *player(void *player_id) { 
  /* We get the 'player_id' id of the player  */
  int self = *(int*)player_id;

  if (TEST)
    printf("> Created (Player %d)\n", self);

  while (1) {
    /* Player thread waiting for it's turn */
    pthread_mutex_lock(&players[self].player_mutex);

    if (player_end) {
      player_end = false;
      if (TEST)
	printf("(Player %d) lost! :(\n", self);
      break;
    }

    if (end_game)
      break;
 
    /* Plays */
    current_bet = generate_bet(previous_bet, dices_left, is_palifico, AI);

    /* Finishes playing */
    player_playing = false;
    pthread_mutex_unlock(&players[self].player_mutex);
   
    sleep(2);
  }
  
  pthread_exit(0);
}



/*
 * Main
 */
int main(void) {
  char *option = NULL, players_read;
  size_t len = 0;
  ssize_t nread;
  bool new_game = false;
  
  printf("*******************\n");
  printf("    PERUDO GAME    \n");
  printf("*******************\n");

  while (1) {
    
    if (end_game)
      break;
  
    while (1) {
      printf("\n* Choose one option:\n");
      printf("\t[1] New Game\n");
      printf("\t[2] End Game\n$ ");

      nread = getline(&option, &len, stdin);
      if (option[0] == '1') {
	/* New Game selected */
	printf("\n* Choose a level:\n");
	printf("\t[1] Easy Mode\n");
	printf("\t[2] Hard Mode\n$ ");

	nread = getline(&option, &len, stdin);
	
	if (option[0] == '1' || option[0] == '2') {
	  AI = (option[0] == '2');
	  printf("\n* How many players [2-6]: ");
	  players_read = getc(stdin);
    
	  if (players_read < '2' || players_read > '6') {
	    printf("> Cannot start a new game, select between [2-6] players\n");
	  } else {
	    printf("> Starting new game...\n");
	    n_players = players_read - '0'; /* Number of players saved */
	    new_game = true;                /* New game selected */
	    break;
	  }
	} else {
	  printf("> Option not found\n");
	}   
      }
      else if (option[0] == '2'){
	/* End game */
	end_game = true;
	new_game = false;
	printf("> See you soon! :)\n"); 
	break;
      }
      else {
	printf("> Option not found\n");
      }
    }

    if (new_game) { /* New game selected */
      dice_rand_init(); /* Seed for pseudo-random starting sequence */
      threads_create();  /* Initialize all threads (Dealer, User &
			    Players threads) */
      pthread_join(dealer_tid, NULL);
      end_game = false;
    }
  }
  return 0;
}
