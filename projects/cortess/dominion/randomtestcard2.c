#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define TESTFUNCTION "Village"

void testEqual(int val, int expected, char* message){
	if(val != expected){
		printf("%s\n", message);
	}
}

void checkCard(struct gameState *G, int currentPlayer){
	struct gameState pre;
	int choice1 = -1;
	int choice2 = -1;
	int choice3 = -1;
	int handPos = 0;
	int card = village;
	int expected;

	memcpy(&pre, G, sizeof(struct gameState));

	G->hand[currentPlayer][handPos] = card;

	if(playCard(handPos, choice1, choice2, choice3, G) < 0){
		printf("TEST FAILED. playCard crash.\n");
	}

	// check that current player has drawn 1 card
	expected = pre.handCount[currentPlayer];
	testEqual(G->handCount[currentPlayer], expected, "TEST FAILED: Player did not draw 1 card.");

	// check that cards drawn came from current player's deck
	expected = pre.deckCount[currentPlayer] - 1;
	testEqual(G->deckCount[currentPlayer], expected, "TEST FAILED: Card not drawn from player's deck.");

	// check that village is now in discard
	expected = village;
	testEqual(G->playedCards[G->playedCardCount - 1], expected, "TEST FAILED: Village is not in played cards pile.");

	// check that player has gained 2 actions
	expected = pre.numActions + 1;
	testEqual(G->numActions, expected, "TEST FAILED: Num actions is incorrect");
}

int main(){
	int i, j, p;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	struct gameState G;
	printf("----------------- Testing Card: %s ----------------\n", TESTFUNCTION);

	for (i = 0; i < 100; i++){
		for (j = 0; j < sizeof(struct gameState); j++){
			((char*)&G)[j] = floor(Random() * 256);
		}
		p = floor(Random() * 2);
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		G.playedCardCount = floor(Random() * MAX_DECK);
		G.whoseTurn = p;
		G.phase = 0;
		G.numActions = 1;
		checkCard(&G, p);
	}
	return 0;
}