#include <stdio.h>
#include <stdlib.h>

typedef struct { // Must dynamiccaly locate memory here

    char *hashString[5000]; // Hash of file
    char *fileName[5000];   // File name
    int fileSize[5000];     // File size
    int totalFileSize;      // File size after all files counted
    int totalFiles;         // Total number of files
    int isDirect[5000];     // Is a directory (bool)
    int duplicateSize;      // Size of all duplicates
    int totalDuplicates;    // Total number of duplicates found

} HASH_LIST;

extern	char *strSHA2(char *);