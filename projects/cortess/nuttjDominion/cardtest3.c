#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "Gardens"

void testEqual(int val, int expected){
	printf("Value: %d\tExpected: %d\n", val, expected);
	if(val == expected){
		printf("TEST PASSED.\n\n");
	} else {
		printf("TEST FAILED.\n\n");
	}
}

void cardtest3() {
	int seed = 1000;
	int numPlayers = 2;
	struct gameState pre;
	struct gameState post;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
					sea_hag, tribute, smithy, council_room};
	int currentPlayer;
	int card = gardens;
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
		// activate card

	// Effect: return -1
	expected = -1;
	printf("Testing that playing this card results in no effect.\n");
	testEqual(playCard(handPos, choice1, choice2, choice3, &post), expected);

	expected = pre.handCount[currentPlayer];
	printf("Testing that current player's hand remains same size.\n");
	testEqual(post.handCount[currentPlayer], expected);

	expected = pre.playedCardCount;
	printf("Testing that current player's played pile is unaffected.\n");
	testEqual(post.playedCardCount, expected);

	expected = pre.handCount[currentPlayer + 1];
	printf("Testing that other player's hand is unaffected.\n");
	testEqual(post.handCount[currentPlayer + 1], expected);
}

int main(int argc, char *argv[]){
	cardtest3();
	return 0;
}