#include "strstack.h"
#include "global.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// stack of dynamically allocated strings
//=======================================

// init stack
void initstack(strstack *ss)
{
	ss->count = 0;
	ss->top = -1;
	for(int i = 0; i < MAX_STACK; i++) ss->arr[i] = NULL; 
}

// push onto stack
bool pushstack(strstack *ss, char *str)
{
	if(ss->count < MAX_STACK)
	{
		ss->arr[ss->count] = (char *) malloc(strlen(str) * sizeof(char));
		strcpy(ss->arr[ss->count], str);

		ss->count++;	
		ss->top++;	

		return true;
	}
	else
		fprintf(stderr, "** WARNING: Could not push string: at full capacity.\n");

	return false;
}

// free all strings on heap
void freestack(strstack *ss)
{
	int i = 0;
	while(ss->arr[i] != NULL && i < MAX_STACK)
	{
		free(ss->arr[i]);
		i++;
	}
}
