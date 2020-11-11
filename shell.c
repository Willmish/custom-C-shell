#include "shell.h"
#include "ui.h"
#include "structures.h"
#include "commands.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include <string.h>
#include <stdbool.h>

#define MAX_HISTORY_LEN 1024

void shell_loop()
{
    // TODO FIX AND add history)
    /*
    history 
    int* history = malloc(MAX_HISTORY_LEN);
    long history_len = 1024;
    long histo
    */
    char* input_line;
    stt_cmd_arr args;
    do
        {
            ui_display_prompt();
            // read user input
            input_line = ui_get_input();
            // separate command flags
            args = *ui_seperate_args(input_line, &args);

            if (args.last_index < 0)
            {
                free(input_line);
                stt_free_command_arr(&args);
                continue;
            }

            if (strcmp(args.content[0], "exit") == 0)
            {
                free(input_line);
                stt_free_command_arr(&args);
                break;
            }

            // execute commands
            shell_execute(&args);

            free(input_line);
            stt_free_command_arr(&args);
        } while(1);
    printf("Goodbye!");
}

void shell_execute(stt_cmd_arr* args)
{
    char* comd_name = args->content[0];

    if (strcmp(comd_name, "cd") == 0)
    {
        if (args->last_index == 1)
            cmd_cd(args->content[1]);
        else if(args->last_index >1)
            printf("%s: too many arguments\n", comd_name);
        else
            printf("%s: too few arguments\n", comd_name);
    }
    else if(strcmp(comd_name, "help") == 0)
    {
        if(args->last_index == 0)
            cmd_help();
        else
            printf("%s: too many arguments\n", comd_name);
    }
    else
        shell_execute_from_path(args);
    
}

void shell_execute_from_path(stt_cmd_arr* args)
{
    if (stt_get_command(args, args->last_index) != NULL) // Make sure the command is NULL-terminated
    {
        stt_add_NULL_terminator(args);
    }

    pid_t child_PID = fork();
    int wstatus;

    if (child_PID < 0)
    {
        perror("Failed to fork the parent process");
    } if (child_PID == 0)
    {
        execvp(stt_get_command(args, 0),args->content);
        // IF it gets here, either the command failed to execute or was not found in path
        if (errno == ENOENT)
        {
            int command_length = strlen(stt_get_command(args, 0));
            bool is_a_file = false;

            for(int i = 0; i < command_length; ++i)
            {
                if (stt_get_command(args, 0)[i] == '/')
                {
                    is_a_file =true;
                    break;
                }
            }

            if (is_a_file)
                printf("%s: No such file or directory\n", stt_get_command(args, 0)); 
            else
                printf("%s: command not found\n", stt_get_command(args, 0));
        } else
            perror("Failed to execute command");

        kill(getpid(), SIGTERM);
    } else
    {
        waitpid(child_PID, &wstatus, 0); // Wait until the Child finishes its process
    }
}
