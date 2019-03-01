#ifndef STRSTACK_H
#define STRSTACK_H

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
void initsstack(strstack *ss);

// push onto stack
bool pushsstack(strstack *ss, char *str);

// free all strings on heap
void freesstack(strstack *ss);

#endif
