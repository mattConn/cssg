#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "strstack.h"
#include "parsefile.h"

// open and parse file lines
bool parsefile(const char *filepath, const strstack *fileargs)
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
		// check for markdown processor spec
		markdownp = markdownp ? markdownp : "markdown";

		// markdown command
		char mdcmd[50];
		sprintf(mdcmd, "%s %s", markdownp, filepath);

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


			char *filename = strchr(line, ' '); // second token (filepath)

			strstack argstack;
			initsstack(&argstack);
			char *tok = strtok(line, " ");
			tok = strtok(NULL, " ");
			tok = strtok(NULL, " ");
			while(tok)
			{
				pushsstack(&argstack, tok);
				tok = strtok(NULL, " ");
			}
			parsefile(filename+1, &argstack);

			freesstack(&argstack);
		}
		// no directive, check for fileargs
		else if(fileargs && fileargs->count > 0)
		{
			for(int i=0; i < strlen(line); i++)
			{
				if(line[i] == '$') // arg delimiter
				{
					int argnum = line[++i] - '0';
					if(argnum <= fileargs->count && argnum > 0) // if num is within arg arr. bounds
						printf("%s", fileargs->arr[argnum-1]);
					else // bad arg/not an arg, print delim and current char
					{
						fprintf(stderr, "** WARNING: Argument delimiter `%c` found, but no valid argument followed.\n", '$');
						printf("%c%c", '$',line[i]);
					}
					
				}
				else // no arg delim, print char
					printf("%c", line[i]);
			}
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
