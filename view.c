#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mp3.h"

int validate_file(char *filename)
{
    char *ext = strrchr(filename, '.');

    if(ext == NULL)
    {
        printf("Invalid file name\n");
        return 0;
    }

    if(strcmp(ext, ".mp3") == 0 || strcmp(ext, ".mpeg") == 0)
    {
        return 1;
    }

    printf("Unsupported file format. Use .mp3 or .mpeg only\n");
    return 0;
}

int view_mp3(char *filename)
{
    FILE *fp = fopen(filename, "rb");

    if(fp == NULL)
    {
        printf("File not found\n");
        return 0;
    }

    char header[10];
    char frame_id[5];
    unsigned char size[4];
    int frame_size;
    char *data;

    char song[100]    = "No Song Name";
    char artist[100]  = "No Artist";
    char album[100]   = "No Album";
    char year[50]     = "No Year";
    char genre[100]   = "No Genre";
    char comment[200] = "No Comment";

    fread(header, 10, 1, fp);

    if(strncmp(header, "ID3", 3) != 0)
    {
        printf("ID3 tag not found\n");
        fclose(fp);
        return 0;
    }

    for(int i = 0; i < 50; i++)
    {
        if(fread(frame_id, 4, 1, fp) != 1)
            break;

        frame_id[4] = '\0';

        if(frame_id[0] == '\0')
            break;

        fread(size, 4, 1, fp);

        frame_size =
            (size[0] << 24) |
            (size[1] << 16) |
            (size[2] << 8)  |
             size[3];

        if(frame_size <= 0 || frame_size > 10000)
            break;

        fseek(fp, 2, SEEK_CUR);

        data = malloc(frame_size + 1);

        if(data == NULL)
        {
            printf("Memory allocation failed\n");
            fclose(fp);
            return 0;
        }

        fread(data, frame_size, 1, fp);
        data[frame_size] = '\0';

        if(strcmp(frame_id, "TIT2") == 0 && strlen(data + 1) > 0)
            strcpy(song, data + 1);

        else if(strcmp(frame_id, "TPE1") == 0 && strlen(data + 1) > 0)
            strcpy(artist, data + 1);

        else if(strcmp(frame_id, "TALB") == 0 && strlen(data + 1) > 0)
            strcpy(album, data + 1);

        else if((strcmp(frame_id, "TYER") == 0 ||
                 strcmp(frame_id, "TDRC") == 0) && strlen(data + 1) > 0)
            strcpy(year, data + 1);

        else if(strcmp(frame_id, "TCON") == 0 && strlen(data + 1) > 0)
            strcpy(genre, data + 1);

        else if(strcmp(frame_id, "COMM") == 0)
        {
            int start = 4;

            while(start < frame_size && data[start] != '\0')
                start++;

            start++;

            if(start < frame_size && strlen(data + start) > 0)
                strcpy(comment, data + start);
        }

        free(data);
    }

    printf("\n===== MP3 Album Details =====\n\n");
    printf("Song Name : %s\n", song);
    printf("Artist    : %s\n", artist);
    printf("Album     : %s\n", album);
    printf("Year      : %s\n", year);
    printf("Genre     : %s\n", genre);
    printf("Comment   : %s\n", comment);

    fclose(fp);
    return 1;
}