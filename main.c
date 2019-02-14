#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

int main(int argc, char *argv[])
{
	// if no file arg
	if(argc == 1)
	{
		fprintf(stderr, "** ERROR: No filepath argument.\n");
		return 1;
	}

	// if path contains directories, get file from path
	char *filedir = getfiledir(argv[1]);
	if(filedir) changedir(filedir);

	// expand path
	realpath(argv[0], cwd);

	// set base directory
	basedir = getfiledir(cwd);

	if(filedir)
		openfile(strrchr(argv[1], '/')+1); // open file by name at end of path
	else
		openfile(argv[1]);

	// uses strndup; must be freed
	free(filedir);

	return 0;
}
