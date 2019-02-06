#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "Smithy"

void testEqual(int val, int expected){
	printf("Value: %d\tExpected: %d\n", val, expected);
	if(val == expected){
		printf("TEST PASSED.\n\n");
	} else {
		printf("TEST FAILED.\n\n");
	}
}

void cardtest2() {
	int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState pre;
	struct gameState post;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
					sea_hag, tribute, smithy, council_room};
	int currentPlayer;
	int card = smithy;
	int choice1 = -1;
	int choice2 = -1;
	int choice3 = -1;
	int handPos = 0;
	int expected = 0;
	// int bonus = 0;
	// int count = 0;

	initializeGame(numPlayers, k, seed, &post);
	memcpy(&pre, &post, sizeof(struct gameState));
	currentPlayer = whoseTurn(&post);
	
	printf("----------------- Testing Card: %s ----------------\n", TESTFUNCTION);
	post.hand[currentPlayer][0] = card;
	printf("Card tested: %d\n", post.hand[currentPlayer][0]);
	printf("Post played card count: %d\n", post.playedCardCount);
	// Effect: draw 3 cards
	if(playCard(handPos, choice1, choice2, choice3, &post) > -1){
		// check that current player has drawn 3 cards (pre hand + 2)
		expected = pre.handCount[currentPlayer] + 2;
		printf("Testing correct player has drawn 3 cards.\n");
		testEqual(post.handCount[currentPlayer], expected);

		// check that smithy is now in discard
		expected = smithy;
		printf("Testing that smithy is now in played cards pile.\n");
		testEqual(post.playedCards[post.playedCardCount - 1], expected);

		// check state of other player hand and discard has not changed
		expected = pre.handCount[currentPlayer + 1];
		printf("Testing that other player's hand has not been affected.\n");
		testEqual(post.handCount[currentPlayer + 1], expected);
	}
}

int main(int argc, char *argv[]){
	cardtest2();
	return 0;
}