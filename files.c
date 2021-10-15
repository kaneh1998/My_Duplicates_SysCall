#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "duplicates.h"

int findMoreDuplicates(char *checkingHash, char **seenHashArray, int loopNum) {

    int alreadyFound = 0;

    for (int i = 0; i < loopNum; i++) {
        if (strcmp(seenHashArray[i], checkingHash) == 0) {
            alreadyFound++;
            //printf("returning >0\n");
            return alreadyFound;
        }
    }

    //printf("returning 0\n");

    return 0;

}

/*
 * Checks the hash of the given file
 * and also will check for duplicates
 * given that the file is not the same
 * and it is not checking the parent or
 * child directories together.
 */

void findDuplicateFiles(HASH_LIST *hash) {

    char *tempHash[hash->totalFiles];
    int tempHashIndex = 0;
    bool seenFlag = 0;

    for (int i = 0; i < hash->totalFiles; i++) {
        if (seenFlag == 1) {
            printf("\n");
        }
        seenFlag = 0;

        if (hash->hFlag == true || hash->fFlag == true) { // Checks for matching hash with -h or -f option
            //printf("Checking hashes\n");
            if (strcmp(hash->hashString[i], *hash->wantedHash) == 0) {
                printf("%s\n", hash->fileName[i]);
                hash->totalDuplicates++;
            }
        }

        if (i > 0) {
            if ((findMoreDuplicates(hash->hashString[i], tempHash, tempHashIndex)) != 0) {
                continue;
            }
        }

        if (hash->fFlag != true && hash->hFlag != true) { // Doesn't bother running this loop if we are just looking for a matching file or hash

        tempHash[tempHashIndex] = hash->hashString[i];
        //printf("%s\n", tempHash[tempHashIndex]);
        tempHashIndex++;

            for (int j = i + 1; j < hash->totalFiles; j++) {

                if (strcmp(hash->hashString[i], hash->hashString[j]) == 0) {
                    if (i == j) {
                        continue;
                    } else if ((strcmp(hash->fileName[i], ".") == 0) || (strcmp(hash->fileName[i], "..") == 0)) {
                        continue;
                    }  else { // Found a duplicate file

                        hash->totalDuplicates++;

                        hash->duplicateSize += hash->fileSize[i];

                        if (hash->lFlag == true) { // Check for -l option -- If a duplicate has been found, loop once again through files to see if any more are contained and report back
                            if (seenFlag == 0) {
                                printf("%s\t%s", hash->fileName[i], hash->fileName[j]);
                                seenFlag = 1;
                            } else {
                                printf("\t%s", hash->fileName[j]);
                            }
                        }
                    }
                }
            }
        }
    }
}

void getStatistics(HASH_LIST *hash){

    if (hash->qFlag == true && hash->totalDuplicates != 0) { // Check for quiet option (-q)
        exit(EXIT_FAILURE);
    } else if (hash->qFlag == true) {
        return;
    }

    if ((hash->hFlag == true || hash->fFlag == true) && hash->totalDuplicates != 0) { // Check for matching hashes (with -h or -f option)
        printf("Success\n");
        exit(EXIT_SUCCESS);
    } else if (hash->hFlag == true || hash->fFlag == true) {
        exit(EXIT_FAILURE);
    }

    if (hash->lFlag == true) {                              // Check if -l option was used
        return;
    }
    
    // If none of the above options are true -- Output the statistics
    printf("%li\n", hash->totalFiles);
    printf("%li\n", hash->totalFileSize);
    printf("%li\n", hash->totalFiles - hash->totalDuplicates);
    printf("%li", hash->totalFileSize - hash->duplicateSize);

}