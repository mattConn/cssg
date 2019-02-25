#include "global.h"

// stack of dynamically allocated strings
//=======================================

#ifndef MAX_STACK
	#define MAX_STACK 20
#endif

typedef struct Strstack
{
	char *arr[MAX_STACK];
	int count;
	
} strstack;

// init stack
bool initsstack(strstack *ss);

// push onto stack
bool pushsstack(strstack *ss, char *str);

// free all strings on heap
void freesstack(strstack *ss);
