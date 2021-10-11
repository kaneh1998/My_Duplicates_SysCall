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

/*
 * Checks if a path to file is a directory or not
 */

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

/*
 * Runs through path and gets
 * various statistics about the files found
 * at each path
 */

void getStats(char path[]) {

    int totalBytes = 0;

    HASH_LIST hash;
    hash.totalFiles = 0;

    int i = 0;

    DIR *dp;
    struct dirent *dirp;
    int ret2;

    dp = opendir(path);

    ret2 = chdir(path);
    if (ret2 != 0) {
        perror("Error: ");
        exit(EXIT_FAILURE);
    }

    while ((dirp = readdir(dp)) != NULL) {

        struct stat buffer;

        int status = stat(dirp->d_name, &buffer);
        if (status != 0) {
            perror("ERROR: ");
            exit(EXIT_FAILURE);
        }

        hash.fileName[i] = dirp->d_name;

        printf("\nNAME OF FILE: \t%s\n", hash.fileName[i]);

        int isDirectoryTF = isDirectory(dirp->d_name); // 1 = Directory && 0 = Not Directory
        printf("is directory? \t%i\n", isDirectoryTF);

        printf("IS DIRECT? : %u\n", dirp->d_type); // Checks if directory
        if (dirp->d_type == 4) {
            if ((strcmp(dirp->d_name, ".") != 0) && (strcmp(dirp->d_name, "..") != 0)) {
                printf("DIRECTORY HIT\n");
                printf("Next path: %s/%s\n", path, dirp->d_name);
                printf("Ghe\n");
                /*char newPath[8] = "";
                printf("Ghed\n");
                strcat(newPath, path);
                printf("Ghefd\n");
                strcat(newPath, "/");
                strcat(newPath, dirp->d_name);
                printf("new path: %s\n", newPath);
                */
                printf("Going to check the %s\n", dirp->d_name);
                getStats(dirp->d_name);
                printf("Back in here\n");
                printf("Going to check %s\n", path);
                getStats(path);
            }
        } else {
            printf("FILE\n");
        }

        if (isDirectoryTF == 1) {
            hash.isDirect[i] = 1;
        } else {
            hash.isDirect[i] = 0;
            hash.totalFiles++;
            hash.totalFileSize += buffer.st_size;
        }


        //printf("Inode #: %hu\n", buffer.st_nlink); // NUM OF LINKS

        printf("size: \t\t%ld Bytes\n", buffer.st_size);
        totalBytes += buffer.st_size;
        hash.fileSize[i] = buffer.st_size;

        hash.hashString[i] = strSHA2(dirp->d_name);

        printf("HASH: \t\t%s\n", hash.hashString[i]);
        printf("Files so far: \t%i\n", hash.totalFiles);

        i++;

    }

    closedir(dp);

    hash.totalDuplicates = checkHash(hash);

    getStatistics(hash);

    printf("Got to end of stats\n");

}