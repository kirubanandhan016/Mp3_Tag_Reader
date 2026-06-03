#ifndef MP3_H
#define MP3_H

int validate_file(char *filename);
int view_mp3(char *filename);
int edit_mp3(char *filename, char *option, char *new_data);

#endif