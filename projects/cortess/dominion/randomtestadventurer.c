#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define TESTFUNCTION "Adventurer"

void testEqual(int val, int expected, char* message){
	if(val != expected){
		printf("%s\n", message);
	}
}

void checkCard(struct gameState *G, int currentPlayer){
	struct gameState pre;
	int i;
	int preTreasureCount = 0;
	int postTreasureCount = 0;
	int choice1 = -1;
	int choice2 = -1;
	int choice3 = -1;
	int handPos = 0;
	int card = adventurer;
	int expected;

	memcpy(&pre, G, sizeof(struct gameState));

	G->hand[currentPlayer][handPos] = card;

	// get count of treasure cards in pre hand
	for (i = 0; i < G->handCount[currentPlayer]; i++){
		if (G->hand[currentPlayer][i] == copper || G->hand[currentPlayer][i] == silver || G->hand[currentPlayer][i] == gold){
			preTreasureCount++;
		}
	}

	if(playCard(handPos, choice1, choice2, choice3, G) < 0){
		printf("TEST FAILED. playCard crash.\n");
	}

	// check that current player has gained 2 cards
	expected = pre.handCount[currentPlayer] + 1;
	testEqual(G->handCount[currentPlayer], expected, "TEST FAILED: Player did not gain 2 cards.");

	// check that cards drawn came from current player's deck
	expected = pre.deckCount[currentPlayer] - (G->discardCount[currentPlayer] - pre.discardCount[currentPlayer] + 2);
	testEqual(G->deckCount[currentPlayer], expected, "TEST FAILED: Card not drawn from player's deck.");

	// check that adventurer is now in discard
	expected = adventurer;
	testEqual(G->playedCards[G->playedCardCount - 1], expected, "TEST FAILED: Village is not in played cards pile.");

	// get count of treasure cards in post hand
	for (i = 0; i < G->handCount[currentPlayer]; i++){
		if (G->hand[currentPlayer][i] == copper || G->hand[currentPlayer][i] == silver || G->hand[currentPlayer][i] == gold){
			postTreasureCount++;
		}
	}

	// check that player has gained 2 treasure cards
	expected = preTreasureCount + 2;
	testEqual(postTreasureCount, expected, "TEST FAILED: Player did not gain 2 treasure cards");
}

int main(){
	int i, j, z, p;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	struct gameState G;
	int seed = time(NULL);
	srand(seed);

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

		printf("Deck Count: %d\n", G.deckCount[p]);

		for (z = 0; z < G.deckCount[p]; z++){
			G.deck[p][z] = rand() % (6 + 1 - 2) + 2;
		}

		for (z = 0; z < G.handCount[p]; z++){
			G.hand[p][z] = rand() % (6 + 1 - 2) + 2;
		}

		checkCard(&G, p);
	}
	return 0;
}