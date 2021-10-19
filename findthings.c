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

void findFilesRecursive(char *basePath, FILE_LIST *hash)
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

        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.' && hash->aFlag == false) {
        // DOES NOT pass files when:
        // -    File name is "." OR ".." OR ".xxxx" OR "aFlag = False" 

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name); // Building new path for recursive finding of files + directories

            if (dp->d_type != 4) { // Check if file is a directory - prevents running stat() on directories

                int status = stat(path, &buffer); //To find size of file
                if (status != 0) {
                    continue;
                }

                // Check if number of hardlinks is >1 && if we have already seen the inode # before
                if (buffer.st_nlink > 1) {
                    if (checkInodeNum(hash, buffer.st_ino) == 1) {  // If we find matching inode - skip this file
                        continue;
                    }
                }

                hash->fileName[hash->totalFiles] = strdup(path);
                CHECK_ALLOC(hash->fileName[hash->totalFiles]);
                hash->hashString[hash->totalFiles] = strSHA2(path);
                hash->fileSize[hash->totalFiles] = buffer.st_size;
                hash->totalFileSize += buffer.st_size;
                hash->inodeNum[hash->totalFiles] = buffer.st_ino;

                hash->totalFiles++;

            }

            findFilesRecursive(path, hash);

        } else if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && hash->aFlag == true) {

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            if (dp->d_type != 4) {

                int status = stat(path, &buffer);
                if (status != 0) {
                    continue;
                }

                // Check if number of hardlinks is >1 && if we have already seen the inode # before
                if (buffer.st_nlink > 1) {
                    if (checkInodeNum(hash, buffer.st_ino) == 1) {  // Loop through all inodes in the struct) {
                        continue;
                    }
                }

                hash->fileName[hash->totalFiles] = strdup(path);
                CHECK_ALLOC(hash->fileName[hash->totalFiles]);
                hash->hashString[hash->totalFiles] = strSHA2(path);
                hash->fileSize[hash->totalFiles] = buffer.st_size;
                hash->totalFileSize += buffer.st_size;
                hash->inodeNum[hash->totalFiles] = buffer.st_ino;

                hash->totalFiles++;

            }

            findFilesRecursive(path, hash);
        }
    }

    closedir(dir);

}