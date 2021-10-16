#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#if defined(__linux__)
extern char *strdup(char *string);
#endif

// DECLARE GLOBAL PREPROCESSOR CONSTANTS

#define NUM_FILES      100000

#define CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

// DEFINE GLOBAL DATA TYPES

typedef struct {

    char *hashString[NUM_FILES];      // Hash of file
    char *fileName[NUM_FILES];        // File name / path
    char *wantedHash[NUM_FILES];      // Wanted file hash (with -h option)
    char *wantedFile[NUM_FILES];      // Wanted file name / path (with -f option)
    uint64_t fileSize[NUM_FILES];     // File size
    uint64_t totalFileSize;         // File size after all files counted
    uint64_t totalFiles;            // Total number of files
    uint64_t duplicateSize;         // Size of all duplicates
    uint64_t totalDuplicates;       // Total number of duplicates found
    bool aFlag;                     // Flags to indicate which options were chosen - used throughout program
    bool fFlag;                     // v           v           v           v           v            v
    bool hFlag;
    bool lFlag;
    bool mFlag;
    bool qFlag;

} FILE_LIST;

// DEFINE GLOBAL FUNCTIONS

extern void getStatistics(FILE_LIST *);

extern void findDuplicateFiles(FILE_LIST *);

extern void findFilesRecursive(char[], FILE_LIST *);

extern	char *strSHA2(char *);
