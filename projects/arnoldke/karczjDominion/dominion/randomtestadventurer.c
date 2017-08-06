#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>

/* adapted from testDrawCard.c */

#define DEBUG 0
#define NOISY_TEST 1

int cardEffectFailure = 0;
int shuffleFailure = 0;
int drawCardFailure = 0;
int trCountFailure = 0;
int deckCountFailure = 0;
int handCountFailure = 0;
int discardCountFailure = 0;

int checkAdventurerCard(int p, struct gameState *post) {
	struct gameState pre;
	//make a copy of gameState into "pre", so we can see what the gameState was before we play AdventurerCard
	memcpy (&pre, post, sizeof(struct gameState));
	
	int i;
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;  //for cardEffect
	int trCardsDrawn = 0;
	int checkCardEffect, checkShuffle, checkDrawCard;  //assertions for functions used in adventurer card
	int curCard, card;
	int numDiscards = 0;
	int discardCards[MAX_HAND];
	int treasureBefore, treasureAfter;
	int deckCountBefore, deckCountAfter;
	int handCountBefore, handCountAfter;
	int discardBefore, discardAfter;
	//printf ("HELLO 1.\n");
	
	/*
	printf ("numPlayers: %d\n whoseTurn: %d\n Phase: %d\n", post->numPlayers, post->whoseTurn, post->phase);
	printf ("numActions: %d\n coins: %d\n numBuys: %d\n", post->numActions, post->coins, post->numBuys);
	printf ("hand: %d\n handCount: %d\n Deck: %d\n", post->hand[p][MAX_HAND], post->handCount[p], post->deck[p][MAX_DECK]);
	printf ("deckCount: %d\n discard: %d\n discardCount: %d\n", post->deckCount[p], post->discard[p][MAX_DECK], post->discardCount[p]);
	printf ("playedCards: %d\n playedCardCount: %d\n ", post->playedCards[MAX_DECK], post->playedCardCount);
	*/
	
	//play Adventurer Card on post and check for failure
	checkCardEffect = cardEffect(adventurer, choice1, choice2, choice3, post, handPos, &bonus);
	if(checkCardEffect == -1) {
		cardEffectFailure++;
	}
	//printf ("HELLO 2.\n");
	
	//implement what we think adventurerCard should do on pre
	while(trCardsDrawn < 2) {
		//printf ("HELLO 3.\n");
		//do I need to check if deck is empty, if I intialized it in main? - yes, drawCard could make it empty
		if(pre.deckCount[p] > 0) {
			checkDrawCard = drawCard(p, &pre);
			if(checkDrawCard == -1) {  //couldn't draw a card, but there were cards in the deck-FAILURE
				drawCardFailure++;
			}
		}		
		else {  // deck is empty, shuffle discard pile and add to player p deck
			checkShuffle = shuffle(p, &pre);
			if(checkShuffle == -1) {  //couldn't shuffle but there were cards in the deck-FAILURE
				shuffleFailure++;
			}
		}
		
		//printf ("HELLO 4.\n");
		curCard = pre.hand[p][pre.handCount[p] - 1]; //look at the card just drawn
		if(curCard == gold || curCard == silver || curCard == copper) {  //if treasure card inc count
			trCardsDrawn++;
		}
		else {  //if not treasure card, discardCard for later (after we've drawn 2 treasure cards)
			discardCards[numDiscards] = curCard;
			pre.handCount[p]--;
			numDiscards++;
		}
		//printf ("HELLO 5.\n");
	}
	
	//while(numDiscards > 0) { //if non-treasure cards were drawn add them to the discard pile
	while(numDiscards - 1 >= 0) {
		pre.discard[p][pre.discardCount[p]++] = discardCards[numDiscards-1];
		numDiscards--;
	}
	
	//printf ("HELLO 6.\n");
	
	//The fun part! Check if pre and post match
	//gameState pre treasure count
	for(i = 0; i < pre.handCount[p]; i++) {
		card = pre.hand[p][i];
		if(card == gold || card == silver || card == copper) {  //if treasure card inc count
			treasureBefore++;
		}
	}
	//gameState post treasure count
	for(i = 0; i < post->handCount[p]; i++) {
		card = post->hand[p][i];
		if(card == gold || card == silver || card == copper) {  //if treasure card inc count
			treasureAfter++;
		}
	}
	//not equal- FAILURE
	if(treasureBefore != treasureAfter) {
		trCountFailure++;
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
	
	//gameState pre discardCount
	discardBefore = pre.discardCount[p];
	//gameState post discardCount
	discardAfter = post->discardCount[p];
	//not equal- FAILURE
	if(discardBefore != discardAfter) {
		discardCountFailure++;
	}
	
	return 0;
}

int main () {
	int j, n, p;
	int numTests = 10000;
	//int numTrCards
    int randTrCard;
	int randCard;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};

	struct gameState G;
	
	
	printf ("Testing adventurerCard.\n");
	printf ("RANDOM TESTS.\n");
	
	SelectStream(2);
	PutSeed(3);
	srand(time(NULL));
	
	//randomly initialize gameState
	for (n = 0; n < numTests; n++) {
		//Randomly assigning bytes to gameState caused seg faults 
		/*
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		//make certain values "sane" for gameState
		//player number is 0 or 1
		//p = floor(Random() * 2);
		p = (rand() % 1) + 0;
		//printf("p: %d\n", p);
		//setting deckCount of player p to not be greater than max deck
		//G.deckCount[p] = floor(Random() * MAX_DECK);
		//G.deckCount[p] = floor(Random() * (MAX_DECK - 3)); //((MAX_DECK - 3) + 1) + 3);
		G.deckCount[p] = (rand() % MAX_DECK) + 3;
		//setting num Treasure cards in the deck (min of 3)
		//numTrCards = floor(Random() * (G.deckCount[p] - 3)); //((G.deckCount[p]- 3) + 1) + 3);
		numTrCards = (rand() % G.deckCount[p] - 3) + 3;
		//setting discardCount of player p to 0
		G.discardCount[p] = 0;
		//setting discardCount of player p to not be greater than max deck
		//G.discardCount[p] = floor(Random() * MAX_DECK);
		//setting handCount of player p to not be greater than max hand
		//G.handCount[p] = floor(Random() * MAX_HAND);
		//G.handCount[p] = floor(Random() * ((MAX_HAND - 3) + 1) + 3);
		G.handCount[p] = (rand() % MAX_HAND) + 3;
		//setting playedCardCount to max deck -1 (we want to discard Village)
		//G.playedCardCount = floor(Random() * MAX_DECK -1);
		G.playedCardCount = (rand() % MAX_DECK) + 1;
		G.handCount[p] = 10;
		G.discard[p][MAX_DECK] = 20;
		G.numPlayers = 2;
		*/
		
		initializeGame(2, k, 1111, &G);
		p = (rand() % 1) + 0;
		int deckSize = (rand() % MAX_DECK) + 1;
		int handSize = (rand() % deckSize) + 1;
		
		G.deckCount[p] = deckSize - handSize;
		G.handCount[p] = handSize;
		/*
		//Make sure there's at least 3 Treasure cards in the deck
		for(i = 0; i < numTrCards; i++) {
			randTrCard = rand() % 3;
			if(randTrCard == 1) {
				G.deck[p][i] = gold;
			}
			if(randTrCard == 2) {
				G.deck[p][i] = silver;
			}
			if(randTrCard == 3) {
				G.deck[p][i] = copper;
			}
		}
		 */
		
		for(j = 0; j < G.deckCount[p]; j++) {
			randTrCard = rand() % 51;
			if(randTrCard == 1) {
				G.deck[p][j] = gold;
			}
			if(randTrCard == 2) {
				G.deck[p][j] = silver;
			}
			if(randTrCard == 3) {
				G.deck[p][j] = copper;
			}
			else {
				randCard = rand() % 10;
				G.deck[p][j] = k[randCard];
			}
		}
		
		//set the player's turn to p
		G.whoseTurn = p;
		//call oracle
		checkAdventurerCard(p, &G);
	}
	
	printf("TESTING COMPLETE\n");
	
	if(cardEffectFailure == 0 && shuffleFailure == 0 && drawCardFailure == 0
	   && trCountFailure == 0 && deckCountFailure == 0 && handCountFailure == 0
	   && discardCountFailure == 0) {
		printf ("CONGRATULATIONS! ALL TESTS PASSED\n");
	}
	else {
		printf("FAILURE(S)\n");
		printf("cardEffect(): %d\n", cardEffectFailure);
		printf("shuffle(): %d\n", shuffleFailure);
		printf("drawCard(): %d\n", drawCardFailure);
		printf("Treasure Count Failure: %d\n", trCountFailure);
		printf("Deck Count Failure: %d\n", deckCountFailure);
		printf("Hand Count Failure: %d\n", handCountFailure);
		printf("Discard Count Failure: %d\n", discardCountFailure);
	}
	printf("END OF adventurerCard TESTNG\n\n");
	

	return 0;
}
