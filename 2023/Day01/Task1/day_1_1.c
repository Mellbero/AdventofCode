#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    if(file == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;

    int sum = 0;
    while(getline(&line, &len, file) != -1) {
        //printf("%s %ld\n", line, len);
        //printf("%c\n", line[1]);
        int i = 0;
        char first = '\0';
        char last = '\0';
        while(line[i] != '\0'){
            if((line[i] >= '0') && (line[i] <= '9')){
                if(first == '\0'){
                    first = line[i];
                    last = line[i];
                }else{
                    last = line[i];
                }
            }
            i++;
        }
        char combined[3] = {first, last, '\0'};
        int combined_integer = 0;
        sscanf(combined, "%d", &combined_integer);
        sum += combined_integer;
    }

    printf("%d\n", sum);

    fclose(file);
    free(line);

    return 0;
}