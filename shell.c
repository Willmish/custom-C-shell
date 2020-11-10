#include "shell.h"
#include "ui.h"
#include "commands.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include <string.h>
#include <stdbool.h>


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
    printf("Goodbye!");
}

void shell_execute(arr2D args)
{
    char* comd_name = args.array[0];

    if (strcmp(comd_name, "cd") == 0)
    {
        if (args.no_rows == 2)
            cmd_cd(args.array[1]);
        else if(args.no_rows > 2)
            printf("%s: too many arguments\n", comd_name);
        else
            printf("%s: too few arguments\n", comd_name);
    }
    else if(strcmp(comd_name, "help") == 0)
    {
        if(args.no_rows == 1)
            cmd_help();
        else
            printf("%s: too many arguments\n", comd_name);
    }
    else
        shell_execute_from_path(args);
    
}

void shell_execute_from_path(arr2D args)
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
        // IF it gets here, either the command failed to execute or was not found in path
        if (errno == ENOENT)
        {
            int command_length = strlen(args.array[0]);
            bool is_a_file = false;

            for(int i = 0; i < command_length; ++i)
            {
                if (args.array[0][i] == '/')
                {
                    is_a_file =true;
                    break;
                }
            }

            if (is_a_file)
                printf("%s: No such file or directory\n", args.array[0]);
            else
                printf("%s: command not found\n", args.array[0]);
        } else
            perror("Failed to execute command");

        kill(getpid(), SIGTERM);
    } else
    {
        waitpid(child_PID, &wstatus, 0); // Wait until the Child finishes its process
    }
}
