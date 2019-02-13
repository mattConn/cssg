#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef enum Bool { false, true } bool;

char cwd[256]; // chdir buf
char *basedir;

// get file dir from file path (uses stringdup; must be freed)
char *getfiledir(const char *filepath);

// unistd chdir wrapper
void changedir(const char *filepath);

bool openfile(const char *filepath);
