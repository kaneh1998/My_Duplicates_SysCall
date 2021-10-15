#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#if defined(__linux__)
extern char *strdup(char *string);
#endif

// DECLARE GLOBAL PREPROCESSOR CONSTANTS

#define MAX_MEM      100000

// DEFINE GLOBAL DATA TYPES

typedef struct { // Must dynamiccaly locate memory here

    char *hashString[MAX_MEM]; // Hash of file
    char *fileName[MAX_MEM];   // File name
    char *wantedHash[MAX_MEM]; // Wanted file hash
    char *wantedFile[MAX_MEM]; // Wanted file name/path
    char *alreadySeen[MAX_MEM]; // Already seen hashes
    uint64_t fileSize[MAX_MEM];     // File size
    uint64_t totalFileSize;       // File size after all files counted
    uint64_t totalFiles;          // Total number of files
    uint64_t duplicateSize;       // Size of all duplicates
    uint64_t totalDuplicates;     // Total number of duplicates found
    bool aFlag;
    bool fFlag;
    bool hFlag;
    bool lFlag;
    bool mFlag;
    bool qFlag;

} HASH_LIST;

// DEFINE GLOBAL FUNCTIONS

extern void getStatistics(HASH_LIST *);

extern void findDuplicateFiles(HASH_LIST *);

extern void findFilesRecursive(char[], HASH_LIST *);

extern	char *strSHA2(char *);

// DECLARE GLOBAL FUNCTIONS

// extern int       readmark(FILE *);
// extern void      correlation(int); // note parameters are not named in header files

// DECLARE GLOBAL VARIABLES

// extern double    projmarks[]; // note array size not provided in header
