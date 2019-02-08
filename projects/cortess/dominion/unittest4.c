#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "numHandCards"
#define EQA(x, y) (x == y)

void unittest4() {
	int i;
	int expected;
	int seed = 1000;
	int numPlayers = 2;
	int currentPlayer = 0;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
					sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);
	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	expected = 5;
	printf("Testing starting hand");
	printf("Expected value: %d, Tested value: %d\n", expected, numHandCards(&G));

	if(EQA(expected, numHandCards(&G))){
		printf("TEST PASSED\n\n");
	} else {
		printf("TEST FAILED\n\n");
	}

	for (i = 0; i < G.handCount[currentPlayer]; i++){
		G.discard[currentPlayer][G.discardCount[currentPlayer]++] = G.hand[currentPlayer][i];//Discard
		G.hand[currentPlayer][i] = -1;//Set card to -1
	}
	G.handCount[currentPlayer] = 0;

	expected = 0;
	printf("Testing discarded hand.\n");
	printf("Expected value: %d, Tested value: %d\n", expected, numHandCards(&G));

	if(EQA(expected, numHandCards(&G))){
		printf("TEST PASSED\n\n");
	} else {
		printf("TEST FAILED\n\n");
	}
}

int main(int argc, char *argv[]){
	unittest4();
	return 0;
}