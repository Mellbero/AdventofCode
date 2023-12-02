#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COLOR_AMMOUNT 3

char *get_game_number_and_cubes(char *line, int *game_number_int){
    char *game = (char*)calloc(10, sizeof(char));
    char *game_number = (char*)calloc(4, sizeof(char));
    char *cubes = (char*)calloc((strlen(line)+1), sizeof(char));
    char game_delim[2] = ":";
    char *temp_line = strdup(line);
    char *tmp_game = strtok(temp_line, game_delim);
    strcpy(game, tmp_game);
    char *tmp_cubes = strtok(NULL, game_delim);
    strcpy(cubes, tmp_cubes);
    strcpy(game_number, &(game[5]));
    sscanf(game_number, "%d", game_number_int);
    free(game);
    free(temp_line);
    free(game_number);
    return cubes;
}

int search_through_colours(char *cubes){
    char *colours[COLOR_AMMOUNT] = {"red", "green", "blue"};
    //int colour_ammount[3] = {12, 13, 14};
    int max_colors[3] = {0, 0, 0};
    for(int colour_i = 0; colour_i < COLOR_AMMOUNT; colour_i++){
        char *cubes_copy = strdup(cubes);
        char *p_remind = cubes_copy;
        do{
            char cube_ammount[4];
            char *rest = strstr(cubes_copy, colours[colour_i]);
            if(rest == NULL){
                break;
            }
            int front_index = (rest - cubes_copy)-3;
            cube_ammount[0] = cubes_copy[front_index]; cube_ammount[1] = cubes_copy[front_index+1]; cube_ammount[2] = cubes_copy[front_index+2]; cube_ammount[3] = '\0';
            int cube_ammount_int = 0;
            sscanf(cube_ammount, "%d", &cube_ammount_int);
            if(cube_ammount_int > max_colors[colour_i]){
                max_colors[colour_i] = cube_ammount_int;
            }
            cubes_copy = rest + strlen(colours[colour_i]) +1;
        }while(cubes_copy != NULL);
        free(p_remind);
    }
    return (max_colors[0]*max_colors[1]*max_colors[2]);
}

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
        
        //printf("%s", line);
        int game = 0;
        char *cubes = get_game_number_and_cubes(line, &game);
        //printf("%d\n", game);
        //printf("%s\n", cubes);

        int power = search_through_colours(cubes);

        sum += power;

        free(cubes);
        
    }
    printf("%d\n", sum);

    fclose(file);
    free(line);

    return 0;
}