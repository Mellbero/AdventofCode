#include <stdio.h>
#include <stdlib.h>

#define INITIAL_LINE_LENGTH 128

char *realloc_line(char *line, int *length){
    *length = (*length)*2;
    char *new_line = (char*)realloc(line, sizeof(char)*(*length));
    if(new_line == NULL){
        perror("Failed to realloc new_line");
        exit(1);
    }
    return new_line;
}

char *malloc_line(int length){
    char *new_line = (char*)malloc(sizeof(char)*length)
    if(new_line == NULL){
        perror("Failed to malloc new_line");
        exit(1);
    }
    return new_line;
}

int getline(char *line_out, FILE *file){
    int length = INITIAL_LINE_LENGTH;
    char *line = malloc_line(length);
    
    while(fgets(line, length, file) != NULL){
        
    }
}