#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	int minChar = 32; //ASCII space
	int maxChar = 125; //ASCII '}'
	char ch;

	// random number ASCII 32 to 125 (inclusive)
	ch = rand() % (maxChar + 1 - minChar) + minChar;
    return ch;
}

char *inputString()
{
	int minCString = 97;
	int maxCString = 122;
	int len = 6;
	char *randString = malloc(len);
	int i;
	
	for(i = 0; i < len - 1; i++) {
		// random number ASCII 97 to 122 (inclusive), lowercase alpha
		randString[i] = rand() % (maxCString + 1 - minCString) + minCString;
	}
	
	// end string with null terminator
	randString[i] = '\0';
	
    return randString;
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
	  free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
