#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // Include the header for ssize_t

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Failed to open the file.\n");
        return 1;
    }

    char *line = NULL;
    size_t line_length = 0;


        while ((_getwline(&line, &line_length, file)) != -1) {
            // Process the line here
            printf("%s", line);
    }

    free(line);
    fclose(file);
    return 0;
}
