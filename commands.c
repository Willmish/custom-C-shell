#include "commands.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
// command libs
#include <unistd.h>

#define MAX_USERNAME 1024


// Commands available:
// user related
char* cmd_get_login()
{
    char* buf = malloc(MAX_USERNAME*sizeof(char));
    getlogin_r(buf, MAX_USERNAME);
    // default max length of username as 1024 chars
    return buf;
}


char* cmd_getcwd()
{
    char* buf = malloc(PATH_MAX*sizeof(char)); 
    // If path exceeds PATH_MAX (which unfortunately can happen), it won't be printed.
    if(getcwd(buf, sizeof(char)*PATH_MAX) == NULL)
    {
        buf = "";
        if (errno == EACCES) 
        {
           perror("Error getting directory");
        }
        else if (errno == ERANGE) 
        {
           perror("Error getting directory");
        }
        else
        {
           perror("Error getting directory ( other)");
        }
    }
        
    return buf;
}

int cmd_cd(stt_cmd_arr* args)
{
    int return_val;
    if (args->last_index == 1)
    {
        return_val = chdir(stt_get_command(args, 1));
        if (return_val != 0)
            return errno;
    }
    else if(args->last_index >1)
        return E2BIG;
    else
    {
        return_val = chdir(getenv("HOME"));
        if (return_val != 0)
            return errno;
    }
    return 0;
}

int cmd_history(stt_cmd_arr* args, stt_cmd_arr* history)
{
    if (args->last_index == 0)
    {
        // call was history
        for (int i = 0; i <= history->last_index; ++i)
        {
            printf("%d  %s", i, stt_get_command(history, i));
        }
    }
    else if(args->last_index == 1)
    {
        //call was history [n]
        int n = (int) strtol(stt_get_command(args, 1), NULL, 10);
        if (history->last_index == 0)
            n= 1;
        else if (n > history->last_index +1)
            n = history->last_index +1;

        for(int i = history->last_index - n + 1; i <= history->last_index; ++i)
            printf("%d  %s", i, stt_get_command(history, i));
    } else
    {
        // argument list too big
        return E2BIG;
    }
    return 0;
}


int cmd_help(stt_cmd_arr* args)
{
    if(args->last_index > 1)
        return E2BIG;
    printf("\n");
    if(args->last_index == 0)
    {
        printf("Shym-SHELL, version 0.2\n");
        printf("Currently does not support piping, Shell variables, arguments longer then a single word.\n");
        printf("\n");
        printf("Built-in commands:\n\n");
        printf("cd [dir] (dir is optional)\n");
        printf("exit\n");
        printf("help [builtin]\n");
        printf("history [n] (n is optional)\n"); 
        printf("\nUse help [builtin] to get help on a particular builtin function.\n\n");
        return 0;
    }
    char* builtin = stt_get_command(args, 1);

    if (strcmp(builtin, "cd") == 0)
    {
        printf("cd: cd [dir]\n\n");
        printf("Change the current directory to DIR. The default DIR is the value of the HOME shell variable.\n");
    }
    else if (strcmp(builtin, "exit") == 0)
    {
        printf("exit: exit\n\n");
        printf("Exits the shell.\n");
    }
    else if (strcmp(builtin, "help") == 0)
    {
        printf("help: help [builtin]\n\n");
        printf("If BUILTIN is specified, displays help mesage for the particular function.\n");
        printf("Otherwise, displays the general help information for this shell.\n");
    }
    else if (strcmp(builtin, "history") == 0)
    {
        printf("history: history [n]\n\n");
        printf("If N is specified, displays the last N commands entered.\n");
        printf("Otherwise, displays all commands entered to the shell for this session.\n");
    }

    else
    {
        printf("%s: no builtin command %s defined\n", stt_get_command(args, 0), builtin);
    }
    return 0;
}
