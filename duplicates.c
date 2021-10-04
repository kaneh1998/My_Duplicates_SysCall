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


void getStats(char dirName[]) {

    //time_t curtime;
    //struct tm *tm;

    int i = 0;
    char *hashVals[500];

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

        //tm = localtime(&buffer.st_mtime);

        printf("size: %ld ", buffer.st_size);

        hashVals[i] = strSHA2(dirp->d_name);

        printf("HASH: %s\n", hashVals[i]);

        i++;

        //char datestring[256];

        //strftime(datestring, sizeof(datestring), NULL, tm);

        printf(" \t%s\n", dirp->d_name);

    }

    closedir(dp);

}

int main(int argc, char *argv[]) {

    char dirName[2000];

    strcpy(dirName, argv[1]);

    getStats(dirName);

    exit(EXIT_SUCCESS);
}