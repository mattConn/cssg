#include "global.h"

#ifndef MAX_STACK
	#define MAX_STACK 20
#endif

typedef struct Strstack
{
	char *arr[MAX_STACK];
	int count;
	
} strstack;

bool initsstack(strstack *ss);

bool pushsstack(strstack *ss, char *str);

void freesstack(strstack *ss);
