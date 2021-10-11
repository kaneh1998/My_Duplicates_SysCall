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

#define OPTLIST "aAfhlmq:"


int main(int argc, char *argv[]) {

    char path[2000];

    int opt;

    /*
     * Sorts through optional flags
     * to determine what to output
     */
    while ((opt = getopt(argc, argv, OPTLIST)) != -1) {
        switch (opt) {
            case 'a':
                printf("Consider all hidden & default '.' files in count \n");
                break;
            case 'A':
                printf("Advanced option \n");
                break;
            case 'f':
                printf("Check if file has duplicates\n");
                printf("Lists relative pathnames of all files whose SHA2 matches indicated file\n");
                printf("Name of file is not listed and terminates with EXIT_SUCCESS if any matching files are found\n");
                printf("EXIT_FAILIURE if no duplicates found\n");
                break;
            case 'h':
                printf("Find and list relative pathnames of all files with the hash provided\n");
                printf("terminates with EXIT_SUCCESS if any matching files are found\n");
                printf("EXIT_FAILIURE if no duplicates found\n");
                break;
            case 'l':
                printf("List all duplicate files found\n");
                printf("Output consists of relative pathnames of two or more files that are duplicates of eachother\n");
                printf("Pathnames of dup files must be seperated by TAB character\n");
                break;
            case 'm':
                printf("minimise total bytes required to store all files' data by moddifying directory structure\n");
                break;
            case 'q':
                printf("No output. \nExit success if no duplciates. or exit failure otherwise\n");
                break;
            default:
                printf("we here\n");
                break;
        }

    }

    for (; optind < argc; optind++) {
        strcpy(path, argv[optind]);
        printf("Extras: %s\n", argv[optind]);
        printf("Path: %s\n", path);
    }

    if (argc == 1) {
        printf("HERE argc == 1\n");
        printf("argc is 1 -- no options or foldder name given\n");
        strcpy(path, ".");
        getStats(path);
    } else {
        printf("HERE argc != 1\n");
        printf("path: %s\n", path);

        getStats(path);
    }

    printf("HERE NOW\n");

    exit(EXIT_SUCCESS);
}
