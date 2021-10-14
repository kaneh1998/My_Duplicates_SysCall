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

void stringFunc(char **charArr) {


    printf("%s\n", charArr[0]);
}


int main(int argc, char **argv) {

    char *colours[500];

    colours[0] = "red";

    //strcpy(colours[0], "red");

    printf("%s\n", colours[0]);
    printf("%s\n", colours[1]);

    stringFunc(colours);

    return 0;
}