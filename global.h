#ifndef GLOBAL_H
#define GLOBAL_H 

#include <stdio.h>

typedef enum Bool { false, true } bool;

char cwd[256]; // chdir buf
char *basedir; // base directory (defined in main)

// get file dir from file path (uses stringdup; must be freed)
char *getfiledir(const char *filepath);

// unistd chdir wrapper
void changedir(const char *filepath);

// markdown processor
char *markdownp;

// include directive
extern char *directive;

// program output destination
FILE *outfile;

#endif
