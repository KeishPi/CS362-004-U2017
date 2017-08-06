/********************************************************************
 * Filename: unittest3.c
 * Author: Keisha Arnold
 * Description: Unit test for updateCoins() method in dominion.c
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
  int handCount;
  int maxBonus = 10;
  int maxHandCount = 5;
  int numPlayers = 2;
  int randSeed = 1003;
  //int result;
  
  //int choice1 = 0, choice2 = 0, choice3 = 0;
  int bonus;
  int k[10] = {adventurer, embargo, village, council_room, smithy,
    	       feast, gardens, mine, remodel, baron};
  struct gameState state;
  
  int coppersHand[MAX_HAND];
  int silversHand[MAX_HAND];
  int goldsHand[MAX_HAND];
  int noTreasureHand[MAX_HAND];

  for(i = 0; i < MAX_HAND; i++) {
    coppersHand[i] = copper;
    silversHand[i] = silver;
    goldsHand[i] = gold;
    noTreasureHand[i] = estate;
    //if(i % 2 == 0) {
  }      	  
  
  printf("***** Testing updateCoins() *****\n");
  //Test for each player
  for(i = 0; i < numPlayers; i++) {
    for(handCount = 0; handCount < maxHandCount; handCount++) {
      for(bonus = 0; bonus <= maxBonus; bonus++) {
        printf("Test player %d: %d Treasure Cards, %d Bonus\n", i, handCount + 1, bonus);
        memset(&state, 23, sizeof(struct gameState));
	//initialize game
        initializeGame(numPlayers, k, randSeed, &state);
	//set # of cards in hand
	state.handCount[i] = handCount; 

	//all copper hand
	memcpy(state.hand[i], coppersHand, sizeof(int)*handCount);
	//updateCoins
        updateCoins(i, &state, bonus);
	pass = testEq(state.coins, handCount * 1 + bonus);
	if(!pass) {
	  printf("Coins Expected: %d, Coins Actual: %d\n", state.coins, handCount * 1 + bonus);
	}

	//all silver hand
	memcpy(state.hand[i], silversHand, sizeof(int)*handCount);

        updateCoins(i, &state, bonus);
	pass = testEq(state.coins, handCount * 2 + bonus);
	if(!pass) {
	  printf("Coins Expected: %d, Coins Actual: %d\n", state.coins, handCount * 2 + bonus);
	}

	//all gold hand
	memcpy(state.hand[i], goldsHand, sizeof(int)*handCount);

        updateCoins(i, &state, bonus);
	pass = testEq(state.coins, handCount * 3 + bonus);
	if(!pass) {
	  printf("Coins Expected: %d, Coins Actual: %d\n", state.coins, handCount * 3 + bonus);
	}

	//no treasure hand
	memcpy(state.hand[i], noTreasureHand, sizeof(int)*handCount);

        updateCoins(i, &state, 0);
	pass = testEq(state.coins, 0);
	if(!pass) {
	  printf("Coins Expected: %d, Coins Actual: %d\n", state.coins, 0);
	}

      }  
    }
  } 
 
  //Done
  printf("***** updateCoins() Tests Complete *****\n\n");

  return 0;
}

