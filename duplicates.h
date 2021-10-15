#include <stdio.h>
#include <stdlib.h>

// DEFINE GLOBAL DATA TYPES

typedef struct { // Must dynamiccaly locate memory here

    char *hashString[50000]; // Hash of file
    char *fileName[50000];   // File name
    int fileSize[50000];     // File size
    int totalFileSize;      // File size after all files counted
    int totalFiles;         // Total number of files
    int isDirect[50000];     // Is a directory (bool)
    int duplicateSize;      // Size of all duplicates
    int totalDuplicates;    // Total number of duplicates found
    bool aFlag;
    bool fFlag;
    bool hFlag;
    bool lFlag;
    bool mFlag;
    bool qFlag;

} HASH_LIST;

// DEFINE GLOBAL FUNCTIONS

extern void getStatistics(HASH_LIST *);

extern int checkHash(HASH_LIST *);

extern void findFilesRecursive(char[], HASH_LIST *);

extern	char *strSHA2(char *);

// DECLARE GLOBAL PREPROCESSOR CONSTANTS

// #define MAX      200

// DECLARE GLOBAL FUNCTIONS

// extern int       readmark(FILE *);
// extern void      correlation(int); // note parameters are not named in header files

// DECLARE GLOBAL VARIABLES

// extern double    projmarks[]; // note array size not provided in header
