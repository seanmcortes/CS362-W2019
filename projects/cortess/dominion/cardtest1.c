#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "Adventurer"
#define EQA(x, y) (x == y)

void cardtest1() {
	int i;
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
	int bonus = 0;
	int count = 0;

	initializeGame(numPlayers, k, seed, &post);
	memcpy(&pre, &post, sizeof(struct gameState));
	currentPlayer = whoseTurn(&post);
	
	printf("----------------- Testing Card: %s ----------------\n", TESTFUNCTION);
	printf("Current player: %d\n", currentPlayer);
	post.hand[currentPlayer][0] = card;
	printf("Card tested: %d\n", post.hand[currentPlayer][0]);
	playCard(handPos, choice1, choice2, choice3, &post);
	// cardEffect(card, choice1, choice2, choice3, &post, handPos, &bonus);
	// if(cardEffect(card, choice1, choice2, choice3, &post, handPos, &bonus) != 0){
	// 		printf("TEST FAILED. cardTest1 returned non 0 value\n");
	// } else {
	// 	count = post.handCount[]
	// }
	printf("Pre: %d\nPost: %d\n", pre.handCount[currentPlayer], post.handCount[currentPlayer]);

	printf("Prehand: ");
	for(i = 0; i < pre.handCount[currentPlayer]; i++){
		printf("%d, ", pre.hand[currentPlayer][i]);
	}

	printf("\nPosthand: ");
	for(i = 0; i < post.handCount[currentPlayer]; i++){
		printf("%d, ", post.hand[currentPlayer][i]);
	}
	// int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
}

int main(int argc, char *argv[]){
	cardtest1();
	return 0;
}