#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    // Read lines using POSIX function getline
    // This code won't work on Windows
    char *line = NULL;
    size_t len = 0;

    while(getline(&line, &len, fp) != -1) {
        printf("%c\n", line[3]);
        //printf("%c\n", line[1]);

    }

    fclose(fp);
    free(line);     // getline will resize the input buffer as necessary
                    // the user needs to free the memory when not needed!
}