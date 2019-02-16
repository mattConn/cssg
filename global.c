#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

// file include directive
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

// open and parse file lines
bool parsefile(const char *filepath)
{
	FILE *fp = fopen(filepath, "r");

	// file open failure
	if(!fp)
	{
		fprintf(stderr, "** ERROR: Could not open file `%s`.\n", filepath);
		return false;
	}

	// get file extension
	char *fext = strrchr(filepath, '.');

	// if markdown file, hand to markdown processor
	if(strcmp(fext, ".md") == 0)
	{
		// markdown command
		char mdcmd[50];
		sprintf(mdcmd, "markdown %s", filepath);

		FILE *md = popen(mdcmd, "r");

		// write characters to stdout
		char c;
		while((c = fgetc(md)) != EOF) fputc(c, stdout);

		pclose(md);

		return true;
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
			parsefile(filename+1);
		}
		else
			printf("%s", line); // no direcitve, just print
	}

	// cleanup
	free(line);
	fclose(fp);

	changedir(basedir); // return to base directory

	return true;
}
