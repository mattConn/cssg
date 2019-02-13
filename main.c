#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		fprintf(stderr, "** ERROR: No filepath argument.\n");
		return 1;
	}

	if(getfiledir(argv[1])) changedir( getfiledir(argv[1]) );

	basedir = getcwd(cwd, sizeof(cwd));

	if( strrchr(argv[1], '/') )
		openfile( strrchr(argv[1], '/')+1);
	else
		openfile(argv[1]);

	return 0;
}
