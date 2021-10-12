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


int main(int argc, char *argv[])
{
   
    char name[100000]; 
    strcpy(name, argv[1]);


    myfilerecursive(name);

    return 0;
}

void myfilerecursive(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    struct stat buffer;
   
    if (!dir) {
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {


        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.') // Skips hidden folders with '.'
        {

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name); // Building new path for recursive finding of files + directories

            if (dp->d_type != DT_DIR) {

                printf("%s\n", dp->d_name);

                printf("PATH: %s\n", path);

                int status = stat(path, &buffer);

                if (status != 0) {
                    perror("ERROR: ");
                    exit(EXIT_FAILURE);
                }

                printf("Size: %li\n", buffer.st_size);

            }

            myfilerecursive(path);
        }
    }

    closedir(dir);

}