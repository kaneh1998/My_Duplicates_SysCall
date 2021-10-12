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

void myfilerecursive(char *path);


int main(int argc, char *argv[]) {
   
    char name[100000]; 

    strcpy(name, argv[1]);

    myfilerecursive(name);

    exit(0);

}

void myfilerecursive(char *basePath) {

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
                printf("Hello\n");

                struct stat buffer;

                int status = stat(dp->d_name, &buffer);

                if (status != 0) {
                    perror("ERROR: ");
                    exit(EXIT_FAILURE);
                }

                printf("Size: %i\n", buffer.st_size);

                printf("Hello\n");

            }

            if (path != NULL) {
                printf("\nChanging directories: %s\n", basePath);
            }

            myfilerecursive(path);

        }

    }

    closedir(dir);
}