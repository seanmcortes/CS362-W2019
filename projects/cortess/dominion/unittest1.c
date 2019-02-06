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


	initializeGame(numPlayers, k, seed, &G);
	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	expected = 1;
	G.supplyCount[province] = 0;
	
	printf("Testing empty province cards.\n");
	printf("Expected value: %d, Tested value: %d\n", expected, isGameOver(&G));

	if(EQA(expected, isGameOver(&G))){
		printf("TEST PASSED\n");
	} else {
		printf("TEST FAILED\n");
	}

	expected = 1;
	G.supplyCount[province] = 1;
	for (i = 0; i < 25; i++){
		G.supplyCount[i] = 1;
	}
	G.supplyCount[0] = 0;
	G.supplyCount[12] = 0;
	G.supplyCount[24] = 0;

	printf("Testing three empty supply piles.\n");
	printf("Expected value: %d, Tested value: %d\n", expected, isGameOver(&G));
	if(EQA(expected, isGameOver(&G))){
		printf("TEST PASSED\n");
	} else {
		printf("TEST FAILED\n");
	}

	expected = 0;
	G.supplyCount[0] = 1;

	printf("Testing two empty supply piles.\n");
	printf("Expected value: %d, Tested value: %d\n", expected, isGameOver(&G));
	if(EQA(expected, isGameOver(&G))){
		printf("TEST PASSED\n");
	} else {
		printf("TEST FAILED\n");
	}
}

int main(int argc, char *argv[]){
	unittest1();
	return 0;
}