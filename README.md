# CSSG (C Static Site Generator)
Another static site generator, written in C.

## Usage
`cssg path/to/file`

This will write the results to stdout.

To include files, use `#include /path/to/file` in document.

### Markdown handling
By default, when a file with a `.md` extension is included in a file, cssg will use whatever `markdown` processor is in your `$PATH`.

You can specify what markdown processor to use via the `-m` flag. For example, if you wanted to use pandoc:
```
cssg -m pandoc index.html
```
Or, specify the path of the processor:
```
cssg -m /usr/bin/pandoc index.html
```

## Building
Run `make` to compile with gcc. The binary will be `cssg`.
