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

int COUNTER = 0;

typedef struct {

    char *fileName[5000];

} HASH_LIST;

void myfilerecursive(char *path, HASH_LIST *hash, char **fileArray);

int main(int argc, char *argv[]) {
   
    char name[100000]; 

    char *FileNames[5000];

    HASH_LIST hash;
    HASH_LIST *ptrHash;
    ptrHash = &hash;

    

    strcpy(name, argv[1]);


    myfilerecursive(name, ptrHash, FileNames);


    printf("File 0: %s\n", hash.fileName[0]);

    printf("filde: %s\n", FileNames[0]);


    exit(0);

}

void myfilerecursive(char *basePath, HASH_LIST *hash, char **fileArray) {

    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
   
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL) 
    {

        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.') { // Check files are not "." or ".." + checks for hidden files - hidden files must be a toggle option

            if (dp->d_type == DT_DIR) {

                strcpy(path, basePath);
                strcat(path, "/");
                strcat(path, dp->d_name);

            } else { // Prints file names
                
                printf("%s\n", dp->d_name);
                hash->fileName[COUNTER] = dp->d_name;
                fileArray[COUNTER] = dp->d_name;
                printf("file: %s\n", hash->fileName[0]);
                printf("file: %s\n", fileArray[COUNTER]);
                printf("Hello\n");

                struct stat buffer;

                int status = stat(dp->d_name, &buffer);

                if (status != 0) {
                    perror("ERROR: ");
                    exit(EXIT_FAILURE);
                }

                printf("Size: %lli\n", buffer.st_size);

                printf("Hello\n");

            }

            COUNTER++;

            myfilerecursive(path, hash, fileArray);

        }

    }

    closedir(dir);
}