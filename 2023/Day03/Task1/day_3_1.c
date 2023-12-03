#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_LENGTH 141
#define MAX_NUMBER_LENGTH 3
#define IS_SYMBOL(c) ((c) > 32 && (c) < 46)
#define IS_NUMBER(n) ((n) > 47 && (n) < 58)

//extra function for 2 line check

char *empty_array(char *current_number){
    for(int i = 0; i < 3; i++){
        current_number[i] = '\0';
    }
    return current_number;
}

char *get_number(char *line, char *current_number, int line_index){
    for(int i = 0; i < MAX_NUMBER_LENGTH; i++){
        if(!IS_NUMBER(line[(line_index+i)])){
            return current_number;
        }
        current_number[i] = line[(line_index+i)];
    }
    return current_number;
}

int task_1(char *line_before, char *line_current, char *line_after){
    int sum = 0;
    int current_symbol_index = 0;
    char *current_number = (char*)calloc((MAX_NUMBER_LENGTH +1), sizeof(char));
    int current_number_int = -1;
    int current_number_index = 0;
    int current_number_length = 0;
    current_number[3] = '\0';
    //beginning
    if(line_before == NULL){
        //call function for 2 line check
        return 0;
    //end
    }else if(line_after == NULL) {
        //call function for 2 line check
        return 0;
    //rest
    }else{
        for(int i = 0; i < LINE_LENGTH; i++){
            if(line_after[i] == '.' && line_current[i] == '.' && line_after[i] == '.'){
                continue;           
            }if(IS_SYMBOL(line_before[i]) || IS_SYMBOL(line_current[i]) || IS_SYMBOL(line_after[i])) {
                current_symbol_index = i;
            }if(current_number_length == 0 && IS_NUMBER(line_current[i])){
                current_number = get_number(line_current, current_number, i);
                current_number_length = strlen(current_number);
                current_number_index = i;
                sscanf(current_number, "%d", &current_number_int);
            }if((current_number_int + current_number_length) < current_symbol_index){
                current_number = empty_array(current_number);
                current_number_length = 0;
                current_number_int = -1;
            }if((current_number_index-1) <= current_symbol_index && (current_number_index + current_number_length) >= current_symbol_index && current_number_int != -1){
                sum += current_number_int;
                i = (i+(current_number_index-i)+current_number_length)-1;
                current_number = empty_array(current_number);
                current_number_length = 0;
                current_number_int = -1;
            }
        }
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

    int size_of_lines = 0;

    char *line_before = NULL;
    char *line_current = NULL;
    char *line_after = NULL;

    int sum = 0;
    while(getline(&line, &len, file) != -1) {
        if(line_current == NULL) {
            line_current = strdup(line);
            continue;
        }else if(line_before == NULL && line_after == NULL){
            line_after = strdup(line);
            sum += task_1(line_before, line_current, line_after);
            continue;
        }else{
            line_before = strdup(line_current);
            line_current = strdup(line_after);
            line_after = strdup(line);
            sum += task_1(line_before, line_current, line_after);
        }
        printf("%s", line);
        
    }

    line_before = line_current;
    line_current = line_after;
    line_after = NULL;
    task_1(line_before, line_current, line_after);

    printf("%d\n", sum);

    fclose(file);
    free(line);

    return 0;
}