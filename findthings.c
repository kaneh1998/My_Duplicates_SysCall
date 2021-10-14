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

void findFilesRecursive(char *basePath, HASH_LIST *hash, char **testArray)
{
    char path[10000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    struct stat buffer;

   
    if (!dir) {
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        printf("PATH: %s\n", path);
        printf("BASEPATH: %s\n", basePath);
        printf("\nFILE NAME: \t%s\n", dp->d_name);

        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.' && hash->aFlag == false) {
        // Skips hidden folders with '.'

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name); // Building new path for recursive finding of files + directories

            if (dp->d_type != 4) {

                printf("\nFILE NAME: \t%s\n", dp->d_name);
                hash->fileName[hash->totalFiles] = dp->d_name;
                testArray[hash->totalFiles] = dp->d_name;
                hash->hashString[hash->totalFiles] = strSHA2(path);
                printf("HASH: \t\t%s\n", hash->hashString[hash->totalFiles]);

                printf("PATH: \t\t%s\n", path);

                int status = stat(path, &buffer);

                if (status != 0) {
                    perror("ERROR: ");
                    exit(EXIT_FAILURE);
                }

                printf("Size: %li\n", buffer.st_size);
                hash->fileSize[hash->totalFiles] = buffer.st_size;
                hash->totalFileSize += buffer.st_size;
                hash->totalFiles += 1;
                printf("Files found so far: %i\n", hash->totalFiles);
                printf("File 1 name: %s\n", hash->fileName[0]);

            }

            if (hash->fileName[hash->totalFiles] != NULL) { // NULL when directory is encountered 
                printf("File name from hash table: %s\n\n", hash->fileName[hash->totalFiles]);
            }

            /*for (int i = 0; i < hash->totalFiles; i++) {
                for (int j = 0; j < hash->totalFiles; j++) {
                    printf("%i\n", j);
                    if (strcmp(hash->hashString[i], hash->hashString[j]) == 0 && i != j) {
                        printf("FOUND DUPLICATE");
                        printf("file: %s    vs file: %s\n", hash->fileName[i], hash->fileName[j]);
                    }
                }
            }*/

            printf("\nRecursive now up again\n");

            findFilesRecursive(path, hash, testArray);
        }
    }

    closedir(dir);

}