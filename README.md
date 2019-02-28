# CSSG (C Static Site Generator)
Another static site generator, written in C.

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
To insert strings in a file, specify strings after an include. Strings must be separated by a character. If the string separator was `,`, the include would look like:

```
#include /path/to/file , string1, string2, stringN
```

For example, consider two files `document.txt` and `greeting.txt`, where we want to include `greeting.txt` in `document.txt`:

```
# document.txt:

#include greeting.txt , hello, world
```
```
# greeting.txt:

A lot of programs like to say "$1 $2!" 
```

Running `cssg document.txt` will write the following to stdout:
```
A lot of programs like to say "hello world!" 
```
The argument separator can be whatever character you like:
```
#include greeting.txt % hello% world
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

## Building
Run `make` to compile with gcc. The binary will be `cssg`.
