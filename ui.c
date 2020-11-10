#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "commands.h"
#include "ui.h"

#define BUFFER_SIZE 64

void ui_display_prompt()
{
    char* buf;
    buf = cmd_get_login();
    printf("%s:", buf);
    buf = cmd_getcwd();
    printf("%s ?? ", buf);
    free(buf);
}

char* ui_get_input()
{
    char* lineptr = malloc(1);
    size_t bufsize = 0;
    getline(&lineptr, &bufsize, stdin);
    return lineptr;
}

arr2D ui_seperate_args(char* input_line)
{
    arr2D args_struct;
    int buff_size = BUFFER_SIZE;
    char** args = malloc(1*sizeof(char*));
    char* buff_string = malloc(buff_size*sizeof(char));
    int input_length = strlen(input_line);
    int arg_no = 0;
    

    if (input_length == 1 && input_line[0] == '\n')
        {
            free(buff_string);
            args_struct.array = args;
            args_struct.no_rows = arg_no;
            return args_struct;
        }

    buff_string[0] = '\0';
    for (int i = 0; i < input_length; ++i)
    {
        if (isspace(input_line[i]))
        {
            if (strlen(buff_string) != 0)
            {
                // If a whitspace char occurs and the buff_string contains an argument, add it to the args list
                ++arg_no;
                args = realloc(args, arg_no*sizeof(char*));
                args[arg_no-1] = malloc(buff_size*sizeof(char));
                strcpy(args[arg_no-1], buff_string);
                buff_string[0] = '\0';
            }
        } else {
            if (strlen(buff_string) + 2 > buff_size) // +2 for Null-terminating char and new char 
            {
                // If the argument is longer then the buffer size, increase by 10
                buff_string = realloc(buff_string, buff_size+BUFFER_SIZE * sizeof(char));
                buff_size += BUFFER_SIZE;
            }
            strncat(buff_string, &input_line[i], 1); // Copy single non-whitespace char to the buffer 
        }
    }

    free(buff_string);
    // Pass the pointer to the 2D array along with the number of elements
    args_struct.array = args;
    args_struct.no_rows = arg_no;
    return args_struct;
}

void ui_display_text(char* text)
{
    printf("%s\n", text);
}

void ui_free_array2D(arr2D arr)
{
    for (int i = 0; i < arr.no_rows; ++i)
    {
        free(arr.array[i]);
    }
}
