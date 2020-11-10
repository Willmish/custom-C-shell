#include "shell.h"
#include "ui.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


void shell_loop()
{
    char* input_line;
    arr2D args;
    do
        {
            ui_display_prompt();
            // read user input
            input_line = ui_get_input();
            // separate command flags
            args = ui_seperate_args(input_line);

            if (args.no_rows <= 0)
            {
                free(input_line);
                ui_free_array2D(args);
                continue;
            }

            if (strcmp(args.array[0], "exit") == 0)
            {
                free(input_line);
                ui_free_array2D(args);
                break;
            }
            /* DEBUG
            for (int i = 0; i < args.no_rows; ++i)
                printf("%d: %s\n", i, args.array[i]);
                */
            // execute commands
            shell_execute(args);

            free(input_line);
            ui_free_array2D(args);
        } while(1);
}

void shell_execute(arr2D args)
{
    if (args.array[args.no_rows - 1] != NULL) // Make sure the command is NULL-terminated
    {
        args.array = realloc(args.array, (args.no_rows+1) * sizeof(char*));
        args.array[args.no_rows] = malloc(sizeof(NULL));
        args.array[args.no_rows] = NULL;
        ++args.no_rows;
    }

    pid_t child_PID = fork();
    int wstatus;

    if (child_PID < 0)
    {
        perror("Failed to fork the parent process");
    } if (child_PID == 0)
    {
        execvp(args.array[0], args.array);
    } else
    {
        waitpid(child_PID, &wstatus, 0); // Wait until the Child finishes its process
    }
}
