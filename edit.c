#include<stdio.h>
#include<string.h>
#include "mp3.h"

void get_tag_name(char *option, char *tag)
{
    if(strcmp(option, "-T") == 0)
        strcpy(tag, "TIT2");
    else if(strcmp(option, "-A") == 0)
        strcpy(tag, "TPE1");
    else if(strcmp(option, "-L") == 0)
        strcpy(tag, "TALB");
    else if(strcmp(option, "-Y") == 0)
        strcpy(tag, "TDRC");
    else if(strcmp(option, "-G") == 0)
        strcpy(tag, "TCON");
    else if(strcmp(option, "-C") == 0)
        strcpy(tag, "COMM");
    else
        strcpy(tag, "NONE");
}

int edit_mp3(char *filename, char *option, char *new_data)
{
    FILE *fp = fopen(filename, "rb+");

    if(fp == NULL)
    {
        printf("File not found\n");
        return 0;
    }

    char tag[5];
    get_tag_name(option, tag);

    if(strcmp(tag, "NONE") == 0)
    {
        printf("Invalid edit option\n");
        fclose(fp);
        return 0;
    }

    char header[10];
    char frame_id[5];
    unsigned char size[4];
    int frame_size;

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

        fread(size, 4, 1, fp);

        frame_size =
            (size[0] << 24) |
            (size[1] << 16) |
            (size[2] << 8)  |
             size[3];

        if(frame_size <= 0 || frame_size > 10000)
            break;

        fseek(fp, 2, SEEK_CUR);

        if(strcmp(frame_id, tag) == 0)
        {
            if(strlen(new_data) + 1 <= frame_size)
            {
                fputc(0, fp);
                fwrite(new_data, strlen(new_data), 1, fp);

                for(int j = strlen(new_data) + 1; j < frame_size; j++)
                    fputc(0, fp);

                printf("Tag updated successfully\n");
            }
            else
            {
                printf("New data is too long\n");
            }

            fclose(fp);
            return 1;
        }

        fseek(fp, frame_size, SEEK_CUR);
    }

    printf("Tag not found in this MP3/MPEG file\n");

    fclose(fp);
    return 0;
}