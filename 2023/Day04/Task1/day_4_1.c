#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define START_OF_WIN_NUMBERS 10
#define END_OF_WIN_NUMEBRS 40
#define START_OF_MYNUMBERS 42
#define IS_NUMBER(n) ((n) > 47 && (n) < 58)

struct numbers{
    int win_numbers[10];
    int my_numbers[25];
    int ammount_of_matches;
    int copies;
};

char *empty_array(char *tmp){
    for(int i = 0; i < 3; i++){
        tmp[i] = '\0';
    }
    return tmp;
}

int task_1(char **cards){
    struct numbers *numbers = (struct numbers*)calloc(223, sizeof(struct numbers));
    char *tmp = (char*)calloc(3, sizeof(char));
    for(int cards_i = 0; cards_i < 223; cards_i++){
        int win_numbers[10];
        tmp= empty_array(tmp);
        int o  = 0;
        int p = 0;
        for(int i = START_OF_WIN_NUMBERS; i < END_OF_WIN_NUMEBRS; i++){
            if(!IS_NUMBER(cards[cards_i][i]) && strlen(tmp) != 0){
                sscanf(tmp, "%d", &win_numbers[p]);
                tmp= empty_array(tmp);
                p++;
                o = 0;
                continue;
            }
            tmp[o] = cards[cards_i][i];
            o++;
        }

        int my_numbers[25];
        tmp= empty_array(tmp);
        o = 0;
        p = 0;
        for(int i = START_OF_MYNUMBERS; i < strlen(cards[cards_i]); i++){
            if(!IS_NUMBER(cards[cards_i][i]) && strlen(tmp) != 0){
                sscanf(tmp, "%d", &my_numbers[p]);
                tmp= empty_array(tmp);
                p++;
                o = 0;
                continue;
            }
            tmp[o] = cards[cards_i][i];
            o++;
        }
        for(int k = 0; k < 10; k++){
            numbers[cards_i].win_numbers[k] = win_numbers[k];

        }
        for(int l = 0; l < 25; l++){
            numbers[cards_i].my_numbers[l] = my_numbers[l];
        }
        numbers[cards_i].ammount_of_matches = 0;
        numbers[cards_i].copies = 1;
    }

    for(int numbers_i = 0; numbers_i < 223; numbers_i++){
        for(int win_number_i = 0; win_number_i < 10; win_number_i++){
            for(int my_number_i = 0; my_number_i < 25; my_number_i++){
                if(numbers[numbers_i].win_numbers[win_number_i] == numbers[numbers_i].my_numbers[my_number_i]){
                    numbers[numbers_i].ammount_of_matches += 1;
                }
            }
        }
        for(int matches_i = 0; matches_i < numbers[numbers_i].ammount_of_matches; matches_i++){
            numbers[numbers_i+matches_i+1].copies += (numbers[numbers_i].copies);
        }
    }
    int sum = 0;
    for(int numbers_final_i = 0; numbers_final_i < 223; numbers_final_i++){
        sum += numbers[numbers_final_i].copies;
    }
    return sum;
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
    int i = 0;
    char **cards = (char**)malloc(224*sizeof(char*));
    cards[223] = '\0';
    while(getline(&line, &len, file) != -1) {
        cards[i] = strdup(line);
        i++;
        //printf("%s", line);
        
    }
    sum = task_1(cards);

    printf("%d\n", sum);

    fclose(file);
    free(line);

    return 0;
}