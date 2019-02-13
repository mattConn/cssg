#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

char directive[] = "#include";

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

bool openfile(const char *filepath)
{
	FILE *fp;

	// if directory in filepath

	char *filedir = getfiledir(filepath);
	if(filedir)	
	{

		if( chdir(filedir) < 0) // change to directory
		{
			fprintf(stderr, "** ERROR: Could not open directory `%s.`\n", filedir);
			free(filedir);
			return false;
		}
			free(filedir);
			fp = fopen( strchr(filepath, '/')+1, "r" );
	}
	else
		fp = fopen(filepath, "r");


	// file open failure
	if(!fp)
	{
		fprintf(stderr, "** ERROR: Could not open file `%s`.\n", filepath);
		return false;
	}

	// check file lines for directive

	char *line = NULL;
	size_t length = 0;
	while( getline(&line, &length, fp) != -1 )
	{
		// if directive found
		if( strncmp(line, directive, strlen(directive)) == 0 )
		{
			if(line[strlen(line)-1] == '\n') // chomp
				line[strlen(line)-1] = '\0';

			char *filename = strchr(line, ' '); // last token (filepath)
			openfile(filename+1);
		}
		else
			printf("%s", line); // no direcitve, just print
	}

	free(line);

	printf("BDIR: %s\n", basedir);
	printf("CDIR: %s\n", getcwd(cwd, sizeof(cwd)));
	changedir(basedir); // return to base directory
	printf("CDIR2: %s\n", getcwd(cwd, sizeof(cwd)));

	return true;
}
