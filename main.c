#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

int main(int argc, char *argv[])
{
	// if no args
	if(argc == 1)
	{
		fprintf(stderr, "** ERROR: Not enough arguments.\n");
		return 1;
	}

	// path of file to parse
	char *filepath;

	// arg index
	int i = 1;

	// parse args
	for(; i < argc; i++)
	{
		// if flag is found
		if(argv[i][0] == '-')	
		{
			// markdown flag
			if(strcmp(argv[i], "-m") == 0)
			{
				// next in vector is markdown processor
				if(i+1 < argc)
					markdownp = argv[++i];
				else
				{
					fprintf(stderr, "** ERROR: Missing markdown processor after flag.\n", argv[i]);
					return 1;
				}
			}
			else
			{
				// using undefined flag
				fprintf(stderr, "** ERROR: Unrecognized flag `%s`.\n", argv[i]);
				return 1;
			}
		}
		// treat non-flag as filepath
		else
			filepath = argv[i];
	} // end parse args

	// if no file arg
	if(!filepath)
	{
		fprintf(stderr, "** ERROR: No filepath argument.\n");
		return 1;
	}

	// if path contains directories, get file from path
	char *filedir = getfiledir(filepath);
	if(filedir) changedir(filedir);

	// expand path
	realpath(argv[0], cwd);

	// set base directory
	basedir = getfiledir(cwd);

	if(filedir)
		parsefile(strrchr(filepath, '/')+1); // open file by name at end of path
	else
		parsefile(filepath);

	// uses strndup; must be freed
	free(filedir);

	return 0;
}
