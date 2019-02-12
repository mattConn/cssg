#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum Bool { false, true } bool;

char directive[] = "#include";

bool openfile(const char *filepath)
{
	FILE *fp = fopen(filepath, "r");

	// file open failure
	if(fp == NULL)
	{
		fprintf(stderr, "Could not open `%s`.\n", filepath);
		return false;
	}

	char *line = NULL;
	size_t length = 0;

	while( getline(&line, &length, fp) != -1 )
	{
		// if directive found
		if( strncmp(line, directive, strlen(directive)) == 0 )
		{
			if(line[strlen(line)-1] == '\n') // chomp
				line[strlen(line)-1] = '\0';

			char *tmp = strchr(line, ' '); // last token (filepath)
			openfile(tmp+1);
		}
		else
			printf("%s", line); // no direcitve, just print
	}

	free(line);

	return true;
}

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		fprintf(stderr, "No filepath argument.\n");
		return 1;
	}

	openfile(argv[1]);

	return 0;
}
