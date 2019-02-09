#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // generate a random character from the preset inputs
    char charOptions[9] = {
    		'[', '(', '{', 
    		' ', 'a', 'x', 
    		'}', ')', ']'
    	};
    int min = 0;
    int max = 9;
    int randomNum = min + rand() % (max - min);

    return charOptions[randomNum];
}

char *inputString()
{
    // generate a string given preset characters and size
    int STR_LEN = 6;

    char charOptions[5] = {
    		'r', 'e', 's', 't', '\0'
    };
    char *res = (char*) malloc(STR_LEN * sizeof(char));		// initialize string
    int i;
    int min = 0;
    int max = 5;
    int randomNum;

    // construct string
    for(i = 0; i < STR_LEN; i++){	
    	randomNum = min + rand() % (max - min);
    	res[i] = charOptions[randomNum];	// select random char from charOptions
    }

    return res;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;

  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
