#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "whoseTurn"
#define EQA(x, y) (x == y)

void unittest2() {
	int i;
	int expected;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
					sea_hag, tribute, smithy, council_room};

	FILE *fp;
	fp = fopen("unittestresults.out", "a+");

	initializeGame(numPlayers, k, seed, &G);
	fprintf(fp, "----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	expected = 0;
	
	fprintf(fp, "Testing first players turn.\n");
	fprintf(fp, "Expected value: %d, Tested value: %d\n", expected, whoseTurn(&G));

	if(EQA(expected, whoseTurn(&G))){
		fprintf(fp, "TEST PASSED\n");
	} else {
		fprintf(fp, "TEST FAILED\n");
	}

	expected = 1;
	G.whoseTurn = 1;

	fprintf(fp, "Testing second player's turn.\n");
	fprintf(fp, "Expected value: %d, Tested value: %d\n", expected, isGameOver(&G));
	if(EQA(expected, whoseTurn(&G))){
		fprintf(fp, "TEST PASSED\n");
	} else {
		fprintf(fp, "TEST FAILED\n");
	}

	fclose(fp);
}