#include<stdio.h>
#include<string.h>
#include "mp3.h"

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Usage:\n");
        printf(".\\mp3tag.exe -v file.mp3\n");
        printf(".\\mp3tag.exe -v file.mpeg\n");
        printf(".\\mp3tag.exe -e -T \"Song Name\" file.mp3\n");
        printf(".\\mp3tag.exe -e -A \"Artist\" file.mp3\n");
        printf(".\\mp3tag.exe -e -L \"Album\" file.mp3\n");
        printf(".\\mp3tag.exe -e -Y \"Year\" file.mp3\n");
        printf(".\\mp3tag.exe -e -G \"Genre\" file.mp3\n");
        printf(".\\mp3tag.exe -e -C \"Comment\" file.mp3\n");
        return 0;
    }

    if(strcmp(argv[1], "-v") == 0)
    {
        if(validate_file(argv[2]))
        {
            view_mp3(argv[2]);
        }
    }
    else if(strcmp(argv[1], "-e") == 0)
    {
        if(argc < 5)
        {
            printf("Usage: .\\mp3tag.exe -e -T \"New Song\" file.mp3\n");
            return 0;
        }

        if(validate_file(argv[4]))
        {
            edit_mp3(argv[4], argv[2], argv[3]);
        }
    }
    else
    {
        printf("Invalid option\n");
    }

    return 0;
}