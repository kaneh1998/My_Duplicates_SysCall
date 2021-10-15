#include <stdio.h>

// Process files - generate hash
// add size etc...
// Check for dup files here

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "duplicates.h"

/*
 * Checks the hash of the given file
 * and also will check for duplicates
 * given that the file is not the same
 * and it is not checking the parent or
 * child directories together.
 */

int checkHash(HASH_LIST *hash) {

    printf("\nGot into check hash\n");

    int duplicates = 0;
    hash->duplicateSize = 0;

    hash->totalDuplicates = 0;

    printf("total files: %i\n", hash->totalFiles);

    for (int i = 0; i < hash->totalFiles; i++) {

        for (int j = i + 1; j < hash->totalFiles; j++) {
            //printf("CHECKING .. %s   VS   %s\n", hash->hashString[i], hash->hashString[j]);
            //printf("CHECKING .. %i   VS   %i\n", i, j);
            if (strcmp(hash->hashString[i], hash->hashString[j]) == 0) {
                if (i == j) {
                    continue;
                } else if ((strcmp(hash->fileName[i], ".") == 0) || (strcmp(hash->fileName[i], "..") == 0)) {
                    continue;
                } else if ((hash->isDirect[i] == 1) || (hash->isDirect[j] == 1)) {
                    continue;
                } else {
                    printf("Duplicate file found\n");
                    printf("NAME 1: %s  VS NAME 2: %s\n", hash->fileName[i], hash->fileName[j]);
                    printf("SIZE 1: %d  VS SIZE 2: %d\n", hash->fileSize[i], hash->fileSize[j]);

                    hash->totalDuplicates++;

                    hash->duplicateSize += hash->fileSize[i];

                    duplicates++;
                }
            }
        }
    }

    printf("End of duplicates function\n");

    return duplicates;
}

void getStatistics(HASH_LIST *hash){

    printf("Duplciate size: %i\n", hash->duplicateSize);
    
    printf("\nNumber of files: \t%i\n", hash->totalFiles);
    printf("Total Bytes: \t\t%i Bytes\n", hash->totalFileSize);
    printf("Total unique files: \t%i\n", hash->totalFiles - hash->totalDuplicates);
    printf("Minimum total size: \t%i Bytes\n", hash->totalFileSize - hash->duplicateSize);

}