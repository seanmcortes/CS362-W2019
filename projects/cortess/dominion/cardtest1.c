#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "Adventurer"

void testEqual(int val, int expected){
	printf("Value: %d\tExpected: %d\n", val, expected);
	if(val == expected){
		printf("TEST PASSED.\n\n");
	} else {
		printf("TEST FAILED.\n\n");
	}
}

void cardtest1() {
	int seed = 1000;
	int numPlayers = 2;
	struct gameState pre;
	struct gameState post;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
					sea_hag, tribute, smithy, council_room};
	int currentPlayer;
	int card = adventurer;
	int choice1 = -1;
	int choice2 = -1;
	int choice3 = -1;
	int handPos = 0;
	int expected = 0;
	int deckCounter = 0;

	initializeGame(numPlayers, k, seed, &post);
	memcpy(&pre, &post, sizeof(struct gameState));
	currentPlayer = whoseTurn(&post);
	
	printf("----------------- Testing Card: %s ----------------\n", TESTFUNCTION);
	post.hand[currentPlayer][0] = card;		// set first card in hand to adventurer
	post.deck[currentPlayer][deckCounter - 1] = copper;		// set top two cards in the deck to be coppers
	post.deck[currentPlayer][deckCounter - 2] = copper;	
	if(playCard(handPos, choice1, choice2, choice3, &post) < 0){
		printf("TEST FAILED. playCard crash.\n");
	}

	// check that current player has gained two cards to hand
	printf("Testing that current player has gained two cards.\n");	// default deck contains two copper at top
	expected = pre.handCount[currentPlayer] + 1;
	testEqual(post.handCount[currentPlayer], expected);

	// check that other player has not drawn any cards
	expected = pre.handCount[currentPlayer + 1];
	printf("Testing that other player's hand has not been affected.\n");
	testEqual(post.handCount[currentPlayer + 1], expected);

	// check that cards drawn came from current player's deck
	expected = pre.deckCount[currentPlayer] - 2;
	printf("Testing that cards drawn is from correct player's deck.\n");
	testEqual(post.deckCount[currentPlayer], expected);

	// check that other player's deck is unaffected
	printf("Other player's deck is unaffected.\n");
	expected = pre.deckCount[currentPlayer + 1];
	testEqual(post.deckCount[currentPlayer + 1], expected);

	// check that all non-treasure cards are discarded
	printf("Testing that non-treasure cards are discarded.\n");	
	memcpy(&post, &pre, sizeof(struct gameState));	// reset game state
	post.hand[currentPlayer][0] = card;
	deckCounter = post.deckCount[currentPlayer];
	post.deck[currentPlayer][deckCounter - 1] = estate;		// set first card in deck to estate (ensure full effect of adventurer occurs)
	playCard(handPos, choice1, choice2, choice3, &post);

	expected = 1;
	testEqual(post.discardCount[currentPlayer], expected);		// test that the estate is removed

	expected = pre.handCount[currentPlayer + 1];
	printf("Testing that other player's hand is not affected.\n");
	testEqual(post.handCount[currentPlayer + 1], expected);

	// check victory cards are not affected
	printf("Checking that game states have not been changed...\n");

	expected = 8;
	printf("Victory cards are unaffected.\n");
	testEqual(post.supplyCount[estate], expected);
	testEqual(post.supplyCount[duchy], expected);
	testEqual(post.supplyCount[province], expected);
}

int main(int argc, char *argv[]){
	cardtest1();
	return 0;
}