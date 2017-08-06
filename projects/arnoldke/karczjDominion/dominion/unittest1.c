/********************************************************************
 * Filename: unittest1.c
 * Author: Keisha Arnold
 * Description: Unit test for whoseTurn() method in dominion.c
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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
  int i = 0;
  int numPlayers = 2;
  int randSeed = 104;
  int result;
  //int choice1 = 0, choice2 = 0, choice3 = 0;
  //int handPos = 0, bonus = 0;
  int k[10] = {adventurer, embargo, village, council_room, smithy,
    	       feast, gardens, mine, remodel, baron};
	  
  struct gameState state;
  
  printf("***** Testing whoseTurn() *****\n");

  for(i = 0; i < numPlayers; i++) {
    printf("Test player %d\n", i);
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, randSeed, &state); 

    //set whose turn
    state.whoseTurn = i;

    //call whoseTurn()
    result = whoseTurn(&state);

    //result of call to whoseTurn() and i should match
    pass = testEq(result, i);
    if(!pass) {
      printf("Player Turn Incorrect. Expected: %d Actual: %d\n", i, result);
    }
  }
 
  //Done
  printf("***** whoseTurn() Tests Complete *****\n\n");

  return 0;
}

