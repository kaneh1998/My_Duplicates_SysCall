//  CITS2002 Project 2 2021
//  Name(s):             Kane Howard
//  Student number(s):   22253494

// Program SUPPORTS: multiple directories being provided + hard links
// Program DOES NOT SUPPORT: -m option

// Assumptions:
// Was not sure how to handle when one or more directories provided are sub-directories of one provided directory
// i.e ./duplicates . ./project
// When directories + sub-directories like this are provided, all files are counted and checked for duplicates 
// Files are doubled up, I guess you could say...

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
                exit(EXIT_SUCCESS);
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

    char *allPaths[1000][1000];     // Holds directories given
    int numberOfDirectories = 0;    // Number of directories given

    for (; optind < argc; optind++) {
        numberOfDirectories++;
        *allPaths[numberOfDirectories] = strdup(argv[optind]);
        CHECK_ALLOC(*allPaths[numberOfDirectories]);
        strcpy(path, argv[optind]);
    }

    // If no directory is provided and no options selected - Just check the current directory
    if (argc == 1) {
        strcpy(path, ".");
        findFilesRecursive(path, ptrHash);

    // Error in option given
    } else if (argc == -1) {
        usage(progName);

    } else {

        // Runs through all directories given
        while (numberOfDirectories != 0) {

            if (access(*allPaths[numberOfDirectories], R_OK) == 0) {
                findFilesRecursive(*allPaths[numberOfDirectories], ptrHash);
            } else {
                fprintf(stderr, "path %s does not exist\n", path);
                exit(EXIT_FAILURE);
            }
            
            numberOfDirectories--;

        }
    }

    findDuplicateFiles(ptrHash);

    getStatistics(ptrHash);

    exit(EXIT_SUCCESS);
}
