#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main(){
	FILE *fp;
	fp = fopen("unittestresults.out", "w+");
	fclose(fp);

	unittest1();
	unittest2();
	unittest3();
	unittest4();

	return 0;
}