#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

#include "commands.h"
#include "ui.h"
#include "structures.h"

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

char* ui_get_input(int* input_length)
{
    char* lineptr = malloc(1);
    size_t bufsize = 0;
    if((*input_length = getline(&lineptr, &bufsize, stdin)) == -1)
    {
        if(feof(stdin))
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("Error reading stdin");
            exit(EXIT_FAILURE);
        }
    }
    return lineptr;
}

stt_cmd_arr* ui_seperate_args(char* input_line, stt_cmd_arr* args)
{
    int buff_size = BUFFER_SIZE;
    char* buff_string = malloc(buff_size*sizeof(char));
    int input_length = strlen(input_line);

    stt_intialise_command_arr(args, buff_size);

    if (input_length == 1 && input_line[0] == '\n')
        {
            free(buff_string);
            args->last_index = -1;
            return args;
        }

    buff_string[0] = '\0'; // Clear buff_string
    for (int i = 0; i < input_length; ++i)
    {
        if (isspace(input_line[i]))
        {
            if (strlen(buff_string) != 0)
            {
                // If a whitspace char occurs and the buff_string contains an argument, add it to the args array
                stt_add_command(args, buff_size, buff_string);
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
    return args;
}

