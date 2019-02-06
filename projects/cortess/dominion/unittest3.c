#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "getCost"
#define EQA(x, y) (x == y)

void unittest3() {
	int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
					sea_hag, tribute, smithy, council_room};

	int expected[27] = {0, 2, 5, 8, 0,
						3, 6, 6, 5, 4, 
						4, 5, 4, 4, 3, 
						4, 3, 5, 3, 5, 
						3, 4, 2, 5, 4, 
						4, 4};

	char* cardNames[27] = {"curse", "estate", "duchy", "province", "copper", 
							"silver", "gold", "adventurer", "council_room", "feast", 
							"gardens", "mine", "remodel", "smithy", "village", 
							"baron", "great hall", "minion", "steward", "tribute", 
							"ambassador", "cutpurse", "embargo", "outpost", "salvager", 
							"sea hag", "treasure map"};
	FILE *fp;
	fp = fopen("unittestresults.out", "a+");

	initializeGame(numPlayers, k, seed, &G);
	fprintf(fp, "----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// expected = 0;
	// fprintf(fp, "Testing \"curse\".\n");
	// fprintf(fp, "Expected value: %d, Tested value: %d\n", expected, getCost(0));

	// if(EQA(expected, getCost(0))){
	// 	fprintf(fp, "TEST PASSED\n");
	// } else {
	// 	fprintf(fp, "TEST FAILED\n");
	// }

	for (i = 0; i < 27; i++) {
		fprintf(fp, "Testing \"%s\".\n", cardNames[i]);
		fprintf(fp, "Expected value: %d, Tested value: %d\n", expected[i], getCost(i));

		if(EQA(expected[i], getCost(i))){
			fprintf(fp, "TEST PASSED\n");
		} else {
			fprintf(fp, "TEST FAILED\n");
		}
	}
	

	fclose(fp);
}

int main(int argc, char *argv[]){
	unittest3();
	return 0;
}