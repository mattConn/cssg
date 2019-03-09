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
void initstack(strstack *ss);

// push onto stack
bool pushstack(strstack *ss, char *str);

// free all strings on heap
void freestack(strstack *ss);

#endif
