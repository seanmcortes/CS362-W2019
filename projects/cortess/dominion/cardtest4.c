#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "Village"

void testEqual(int val, int expected){
	printf("Value: %d\tExpected: %d\n", val, expected);
	if(val == expected){
		printf("TEST PASSED.\n\n");
	} else {
		printf("TEST FAILED.\n\n");
	}
}

void cardtest4() {
	int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState pre;
	struct gameState post;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
					sea_hag, tribute, smithy, council_room};
	int currentPlayer;
	int card = village;
	int choice1 = -1;
	int choice2 = -1;
	int choice3 = -1;
	int handPos = 0;
	int expected = 0;

	initializeGame(numPlayers, k, seed, &post);
	memcpy(&pre, &post, sizeof(struct gameState));
	currentPlayer = whoseTurn(&post);
	
	printf("----------------- Testing Card: %s ----------------\n", TESTFUNCTION);
	post.hand[currentPlayer][0] = card;
	printf("Card tested: %d\n", post.hand[currentPlayer][0]);
	playCard(handPos, choice1, choice2, choice3, &post);	// activate card

	// Effect: draw 1 card, gain 2 actions.
	expected = pre.handCount[currentPlayer];
	printf("Testing that current player has drawn 1 card.\n");
	testEqual(post.handCount[currentPlayer], expected);

	expected = village;
	printf("Testing that village is now in played pile.\n");
	testEqual(post.playedCards[post.playedCardCount - 1], village);
	printf("Played count: %d\n", post.playedCardCount);

	expected = pre.numActions + 1;
	printf("Testing that current player has gained 2 actions.\n");
	testEqual(post.numActions, expected);

	expected = pre.handCount[currentPlayer + 1];
	printf("Testing that other player's hand remains unaffected.\n");
	testEqual(post.handCount[currentPlayer + 1], expected);
}

int main(int argc, char *argv[]){
	cardtest4();
	return 0;
}