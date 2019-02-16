typedef enum Bool { false, true } bool;

char cwd[256]; // chdir buf
char *basedir; // base directory (defined in main)

// get file dir from file path (uses stringdup; must be freed)
char *getfiledir(const char *filepath);

// unistd chdir wrapper
void changedir(const char *filepath);

// parse file lines
bool parsefile(const char *filepath);

// markdown processor
char *markdownp;
