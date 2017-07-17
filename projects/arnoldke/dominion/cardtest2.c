/*************************************************************
 * Filename: cardtest2.c
 * Author: Keisha Arnold
 * Description: Unit test for adventurerCard() in dominion.c
 *************************************************************/

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
  int randSeed = 501;
//  int cardsDrawn = 2;  //how do we know how many total cards were drawn???
  int cardsGained = 2;
  int cardsDiscarded = 1;
  int choice1 = 0, choice2 = 0, choice3 = 0;
  int handPos = 0, bonus = 0;
  int testTrCard;
  int numTreasureTest = 0;
  int numTreasure = 0;
  int k[10] = {adventurer, embargo, village, council_room, smithy,
    	       feast, gardens, mine, remodel, baron};
	  
  struct gameState state, stateTest;

  //initialize Game
  initializeGame(numPlayers, k, randSeed, &state); 

  printf("***** Testing adventurerCard()... *****\n");

  //Test if handcount gets +2
  printf("Testing Player 0 Adventurer +2 hand count...\n");
  memcpy(&stateTest, &state, sizeof(struct gameState));
  cardEffect(adventurer, choice1, choice2, choice3, &stateTest, handPos, &bonus);
  pass = testEq(stateTest.handCount[0], state.handCount[0] + cardsGained - cardsDiscarded); 
  if (!pass) {
    printf("Player hand count incorrect. Expected: %d Actual: %d\n", state.handCount[0] + cardsGained - cardsDiscarded, stateTest.handCount[0]); 
  }

  //KEEP for now, but deck count -2 not always true? need to figure out how many cards player drew, then discarded.
/*
  //Test players deckcount gets -2
  printf("Testing Player 0 deck count -2...\n");
  pass = testEq(stateTest.deckCount[0], state.deckCount[0] - cardsDrawn);
  if(!pass) {
    printf("Player deck count incorrect. Expected: %d Actual: %d\n", state.deckCount[0] - cardsDrawn, stateTest.deckCount[0]);
  }
*/
/*
  //Test if there are two additional treasure cards
  //Will always be on the top?
  printf("Testing if two cards added to hand are treasure cards...\n");
  //for(i = 0; i < stateTest.handCount[0]; i++) {
  testTrCard = stateTest.hand[0][stateTest.handCount[0]-1];
  if(testTrCard != gold || testTrCard != silver || testTrCard != copper) {
    printf("Test FAILED\n");
    printf("Card not a Treasure Card\n");
  }
  testTrCard = stateTest.hand[0][stateTest.handCount[0]-2];
  if(testTrCard != gold || testTrCard != silver || testTrCard != copper) {
    printf("Test FAILED\n");
    printf("Card not a Treasure Card\n");
  }
  else {
    printf("Test PASSED\n");
  }
*/
  
  //Test if the hand contains 2 additional treasure cards
  printf("Test if player has 2 additional treasure cards...");
  for(i = 0; i < stateTest.handCount[0]; i++) {
    testTrCard = stateTest.hand[0][i];
    if(testTrCard == gold || testTrCard == silver || testTrCard == copper) {
      numTreasureTest++;
    }
  }

  for(i = 0; i < state.handCount[0]; i++) {
    testTrCard = state.hand[0][i];
    if(testTrCard == gold || testTrCard == silver || testTrCard == copper) {
      numTreasure++;
    }
  }
 
  pass = testEq(numTreasure + 2, numTreasureTest);
  if(!pass) {
    printf("Player does not have 2 additional Treasure Cards. Expected %d Actual %d\n", numTreasure + 2, numTreasureTest);
  }  

  //Test if score remains unchanged
  printf("Testing Player 0 score unchanged...\n");
  pass = testEq(scoreFor(0, &stateTest), scoreFor(0, &state));
  if(!pass) {
    printf("Player Score incorrect. Expected: %d Actual: %d\n", scoreFor(0, &state), scoreFor(0, &stateTest));
  }

  //Test opposing Player state remains unchanged
  printf("Testing Player 1 score unchanged...\n");
  pass = testEq(scoreFor(1, &stateTest), scoreFor(1, &state));
  if(!pass) {
    printf("Opposing player score changed. Expected: %d Actual: %d\n", scoreFor(1, &state), scoreFor(1, &stateTest));
  }

  printf("Testing Player 1 hand count unchanged...\n");
  pass = testEq(stateTest.handCount[1], state.handCount[1]);
  if(!pass) {
    printf("Opposing player hand count changed. Expected: %d Actual: %d\n", state.handCount[1], stateTest.handCount[1]);
  }
        
  printf("Testing Player 1 deck count unchanged...\n");
  pass = testEq(stateTest.deckCount[1], state.deckCount[1]);
  if(!pass) {
    printf("Opposing player deck count changed. Expected: %d Actual: %d\n", state.deckCount[1], stateTest.deckCount[1]);
  }

  //Vicory Card piles unchanged
  printf("Testing Victory Card Piles unchanged...\n");
  printf("Estate Card Pile...\n");
  pass = testEq(stateTest.supplyCount[estate], state.supplyCount[estate]);
  if(!pass) {
    printf("Estate Card Pile Changed. Expected: %d Actual: %d\n", state.supplyCount[estate], stateTest.supplyCount[estate]);
  }

  printf("Province Card Pile...\n");
  pass = testEq(stateTest.supplyCount[province], state.supplyCount[province]);
  if(!pass) {
    printf("Province Card Pile Changed. Expected: %d Actual: %d\n", state.supplyCount[province], stateTest.supplyCount[province]);
  }

  printf("Duchy Card Pile...\n");
  pass = testEq(stateTest.supplyCount[duchy], state.supplyCount[duchy]);
  if(!pass) {
    printf("Duchy Card Pile Changed. Expected: %d Actual: %d\n", state.supplyCount[duchy], stateTest.supplyCount[duchy]);
  }
  
  //Kingdom Card piles unchanged
  printf("Testing Kingdom Card Piles unchanged...\n");
  for(i = 0; i < 10; i++) {
    pass = testEq(stateTest.supplyCount[k[i]], state.supplyCount[k[i]]);
    if(!pass) {
      printf("Kingdom Card Pile %d Changed.\n", i);
    }
  }

  //Done
  printf("***** adventurerCard() Tests Complete *****\n\n");

  return 0;
}

