# MP3 Tag Reader & Editor in C

A command-line C project for reading and editing supported ID3 metadata in MP3 files. The project focuses on binary file handling, frame parsing, structures, and command-line arguments.

## Features

- Read supported ID3 metadata frames
- Parse selected ID3 frames
- View metadata from the command line
- Edit supported fields when the required frame already exists
- Modular C source files

## Technology

C · GCC · ID3 metadata · Binary file I/O

## Build

Clone the repository:

```bash
git clone https://github.com/kirubanandhan016/Mp3_Tag_Reader.git
cd Mp3_Tag_Reader
```

Compile with GCC:

```bash
gcc -Wall -Wextra main.c edit.c view.c -o mp3tag
```

On Windows, compile to `mp3tag.exe` if desired:

```powershell
gcc -Wall -Wextra main.c mp3.c edit.c view.c -o mp3tag.exe
```

## Usage examples

View metadata:

**Windows PowerShell**
```powershell
.\mp3tag.exe -v ".\songs\song.mp3"
```

**macOS/Linux**
```bash
./mp3tag -v songs/song.mp3
```

Edit examples depend on the CLI options supported by the current source. For example, the documented title-edit command is:

```powershell
.\mp3tag.exe -e -T "Song Title" ".\songs\song.mp3"
```

## Known limitations

- The editor cannot currently add every missing metadata frame (for example, a missing `TIT2` frame).
- Behavior can vary with the frames already present in the file.
- Compatibility with different ID3 versions and frame encodings requires further testing.

Test with copies of audio files, not your only copy of an original. Confirm that sample audio files can legally be redistributed before committing them.

## Project scope

This C project demonstrates file-format handling and is secondary to the Python backend projects in my portfolio.

## Author

**Kirubanandhan V** · [GitHub](https://github.com/kirubanandhan016)
