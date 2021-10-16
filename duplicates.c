//  CITS2002 Project 2 2021
//  Name(s):             Kane Howard
//  Student number(s):   22253494

// Process command line options and usage() function


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

#define OPTLIST "aAf:h:lmq"

FILE_LIST hash;

void usage(char *progName) {

    fprintf(stderr, "Usage: %s [options] dirname\n", progName);

    fprintf(stderr, "where options are:\n\n");

    fprintf(stderr, "-a\t\tcheck all files, including hidden\n");

    fprintf(stderr, "-A\t\ttest advanced version\n");

    fprintf(stderr, "-f\t\tcheck for a given filename\n");

    fprintf(stderr, "-h\t\tcheck for a given hash\n");

    fprintf(stderr, "-l\t\tlists all duplicate filenames\n");

    fprintf(stderr, "-q\t\tquietly check files, exiting with no output\n");

    exit(EXIT_FAILURE);

}

int main(int argc, char *argv[]) {

    char *progName = "duplicates";

    char path[50000];
    FILE_LIST *ptrHash = &hash;

    int opt;

    /*
     * Sorts through option flags
     * to determine what to do
     */
    while ((opt = getopt(argc, argv, OPTLIST)) != -1) {
        switch (opt) {
            case 'a':
                ptrHash->aFlag = true;
                break;
            case 'A':
                exit(EXIT_FAILURE);
                break;
            case 'f':
                ptrHash->fFlag = true;
                ptrHash->wantedHash[0] = strSHA2(optarg);

                if (*ptrHash->wantedHash == NULL) {
                    fprintf(stderr, "Illegal file given\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
                ptrHash->hFlag = true;
                ptrHash->wantedHash[0] = optarg;
                break;
            case 'l':
                ptrHash->lFlag = true;
                break;
            case 'm':
                ptrHash->mFlag = true;
                break;
            case 'q':
                ptrHash->qFlag = true;
                break;
            default:
                fprintf(stderr, "%s : illegal option -%c\n", progName, optopt);
                argc = -1;
                break;
        }

    }

    for (; optind < argc; optind++) {
        strcpy(path, argv[optind]);
    }

    if (argc == 1) { // If no directory is provided and no options selected - Just check the current directory
        strcpy(path, ".");
        findFilesRecursive(path, ptrHash);
    } else if (argc == -1) {
        usage(progName);
    } else {
        if (access(path, R_OK) == 0) { // Check we can read the directory
            findFilesRecursive(path, ptrHash);
        } else {
            fprintf(stderr, "path %s does not exist\n", path);
            exit(EXIT_FAILURE);
        }
    }

    findDuplicateFiles(ptrHash);

    getStatistics(ptrHash);

    exit(EXIT_SUCCESS);
}
