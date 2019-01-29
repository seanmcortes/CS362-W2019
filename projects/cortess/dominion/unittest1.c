#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "isGameOver"
#define EQA(x, y) (x == y)

void unittest1() {
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

	expected = 1;
	G.supplyCount[province] = 0;
	
	fprintf(fp, "Testing empty province cards.\n");
	fprintf(fp, "Expected value: %d, Tested value: %d\n", expected, isGameOver(&G));

	if(EQA(expected, isGameOver(&G))){
		fprintf(fp, "TEST PASSED\n");
	} else {
		fprintf(fp, "TEST FAILED\n");
	}

	expected = 1;
	G.supplyCount[province] = 1;
	for (i = 0; i < 25; i++){
		G.supplyCount[i] = 1;
	}
	G.supplyCount[0] = 0;
	G.supplyCount[12] = 0;
	G.supplyCount[24] = 0;

	fprintf(fp, "Testing three empty supply piles.\n");
	fprintf(fp, "Expected value: %d, Tested value: %d\n", expected, isGameOver(&G));
	if(EQA(expected, isGameOver(&G))){
		fprintf(fp, "TEST PASSED\n");
	} else {
		fprintf(fp, "TEST FAILED\n");
	}

	expected = 0;
	G.supplyCount[0] = 1;

	fprintf(fp, "Testing two empty supply piles.\n");
	fprintf(fp, "Expected value: %d, Tested value: %d\n", expected, isGameOver(&G));
	if(EQA(expected, isGameOver(&G))){
		fprintf(fp, "TEST PASSED\n");
	} else {
		fprintf(fp, "TEST FAILED\n");
	}
	fclose(fp);
}