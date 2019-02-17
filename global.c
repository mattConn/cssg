#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

// get file dir from file path (uses stringdup; must be freed)
char *getfiledir(const char *filepath)
{
	char *slashloc = strrchr(filepath, '/');

	if(slashloc) return strndup(filepath, strlen(filepath) - strlen(slashloc));

	return NULL;
}

// unistd chdir wrapper
void changedir(const char *filepath)
{
	if(chdir(filepath) < 0)
		fprintf(stderr, "** ERROR: Could not change to directory `%s`.\n", filepath);
}
