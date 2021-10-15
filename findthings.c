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

void findFilesRecursive(char *basePath, HASH_LIST *hash)
{
    char path[10000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    struct stat buffer;
   
    if (!dir) {
        return;
    }

    while ((dp = readdir(dir)) != NULL) // TODO: Add support for the -a
    {
        //printf("File No: %li\n", hash->totalFiles);
        //printf("BASEPATH: %s\n", basePath);
        //printf("\nFILE NAME: \t%s\n", dp->d_name);
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.' && hash->aFlag == false) {
        // DOES NOT pass files when:
        // -    File name is "." OR ".." OR ".xxxx" OR "aFlag = False" 

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name); // Building new path for recursive finding of files + directories

            if (dp->d_type != 4) { // Not a directory

                int status = stat(path, &buffer); //To find size of file
                if (status != 0) {
                    perror("ERROR: ");
                }

                hash->fileName[hash->totalFiles] = strdup(path); // Add path as name
                hash->hashString[hash->totalFiles] = strSHA2(path);
                hash->fileSize[hash->totalFiles] = buffer.st_size;
                hash->totalFileSize += buffer.st_size;

                //printf("\nFILE NAME: \t%s\n", dp->d_name);
                //printf("HASH: \t\t%s\n", hash->hashString[hash->totalFiles]);
                //printf("PATH: \t\t%s\n", path);
                //printf("Size: %li\n", buffer.st_size);

                hash->totalFiles++;
                //printf("Files found so far: %i\n", hash->totalFiles);

            }

            findFilesRecursive(path, hash);

        } else if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && hash->aFlag == true) {

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            if (dp->d_type != 4) { // Not a directory

                int status = stat(path, &buffer); //To find size of file
                if (status != 0) {
                    perror("ERROR: ");
                }

                hash->fileName[hash->totalFiles] = strdup(path); // Add path as name // Add a CHECKALLOC after this
                hash->hashString[hash->totalFiles] = strSHA2(path);
                hash->fileSize[hash->totalFiles] = buffer.st_size;
                hash->totalFileSize += buffer.st_size;

                //printf("\nFILE NAME: \t%s\n", dp->d_name);
                //printf("HASH: \t\t%s\n", hash->hashString[hash->totalFiles]);
                //printf("PATH: \t\t%s\n", path);
                //printf("Size: %liMBs\n", buffer.st_size/1000000);

                hash->totalFiles++;
                //printf("Files found so far: %i\n", hash->totalFiles);

            }

            findFilesRecursive(path, hash);
        }
    }

    closedir(dir);

}