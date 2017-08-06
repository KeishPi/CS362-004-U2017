/********************************************************************
 * Filename: unittest4.c
 * Author: Keisha Arnold
 * Description: Unit test for supplyCount() method in dominion.c
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
  int randSeed = 3005;
  //int result;
  //int choice1 = 0, choice2 = 0, choice3 = 0;
  //int handPos = 0, bonus = 0;
  int k[10] = {adventurer, embargo, village, council_room, smithy,
    	       feast, gardens, mine, remodel, baron};
	  
  struct gameState state, stateTest;
  
  printf("***** Testing supplyCount() *****\n");
  printf("testing default supply counts...\n");  
  for(i = 0; i < treasure_map+1; i++) {
    printf("Test supplyCount[%d]\n", i);
    memset(&state, 23, sizeof(struct gameState));
    memset(&stateTest, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, randSeed, &state); 
    memcpy(&stateTest, &state, sizeof(struct gameState));
    //state.supplyCount = i;

    //call supplyCount()
    supplyCount(i, &stateTest);

    pass = testEq(state.supplyCount[i], stateTest.supplyCount[i]);
    if(!pass) {
      printf("Supply Count Incorrect. Expected: %d Actual: %d\n", state.supplyCount[i], stateTest.supplyCount[i]);
    }
  }
 
  printf("testing supply counts = 0...\n");
  for(i = 0; i < treasure_map+1; i++) {
    printf("Test supplyCount[%d]\n", i);
    //set supplyCount to 0
    stateTest.supplyCount[i] = 0;
    //call supplyTurn()
    supplyCount(i, &stateTest);

    pass = testEq(stateTest.supplyCount[i], 0);
    if(!pass) {
      printf("Supply Count Incorrect. Expected: %d Actual: %d\n", 0, stateTest.supplyCount[i]);
    }
  }
  
 
  //Done
  printf("***** supplyCount() Tests Complete *****\n\n");

  return 0;
}

