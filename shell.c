#include "shell.h"
#include "ui.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


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
    pid_t child_PID = fork();
    int wstatus;

    if (child_PID == -1)
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
