// I/O
#include <stdio.h>
// Memory handling
#include <stdlib.h>

// Type related
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// builtins
#include "commands.h"

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

char** ui_seperate_args(char* input_line)
{
    int buff_size = 50;
    char** args = malloc(1*sizeof(char*));
    char* buff_string = malloc(buff_size*sizeof(char));
    int input_length = strlen(input_line);
    int arg_no = 0;
    
    // DEBUGGING
    printf("Length of input_line: %d\n", input_length);

    for (int i = 0; i < input_length; ++i)
    {
        printf("%d\n", input_line[i]);
    }
    // DEBUGGING END

    if (input_length == 1 && input_line[0] == '\n')
        {
            args[0] = NULL;
            free(buff_string);
            return args;
        }

    buff_string = "";
    for (int i = 0; i < input_length; ++i)
    {
        if (isspace(input_line[i]))
        {
            if (strlen(buff_string) != 0)
            {
                ++arg_no;
                args = realloc(args, arg_no*sizeof(char*));
                args[arg_no-1] = malloc(buff_size*sizeof(char));
                strcpy(args[arg_no-1], buff_string);
                buff_string = "";
            }
        } else {
            if (strlen(buff_string) + 2 > buff_size) // +2 for Null-terminating char and new char 
            {
                buff_string = realloc(buff_string, buff_size+10 * sizeof(char));
                buff_size += 10;
            }
            strncat(buff_string, &input_line[i], 1); // Copy single non-whitespace char to the buffer 
        }
    }
    free(buff_string);
    return args;
}

void ui_display_text(char* text)
{
    printf("%s\n", text);
}

