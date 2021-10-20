#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "duplicates.h"

/*
 * Used to check if we have previously seen
 * the given hash
*/

int findMoreDuplicates(char *checkingHash, char **seenHashArray, int loopNum) {

    int alreadyFound = 0;

    for (int i = 0; i < loopNum; i++) {
        if (strcmp(seenHashArray[i], checkingHash) == 0) {

            alreadyFound++;
            return alreadyFound;

        }
    }

    return 0;

}

/*
 * Checks the hash of all files
 * and also will check for duplicates
 */

void findDuplicateFiles(FILE_LIST *hash) {

    char *tempHash[hash->totalFiles]; // Store already seen hashes
    int tempHashIndex = 0;            // Number of unique hashes / files
    bool seenFlag = 0;                // Used for checking if we have seen the hash already when checking a new file

    for (int i = 0; i < hash->totalFiles; i++) {

        // Used for the -l option, prints new lines for unique duplicates
        if (seenFlag == 1) {
            printf("\n");
        }
        seenFlag = 0;

        // Checks for matching hash with -h or -f option
        if (hash->hFlag == true || hash->fFlag == true) {

            if (strcmp(hash->hashString[i], *hash->wantedHash) == 0) {
                printf("%s\n", hash->fileName[i]);
                hash->totalDuplicates++;
            }
        }

        // Checks for unique hashes after the first hash has been checked
        if (i > 0) {
            if ((findMoreDuplicates(hash->hashString[i], tempHash, tempHashIndex)) != 0) {
                continue;
            }
        }

        // Doesn't bother running this loop if we are just looking for a matching file or hash
        if (hash->fFlag != true && hash->hFlag != true) {

            tempHash[tempHashIndex] = hash->hashString[i];
            tempHashIndex++;

            for (int j = i + 1; j < hash->totalFiles; j++) {

                if (strcmp(hash->hashString[i], hash->hashString[j]) == 0) {

                    // Ignore files that are the same
                    if (i == j) {
                        continue;
                    } else { // Found a duplicate file

                        hash->totalDuplicates++;
                        hash->duplicateSize += hash->fileSize[i];

                        // Check for -l option
                        if (hash->lFlag == true) {
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

/*
 *  Function to help check
 *  inodes we have found so far
 *  If the inode we are checking is found - we have found a hard-link
 *  returns 1 -- otherwise 0
 */

int checkInodeNum(FILE_LIST *hash, int inodeToCheck) {

    for (int i = 0; i < hash->totalFiles; i++) {
        if (inodeToCheck == hash->inodeNum[i]) {
            return 1;
        }
    }

    return 0;

}

/*
 * Prints statistics about the files found
 * depending on options the program is ran with
*/

void getStatistics(FILE_LIST *hash){

    if (hash->qFlag == true && hash->totalDuplicates != 0) { // Check for quiet option (-q)
        exit(EXIT_FAILURE);
    } else if (hash->qFlag == true) {
        return;
    }

    if ((hash->hFlag == true || hash->fFlag == true) && hash->totalDuplicates != 0) { // Check for matching hashes (with -h or -f option)
        exit(EXIT_SUCCESS);
    } else if (hash->hFlag == true || hash->fFlag == true) {
        exit(EXIT_FAILURE);
    }

    if (hash->lFlag == true) {     // Check if -l option was used
        return;
    }
    
    // If none of the above options apply -- Output the statistics
    printf("%llu\n", (unsigned long long)hash->totalFiles);
    printf("%llu\n", (unsigned long long)hash->totalFileSize);
    printf("%llu\n", (unsigned long long)hash->totalFiles - hash->totalDuplicates);
    printf("%llu\n", (unsigned long long)hash->totalFileSize - hash->duplicateSize);

}