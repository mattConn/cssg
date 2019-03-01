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
	// get file extension
	char *fext = strrchr(filepath, '.');

	// if filepath has file extension
	if(fext)
	{
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
	}

	// open file
	FILE *fp = fopen(filepath, "r");

	// file open failure
	if(!fp)
	{
		fprintf(stderr, "** ERROR: Could not open file `%s`.\n", filepath);
		fclose(fp);
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

			char *filename = NULL;

			// tokenize line
			//--------------

			char *tok = strtok(line, " "); // first tok.: directive

			tok = strtok(NULL, " "); // second tok.: filename
			if(tok) // check for filename tok
			{
				filename = (char *) malloc(strlen(tok) * sizeof(char));
				strcpy(filename, tok);
			}
			else
			{
				fprintf(stdout, "** ERROR: Include directive found but no file specified.\n");
				return false;
			}


			tok = strtok(NULL, " "); // third tok.: arg. delim

			if(tok) // if delim tok was found in line
			{
				// dynamic string stack for file args
				strstack argstack;
				initsstack(&argstack);

				// allocate mem. for delim. token
				char *argDelim = (char *) malloc(strlen(tok) * sizeof(char));
				strcpy(argDelim, tok);

				tok = strtok(NULL, argDelim); // fourth tok.: first arg
				while(tok) // store file args
				{
					if(tok[0] == ' ') tok++; // ignore single leading whitespace
					pushsstack(&argstack, tok);
					tok = strtok(NULL, argDelim);
				}

				free(argDelim); // frem delim. mem.

				parsefile(filename, &argstack);

				// free dyn str stack
				freesstack(&argstack);
			}
			else
				parsefile(filename, NULL);

			// clean up
			free(filename);
		}
		// no directive:

		// check if comment
		else if(line[0] == '#')
		{/*do nothing*/}
		//  check for fileargs
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
						printf("%c%c", '$',line[i]);
					
				}
				else // no arg delim, print char
					printf("%c", line[i]);
			}
		}
		else
			printf("%s", line); // no direcitve, just print
	} // end getline routine

	// cleanup
	free(line);
	fclose(fp);

	changedir(basedir); // return to base directory

	return true;
}
