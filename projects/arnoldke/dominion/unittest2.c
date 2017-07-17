/********************************************************************
 * Filename: unittest2.c
 * Author: Keisha Arnold
 * Description: Unit test for isGameOver() method in dominion.c
 * Basic Requirements of isGameOver():
 * 1) If Province card stack is empty- game over
 * 2) If three Supply card stacks are empty- game over
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testEq(int value1, int value2) {
  if (value1 == value2) {
    printf("Test PASSED\n");
    return 1;
  }
  else {
    printf("Test FAILED\n");
    return 0;
  }
}   

int main() {
  int pass;
  //int i = 0;
  int numPlayers = 2;
  int randSeed = 785;
  int result;
  //int choice1 = 0, choice2 = 0, choice3 = 0;
  //int handPos = 0, bonus = 0;
  int randCard1, randCard2, randCard3;
  time_t t;
  int diff = 0;
  int k[10] = {adventurer, embargo, village, council_room, smithy,
    	       feast, gardens, mine, remodel, baron};
	  
  struct gameState state;
  
  srand((unsigned) time(&t));

  printf("***** Testing isGameOver() *****\n");

  //initilize game
  memset(&state, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, randSeed, &state);

  //supply cards are full
  printf("test if game over when none of the supply is empty...\n");
  result = isGameOver(&state);
  pass = testEq(result, 0);
  if(!pass) {
    printf("Game ended when none of the supply was empty\n");
  }

  printf("test if game over when Province card stack is empty...\n"); 
  state.supplyCount[province] = 0;
  result = isGameOver(&state);
  pass = testEq(result, 1);
  if(!pass) {
    printf("Game did not end when Province card stack was empty\n");
  }

  //reset province stack
  state.supplyCount[province] = 10;

  printf("test if game over when 1 supply card stack is empty...\n");
  //for(i = 0; i < 3; i++) {
  randCard1 = rand() % 25;
  state.supplyCount[randCard1] = 0;
  result = isGameOver(&state);
  pass = testEq(result, 0);
  if(!pass) {
    printf("Game ended when only one supply stack was empty\n");
  }
    
  printf("test if game over when 2 supply card stacks are empty...\n");
  //for(i = 0; i < 3; i++) {
  randCard2 = rand() % 25;
  while(diff == 0) {
    if(state.supplyCount[randCard1] == state.supplyCount[randCard2]) {
      randCard2 = rand() %25;
    }
    else {
      diff = 1;
    }
  }
  state.supplyCount[randCard2] = 0;
  result = isGameOver(&state);
  pass = testEq(result, 0);
  if(!pass) {
    printf("Game ended when only two supply stacks were empty\n");
  }

  printf("test if game over when 3 supply card stacks are empty...\n");
  //for(i = 0; i < 3; i++) {
  randCard3 = rand() % 25;
  diff = 0;
  while(diff == 0) {
    if(state.supplyCount[randCard1] == state.supplyCount[randCard3] || 
       state.supplyCount[randCard2] == state.supplyCount[randCard3]) {
    randCard3 = rand() %25;
    }
    else {
      diff = 1;
    }
  }
  state.supplyCount[randCard3] = 0;
  result = isGameOver(&state);
  pass = testEq(result, 1);
  if(!pass) {
    printf("Game did not end when three supply stacks were empty\n");
  }

  //Done
  printf("***** isGameOver() Tests Complete *****\n\n");

  return 0;
}

