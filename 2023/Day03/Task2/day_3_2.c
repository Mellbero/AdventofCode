#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_LENGTH 140
#define MAX_NUMBER_LENGTH 3
#define IS_SYMBOL(c) (c == 42)
#define IS_NUMBER(n) ((n) > 47 && (n) < 58)

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

bool is_adjacent(int current_symbol_index, int current_number_index, int current_number_length, int current_number_int){
    if((current_number_index-1) <= current_symbol_index && (current_number_index + current_number_length) >= current_symbol_index && current_number_int != -1 && current_symbol_index != -1){
        return true;
    }else{
        return false;
    }
}

int task_2(char *line_before, char *line_current, char *line_after){
    int sum = 0;
    int current_symbol_index = -1;
    char *current_number = (char*)calloc((MAX_NUMBER_LENGTH +1), sizeof(char));
    int current_number_int = -1;
    int current_number_index = 0;
    int current_number_length = 0;
    bool current_number_is_adjacent_current_symbol = false;
    current_number[3] = '\0';
    char *current_2_number = (char*)calloc((MAX_NUMBER_LENGTH +1), sizeof(char));
    int current_2_number_int = -1;
    current_2_number[3] = '\0';
    char *before_number = (char*)calloc((MAX_NUMBER_LENGTH +1), sizeof(char));
    int before_number_int = -1;
    int before_number_index = 0;
    int before_number_length = 0;
    bool before_number_is_adjacent_current_symbol = false;
    current_number[3] = '\0';
    char *before_2_number = (char*)calloc((MAX_NUMBER_LENGTH +1), sizeof(char));
    int before_2_number_int = -1;
    current_2_number[3] = '\0';
    char *after_number = (char*)calloc((MAX_NUMBER_LENGTH +1), sizeof(char));
    int after_number_int = -1;
    int after_number_index = 0;
    int after_number_length = 0;
    bool after_number_is_adjacent_current_symbol = false;
    current_number[3] = '\0';
    char *after_2_number = (char*)calloc((MAX_NUMBER_LENGTH +1), sizeof(char));
    int after_2_number_int = -1;
    current_2_number[3] = '\0';
    //beginning
    for(int i = 0; i < LINE_LENGTH; i++){
        if(line_after == NULL || line_before == NULL){
            return 0;
        }
        if(IS_SYMBOL(line_current[i])) {
            current_symbol_index = i;
        }
        if(current_number_length == 0 && IS_NUMBER(line_current[i])){
            current_number = get_number(line_current, current_number, i);
            current_number_length = strlen(current_number);
            current_number_index = i;
            sscanf(current_number, "%d", &current_number_int);
            if((current_number_length +1 + current_number_index) < LINE_LENGTH && IS_NUMBER(line_current[(current_number_length +1 + current_number_index)]) && (IS_SYMBOL(line_current[(current_number_length + current_number_index)]))){
                current_2_number = get_number(line_current, current_2_number, (current_number_length +1 + current_number_index));
                sscanf(current_2_number, "%d", &current_2_number_int);
                sum += (current_2_number_int*current_number_int);
                current_2_number = empty_array(current_2_number);
                current_2_number_int = -1;
            }
            if((current_number_length +1 + current_number_index) < LINE_LENGTH && IS_NUMBER(line_before[(current_number_length +1 + current_number_index)]) && !IS_NUMBER(line_before[(current_number_length + current_number_index)]) && (IS_SYMBOL(line_current[(current_number_length + current_number_index)]))){
                before_2_number = get_number(line_before, before_2_number, (current_number_length +1 + current_number_index));
                sscanf(before_2_number, "%d", &before_2_number_int);
                sum += (before_2_number_int*current_number_int);
                before_2_number = empty_array(before_2_number);
                before_2_number_int = -1;
            }
            if((current_number_length +1 + current_number_index) < LINE_LENGTH && IS_NUMBER(line_after[(current_number_length +1 + current_number_index)]) && !IS_NUMBER(line_after[(current_number_length + current_number_index)]) && (IS_SYMBOL(line_current[(current_number_length + current_number_index)]))){
                after_2_number = get_number(line_after, after_2_number, (current_number_length +1 + current_number_index));
                sscanf(after_2_number, "%d", &after_2_number_int);
                sum += (after_2_number_int*current_number_int);
                after_2_number = empty_array(after_2_number);
                after_2_number_int = -1;
            }
        }
        if(before_number_length == 0 && IS_NUMBER(line_before[i])){
            before_number = get_number(line_before, before_number, i);
            before_number_length = strlen(before_number);
            before_number_index = i;
            sscanf(before_number, "%d", &before_number_int);
            if((before_number_length +1 + before_number_index) < LINE_LENGTH && IS_NUMBER(line_before[(before_number_length +1 + before_number_index)]) && (IS_SYMBOL(line_current[(before_number_length + before_number_index)]))){
                before_2_number = get_number(line_before, before_2_number, (before_number_length +1 + before_number_index));
                sscanf(before_2_number, "%d", &before_2_number_int);
                sum += (before_2_number_int*before_number_int);
                before_2_number = empty_array(before_2_number);
                before_2_number_int = -1;
            }
            if((before_number_length +1 + before_number_index) < LINE_LENGTH && IS_NUMBER(line_after[(before_number_length +1 + before_number_index)]) && !IS_NUMBER(line_after[(before_number_length + before_number_index)]) && (IS_SYMBOL(line_current[(before_number_length + before_number_index)]))){
                after_2_number = get_number(line_after, after_2_number, (before_number_length +1 + before_number_index));
                sscanf(after_2_number, "%d", &after_2_number_int);
                sum += (after_2_number_int*before_number_int);
                after_2_number = empty_array(after_2_number);
                after_2_number_int = -1;
            }
            if((before_number_length +1 + before_number_index) < LINE_LENGTH && IS_NUMBER(line_current[(before_number_length +1 + before_number_index)]) && !IS_NUMBER(line_current[(before_number_length + before_number_index)]) && (IS_SYMBOL(line_current[(before_number_length + before_number_index)]))){
                current_2_number = get_number(line_current, current_2_number, (before_number_length +1 + before_number_index));
                sscanf(current_2_number, "%d", &current_2_number_int);
                sum += (current_2_number_int*before_number_int);
                current_2_number = empty_array(current_2_number);
                current_2_number_int = -1;
            }
        }
        if(after_number_length == 0 && IS_NUMBER(line_after[i])){
            after_number = get_number(line_after, after_number, i);
            after_number_length = strlen(after_number);
            after_number_index = i;
            sscanf(after_number, "%d", &after_number_int);
            if((after_number_length +1 + after_number_index) < LINE_LENGTH && IS_NUMBER(line_after[(after_number_length +1 + after_number_index)]) && (IS_SYMBOL(line_current[(after_number_length + after_number_index)]))){
                after_2_number = get_number(line_after, after_2_number, (after_number_length +1 + after_number_index));
                sscanf(after_2_number, "%d", &after_2_number_int);
                sum += (after_2_number_int*after_number_int);
                after_2_number = empty_array(after_2_number);
                after_2_number_int = -1;
            }
            if((after_number_length +1 + after_number_index) < LINE_LENGTH && IS_NUMBER(line_before[(after_number_length +1 + after_number_index)]) && !IS_NUMBER(line_before[(after_number_length + after_number_index)]) && (IS_SYMBOL(line_current[(after_number_length + after_number_index)]))){
                before_2_number = get_number(line_before, before_2_number, (after_number_length +1 + after_number_index));
                sscanf(before_2_number, "%d", &before_2_number_int);
                sum += (before_2_number_int*after_number_int);
                before_2_number = empty_array(before_2_number);
                before_2_number_int = -1;
            }
            if((after_number_length +1 + after_number_index) < LINE_LENGTH && IS_NUMBER(line_current[(after_number_length +1 + after_number_index)]) && !IS_NUMBER(line_current[(after_number_length + after_number_index)]) && (IS_SYMBOL(line_current[(after_number_length + after_number_index)]))){
                current_2_number = get_number(line_current, current_2_number, (after_number_length +1 + after_number_index));
                sscanf(current_2_number, "%d", &current_2_number_int);
                sum += (current_2_number_int*after_number_int);
                current_2_number = empty_array(current_2_number);
                current_2_number_int = -1;
            }
        }

        current_number_is_adjacent_current_symbol = is_adjacent(current_symbol_index, current_number_index, current_number_length, current_number_int);
        before_number_is_adjacent_current_symbol = is_adjacent(current_symbol_index, before_number_index, before_number_length, before_number_int);
        after_number_is_adjacent_current_symbol = is_adjacent(current_symbol_index, after_number_index, after_number_length, after_number_int);

        if(current_number_is_adjacent_current_symbol && before_number_is_adjacent_current_symbol){
            sum += (current_number_int*before_number_int);
            if(current_number_index < before_number_index){
                i = (i+(current_number_index-i)+current_number_length)-1;
                current_number = empty_array(current_number);
                current_number_length = 0;
                current_number_int = -1;
            }else{
                i = (i+(before_number_index-i)+before_number_length)-1;
                before_number = empty_array(before_number);
                before_number_length = 0;
                before_number_int = -1;
            }
        }
        if(current_number_is_adjacent_current_symbol && after_number_is_adjacent_current_symbol){
            sum += (current_number_int*after_number_int);
            if(current_number_index < after_number_index){
                i = (i+(current_number_index-i)+current_number_length)-1;
                current_number = empty_array(current_number);
                current_number_length = 0;
                current_number_int = -1;
            }else{
                i = (i+(after_number_index-i)+after_number_length)-1;
                after_number = empty_array(after_number);
                after_number_length = 0;
                after_number_int = -1;
            }
        }
        if(after_number_is_adjacent_current_symbol && before_number_is_adjacent_current_symbol){
            sum += (before_number_int*after_number_int);
            if(after_number_index < before_number_index){
                i = (i+(after_number_index-i)+after_number_length)-1;
                after_number = empty_array(after_number);
                after_number_length = 0;
                after_number_int = -1;
            }else{
                i = (i+(before_number_index-i)+before_number_length)-1;
                before_number = empty_array(before_number);
                before_number_length = 0;
                before_number_int = -1;
            }
        }
        if(i >= (current_number_index+current_number_length)){
            current_number = empty_array(current_number);
            current_number_length = 0;
            current_number_int = -1;
        }
        if(i >= (before_number_index+before_number_length)){
            before_number = empty_array(before_number);
            before_number_length = 0;
            before_number_int = -1;
        }
        if(i >= (after_number_index+after_number_length)){
            after_number = empty_array(after_number);
            after_number_length = 0;
            after_number_int = -1;
        }
        if(current_number_index-1 == -1){
            if((i >= (current_number_index + current_number_length) && current_number_int != -1)){
                current_number = empty_array(current_number);
                current_number_length = 0;
                current_number_int = -1;
            }
        }
        if(before_number_index-1 == -1){
            if((i >= (before_number_index + before_number_length) && before_number_int != -1)){
                before_number = empty_array(before_number);
                before_number_length = 0;
                before_number_int = -1;
            }
        }
        if(after_number_index-1 == -1){
            if((i >= (after_number_index + after_number_length) && after_number_int != -1)){
                after_number = empty_array(after_number);
                after_number_length = 0;
                after_number_int = -1;
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
            continue;
        }else{
            line_before = strdup(line_current);
            line_current = strdup(line_after);
            line_after = strdup(line);
            sum += task_2(line_before, line_current, line_after);
        }
        printf("%s", line);
        
    }

    line_before = line_current;
    line_current = line_after;
    line_after = NULL;

    printf("%d\n", sum);

    fclose(file);
    free(line);

    return 0;
}