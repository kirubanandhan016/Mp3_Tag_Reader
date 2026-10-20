# MP3 ID3 tag reader

This command-line program displays and edits common ID3 tags in MP3/MPEG files.
It supports ID3v2.3 and ID3v2.4 tags, including UTF-8 and UTF-16 text when
displaying tags.

## Build

With GCC installed and available on `PATH`, build from the project directory:

```text
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -o build/mp3tag.exe main.c mp3.c view.c edit.c
```

In VS Code, use **Terminal: Run Build Task** or start the debugger to build
automatically.

## Use

```text
build\mp3tag.exe -v song.mp3
build\mp3tag.exe -e -T "New title" song.mp3
```

Edit options are `-T` (title), `-A` (artist), `-L` (album), `-Y` (year),
`-G` (genre), and `-C` (comment). Editing updates an existing frame in place;
the new value must fit its current frame. ID3v2.3 edits accept ASCII text,
while ID3v2.4 edits store UTF-8. Compressed, encrypted, unsynchronised, and
extended-header tags are not supported.
