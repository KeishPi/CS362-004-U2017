#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
/* adapted from testDrawCard.c */

#define DEBUG 0
#define NOISY_TEST 1

int cardEffectFailure = 0;
//int shuffleFailure = 0;
int drawCardFailure = 0;
int deckCountFailure = 0;
int handCountFailure = 0;
int playedCardCountFailure = 0;
int discardFailure = 0;
int numActionsFailure = 0;

int checkVillageCard(int p, struct gameState *post) {
	struct gameState pre;
	//make a copy of gameState into "pre", so we can see what the gameState was before we play AdventurerCard
	memcpy (&pre, post, sizeof(struct gameState));
	
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;  //for cardEffect
	int checkCardEffect;  //assertions for functions used in village
	//int checkShuffle;
	int checkDrawCard, checkDiscard;
	int deckCountBefore, deckCountAfter;  //for checking pre & post
	int handCountBefore, handCountAfter;
	int playedCardCountBefore, playedCardCountAfter;
	int numActionsBefore, numActionsAfter;
	
	//play Village Card on post and check for failure
	checkCardEffect = cardEffect(village, choice1, choice2, choice3, post, handPos, &bonus);
	if(checkCardEffect == -1) {
		cardEffectFailure++;
	}
	
	//implement what we think villageCard should do on pre
	//draw 1 card
	checkDrawCard = drawCard(p, &pre);
		if(checkDrawCard == -1) {  //couldn't draw a card, but there were cards in the deck-FAILURE
			drawCardFailure++;
		}
		/*
		else {  // deck is empty, shuffle discard pile and add to player p deck
			checkShuffle = shuffle(p, &pre);
			if(checkShuffle == -1) {  //couldn't shuffle but there were cards in the deck-FAILURE
				shuffleFailure++;
			}
		}
		*/
	
	//add 2 actions to pre
	pre.numActions = pre.numActions + 2;
	
	//discard Village
	checkDiscard = discardCard(handPos, p, &pre, 0);
	if(checkDiscard != 0) {
		discardFailure++;
	}

	//gameState pre deckCount
	deckCountBefore = pre.deckCount[p];
	//gameState post deckCount
	deckCountAfter = post->deckCount[p];
	//not equal- FAILURE
	if(deckCountBefore != deckCountAfter) {
		deckCountFailure++;
	}
	
	//gameState pre handCount
	handCountBefore = pre.handCount[p];
	//gameState post handCount
	handCountAfter = post->handCount[p];
	//not equal- FAILURE
	if(handCountBefore != handCountAfter) {
		handCountFailure++;
	}
	
	//gameState pre playedCardCount
	playedCardCountBefore = pre.playedCardCount;
	//gameState post playedCardCount
	playedCardCountAfter = post->playedCardCount;
	//not equal- FAILURE
	if((playedCardCountBefore + 1) != playedCardCountAfter) {
		playedCardCountFailure++;
	}

	//gameState pre numActions
	numActionsBefore = pre.numActions;
	//gameState post numActions
	numActionsAfter = post->numActions;
	//not equal- FAILURE
	if((numActionsBefore + 1) != numActionsAfter) {
		numActionsFailure++;
	}

	return 0;
}

int main () {
	int i, n, p;
	int numTests = 10000;
	//int numTrCards, randTrCard;
/*
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
*/
	struct gameState G;
	
	
	printf ("Testing villageCard.\n");
	printf ("RANDOM TESTS.\n");
	
	SelectStream(2);
	PutSeed(3);
	srand(time(NULL));
	//randomly initialize gameState
	for (n = 0; n < numTests; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		//*make certain values "sane" for gameState
		//player number is 0 or 1
		p = floor(Random() * 2);
		//setting deckCount of player p to not be greater than max deck
		G.deckCount[p] = floor(Random() * MAX_DECK);
		//setting discardCount of player p to 0
		//G.discardCount[p] = 0;
		//setting discardCount of player p to not be greater than max deck - 1
		G.discardCount[p] = floor(Random() * MAX_DECK - 1);
		//setting handCount of player p to not be greater than max hand
		G.handCount[p] = floor(Random() * MAX_HAND);
		//setting playedCardCount to max deck -1 (we want to discard Village)
		G.playedCardCount = floor(Random() * MAX_DECK -1);
		//setting numActions not to be > 10
		G.numActions = rand() % 10;
		
		//set the player's turn to p
		G.whoseTurn = p;
		//call oracle
		checkVillageCard(p, &G);
	}
	
	printf("TESTING COMPLETE\n");
	
	if(cardEffectFailure == 0 && drawCardFailure == 0
	   && deckCountFailure == 0 && handCountFailure == 0
	   && playedCardCountFailure == 0 && numActionsFailure == 0) {
		printf ("CONGRATULATIONS! ALL TESTS PASSED\n");
	}
	else {
		printf("FAILURE(S)\n");
		printf("cardEffect(): %d\n", cardEffectFailure);
		//printf("shuffle(): %d\n", shuffleFailure);
		printf("drawCard(): %d\n", drawCardFailure);
		printf("Deck Count Failure: %d\n", deckCountFailure);
		printf("Hand Count Failure: %d\n", handCountFailure);
		printf("Played Card Count Failure: %d\n", playedCardCountFailure);
		printf("Number Actions Count Failure: %d\n", numActionsFailure);
	}
	printf("END OF villageCard TESTNG\n\n");
	
	return 0;
}
