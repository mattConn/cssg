#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "parsefile.h"

// specify build date and version for -v flag
#ifndef BUILD_DATE
#define BUILD_DATE "unspecified date"
#endif

#ifndef VERSION
#define VERSION "unspecified version"
#endif

/*
main.c will do the following and aim to exit early at any error:

initial definitions

parse args

handle file path (get directory and file name)

parse file

cleanup (free heap memory)
*/

int main(int argc, char *argv[])
{

	// initial definitions
	// ===================

	// if no args, early exit
	if(argc == 1)
	{
		fprintf(stderr, "** ERROR: Not enough arguments.\n");
		return 1;
	}

	char *filepath; // path of file to parse
	outfile = stdout; // output file

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

				// specify output file
				// -------------------
				case 'o':
					if(i+1 < argc)
					{
						outfile = fopen(argv[++i], "w");
						if(!outfile)
						{
							fprintf(stderr, "** ERROR: Could not open outfile `%s`.\n", argv[i]);
							return 1;
						}
					}
					else
					{
						fprintf(stderr, "** ERROR: Missing outfile after flag.\n");
						return 1;
					}
				break;

				// using undefined flag, exit program
				// ----------------------------------
				default:
					fprintf(stderr, "** ERROR: Unrecognized flag `%s`.\n", argv[i]);
					return 1;
			}
		}
		// treat non-flag as filepath
		else
			filepath = argv[i];
	}

	// handle file path
	// ================

	// if path contains directories, get get directories path and change to it
	char *filedir = getfiledir(filepath);
	if(filedir) changedir(filedir);

	// set base directory to where program was called from 
	realpath(argv[0], cwd); // expand path to absolute path
	basedir = getfiledir(cwd);

	// parse file
	// ==========

	if(filedir) // if filepath contained directories
		parsefile(strrchr(filepath, '/')+1, NULL); // open file by name at end of path
	else
		parsefile(filepath, NULL);

	// cleanup
	// =======

	// uses strndup; must be freed
	free(filedir);
	free(basedir);

	// if outfile was specified and opened
	if(outfile != stdout) fclose(outfile);

	return 0;
}
