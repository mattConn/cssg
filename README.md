# CSSG (C Static Site Generator)
A static site generator and file manipulator for Linux and Mac. Concatenates files, inserts text, writes to files and more.

## Usage
In your shell:
```
$ cssg path/to/file
```
This will write the results to stdout.

To include files, use `#include /path/to/file` in a document.

## Features

### Include Arguments

#### String Insertion
To insert strings in a file, specify strings after an include, separated by a comma:

```
#include /path/to/file string1, string2, stringN
```

For example, consider two files `document.txt` and `greeting.txt`, where we want to include `greeting.txt` in `document.txt`:

```
# document.txt:

#include greeting.txt hello, world
```
```
# greeting.txt:

A lot of programs like to say "$1 $2!" 
```

Running `cssg document.txt` will write the following to stdout:
```
A lot of programs like to say "hello world!" 
```
The locations to insert a string in a file must be specified by a `$N` delimiter, where N is the number of the argument in the include line, starting from 1.

### Markdown handling
By default, when a file with a `.md` extension is included in another file, cssg will use whatever markdown processor is in your `$PATH` by the name of `markdown`.

You can specify what markdown processor to use via the `-m` flag. For example, if you wanted to use pandoc:
```
$ cssg -m pandoc path/to/file
```
Or, specify the path of the processor:
```
$ cssg -m /usr/bin/pandoc path/to/file
```

### Writing to a File
By default, CSSG will write its results to stdout. You can specify another file to write to with the `-o` flag:
```
$ cssg path/to/file -o /output/file
```

### Comments
A line can be commented out by starting it with a `#` character:

```
This line will be written to stdout.
# This line will not.
```

## Building
Run `make` to compile with gcc. The binary will be `cssg`.
