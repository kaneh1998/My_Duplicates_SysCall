#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <getopt.h>

#include "duplicates.h"

int globalCounter = 0;

void findFilesRecursive(char *basePath, HASH_LIST *hash)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    struct stat buffer;

   
    if (!dir) {
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {

        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.') // Skips hidden folders with '.'
        {

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name); // Building new path for recursive finding of files + directories

            if (dp->d_type != 4) {

                printf("\n%s\n", dp->d_name);
                hash->fileName[globalCounter] = dp->d_name;
                hash->hashString[globalCounter] = strSHA2(path);
                printf("HASH: %s\n", hash->hashString[globalCounter]);

                //printf("PATH: %s\n", path);

                int status = stat(path, &buffer);

                if (status != 0) {
                    perror("ERROR: ");
                    exit(EXIT_FAILURE);
                }

                printf("Size: %li\n", buffer.st_size);
                hash->fileSize[globalCounter] = buffer.st_size;
                hash->totalFileSize += buffer.st_size;
                hash->totalFiles += 1;
                printf("Files found so far: %i\n", hash->totalFiles);
                printf("File 0 name: %s\n", hash->fileName[6]);

            }

            if (hash->fileName[globalCounter] != NULL) { // NULL when directory is encountered 
                printf("File name from hash table: %s\n\n", hash->fileName[globalCounter]);
            }

            globalCounter++;

            findFilesRecursive(path, hash);
        }
    }

    closedir(dir);

}