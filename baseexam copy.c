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


int main()
{
   
    char name[100000]; 
    printf("Enter path to list files: ");
    scanf("%s", name);

    myfilerecursive(name);

    return 0;
}

void myfilerecursive(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

   
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.') // Skips hidden folders with '.'
        {
            if (dp->d_type != DT_DIR) {
                printf("%s\n", dp->d_name);
            }
            
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            myfilerecursive(path);
        }
    }

    closedir(dir);
}