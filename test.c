#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "strstack.h"

int main()
{
	char *line = NULL;
	size_t size = 0;
	FILE *f = fopen("testfiles/test.txt", "r");

	strstack ss;	
	initsstack(&ss);
	while(getline(&line, &size, f) != -1)
	{
		char *tok = strtok(line, " ");
		while(tok)
		{
			pushsstack(&ss, tok);
			tok = strtok(NULL, " ");
		}
	}

	for(int i = 0; i < ss.count; i++)
	{
		printf("%s\n", ss.arr[i]);
	}

	free(line);
	freesstack(&ss);
	fclose(f);

	return 0;
}
