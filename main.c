#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "parsefile.h"

#ifndef BUILD_DATE
#define BUILD_DATE "unspecified date"
#endif

#ifndef VERSION
#define VERSION "unspecified version"
#endif

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

	// parse args
	//===========

	// arg index
	int i = 1;

	for(; i < argc; i++)
	{
		// if flag is found
		if(argv[i][0] == '-' && strlen(argv[i])>1)
		{
			switch(argv[i][1])
			{
				// markdown flag
				//--------------
				case 'm':
					// next in vector is markdown processor
					if(i+1 < argc)
						markdownp = argv[++i];
					else
					{
						fprintf(stderr, "** ERROR: Missing markdown processor after flag.\n");
						return 1;
					}
				break;

				// print version info
				//-------------------
				case 'v':
					printf("CSSG %s.\nBuilt on %s.\n", VERSION, BUILD_DATE);
					return 0;
				break;

				// using undefined flag
				default:
					fprintf(stderr, "** ERROR: Unrecognized flag `%s`.\n", argv[i]);
					return 1;
			}
		}
		// treat non-flag as filepath
		else
			filepath = argv[i];
	}

	// ==============
	// end parse args

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

	// define include directive
	directive = "#include";

	// parse file
	if(filedir)
		parsefile(strrchr(filepath, '/')+1, NULL); // open file by name at end of path
	else
		parsefile(filepath, NULL);

	// uses strndup; must be freed
	free(filedir);
	free(basedir);

	return 0;
}
