//  CITS2002 Project 2 2021
//  Name(s):             Kane Howard
//  Student number(s):   22253494


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

#include "duplicates.h"

typedef struct {

    char *hashString[5000];
    char *fileName[5000];

} HASH_LIST;


int checkHash(HASH_LIST hash) {
    int duplicates = 0;

    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            //printf("CHECKING .. %s   VS   %s\n", hash.hashString[i], hash.hashString[j]);
            //printf("CHECKING .. %i   VS   %i\n", i, j);
            if (strcmp(hash.hashString[i], hash.hashString[j]) == 0) {
                if (i == j) {
                    continue;
                } else {
                    printf("Duplicate file found\n");
                    printf("NAME 1: %s  VS NAME2: %s\n", hash.fileName[i], hash.fileName[j]);
                    duplicates++;
                }
            }
        }
    }

    return duplicates;
}

void getStats(char dirName[]) {

    int numberOfFiles = 0;
    int *numFiles = &numberOfFiles;
    int totalBytes = 0;

    HASH_LIST hash;

    int i = 0;

    DIR *dp;
    struct dirent *dirp;
    int ret2;

    dp = opendir(dirName);

    ret2 = chdir(dirName);
    if (ret2 != 0) {
        perror("Unable to change directory\n");
        exit(EXIT_FAILURE);
    }

    while ((dirp = readdir(dp)) != NULL) {

        struct stat buffer;

        int status = stat(dirp->d_name, &buffer);
        if (status != 0) {
            printf("ERROR\n");
            exit(EXIT_FAILURE);
        }
        numberOfFiles++;

        //tm = localtime(&buffer.st_mtime);

        printf("size: %ld ", buffer.st_size);
        totalBytes += buffer.st_size;


        hash.hashString[i] = strSHA2(dirp->d_name);
        hash.fileName[i] = dirp->d_name;

        printf("HASH: %s\n", hash.hashString[i]);
        printf("NAME FILE: %s\n", hash.fileName[i]);

        i++;

        //char datestring[256];

        //strftime(datestring, sizeof(datestring), NULL, tm);

        printf(" \t%s\n", dirp->d_name);

    }

    closedir(dp);

    int dups = checkHash(hash);
    int duplicateSize = 500;

    printf("Number of files: %i\n", *numFiles);
    printf("Total Bytes: %i\n", totalBytes);
    printf("Total unique files: %i\n", *numFiles - dups);
    printf("Minimum total size: %i\n", totalBytes - duplicateSize);

}

int main(int argc, char *argv[]) {

    char dirName[2000];

    strcpy(dirName, argv[1]);

    getStats(dirName);

    exit(EXIT_SUCCESS);
}