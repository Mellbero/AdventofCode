#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPLACE_LIST_LENGTH 9

char *copy_part_of_string(char *line, int line_len, char *str, int from, int to){
    int o = 0;
    for(int i = from; i < to; i++){
        str[o] = line[i];
        o++;
    }
    return str;
}

char *replace_string_with_number(char *in_line){
    int line_len = strlen(in_line);
    char* line = (char*)malloc((line_len+1)*sizeof(char));
    line[0] = '\0';
    strcpy(line, in_line);
    line[line_len] = '\0';

    char* replace_list[9][2] = {
        {"one", "o1e"},
        {"two", "t2o"},
        {"three", "t3ree"},
        {"four", "f4ur"},
        {"five", "f5ve"},
        {"six", "s6x"},
        {"seven", "s7ven"},
        {"eight", "e8ght"},
        {"nine", "n9ne"}
    };

    char *rest = NULL;
    do{
        rest = NULL;
        int rest_len = 0;
        int replace_list_index = 0;
        for(int i = 0; i < REPLACE_LIST_LENGTH; i++){
            char *tmp = NULL;
            int tmp_len = 0;
            tmp = strstr(line, replace_list[i][0]);
            if(tmp != NULL){
                if(rest != NULL){
                    tmp_len = strlen(tmp);
                    if(tmp_len > rest_len){
                        rest = tmp;
                        rest_len = tmp_len;
                        replace_list_index = i;
                    }
                }
                if(rest == NULL){
                    rest = tmp;
                    rest_len = strlen(rest);
                    replace_list_index = i;
                }
            }
        }
        if(rest != NULL){
            int front_index = rest - line;
            int back_index = front_index + strlen(replace_list[replace_list_index][0]);
            int current_line_len = strlen(line);
            char *str1 = (char*)calloc((line_len+1), sizeof(char));
            char *str2 = NULL;
            bool number_front = false;
            str1[0] = '\0';
            if(front_index == 0){
                str1 = copy_part_of_string(line, current_line_len, str1, back_index, current_line_len);
                number_front = true;
            }else if(back_index+1 == current_line_len){
                str1 = copy_part_of_string(line, current_line_len, str1, 0, front_index);
                number_front = false;
            }else{
                str2 = (char*)calloc((line_len+1), sizeof(char));
                str2[0] = '\0';
                str1 = copy_part_of_string(line, current_line_len, str1, 0, front_index);
                str2 = copy_part_of_string(line, current_line_len, str2, back_index, current_line_len);
                number_front = true;
            }
            char *combined = (char*)calloc((line_len+1), sizeof(char));
            combined[0] = '\0';
            if(str2 != NULL){
                strcat(combined, str1);
                strcat(combined, replace_list[replace_list_index][1]);
                strcat(combined, str2);
            }else if(str2 == NULL && number_front){
                strcat(combined, replace_list[replace_list_index][1]);
                strcat(combined, str1);
            }else if(str2 == NULL && !number_front){
                strcat(combined, str1);
                strcat(combined, replace_list[replace_list_index][1]);
            }
            strcpy(line, combined);
            free(combined);
            free(str1);
            free(str2);
        }
    }while(rest != NULL);
    
    return line;
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
        printf("Before: %s\n", line);
        char *new_line = replace_string_with_number(line);
        printf("After: %s\n", new_line);
        int i = 0;
        char first = '\0';
        char last = '\0';
        while(new_line[i] != '\0'){
            if((new_line[i] >= '0') && (new_line[i] <= '9')){
                if(first == '\0'){
                    first = new_line[i];
                    last = new_line[i];
                }else{
                    last = new_line[i];
                }
            }
            i++;
        }
        char combined[3] = {first, last, '\0'};
        int combined_integer = 0;
        sscanf(combined, "%d", &combined_integer);
        printf("%d\n", combined_integer);
        sum += combined_integer;
        free(new_line);
    }

    printf("%d\n", sum);

    fclose(file);
    free(line);

    return 0;
}