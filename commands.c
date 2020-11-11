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

int cmd_cd(const char* dir_path)
{
    int return_val = chdir(dir_path);
    if (return_val != 0)
    {
        switch(errno)
        {
            case EACCES:
                perror("Error changing directory");
                break;
            case ENOENT:
                printf("cd: %s: %s\n", dir_path, strerror(errno));
                break;
            default:
                perror("Error changing directory (other)");
        }
    }
    return return_val;
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


void cmd_help(stt_cmd_arr* args)
{
    printf("Shym-SHELL, version 0.1\n");
    printf("Currently does not support piping, Shell variables, arguments longer then a single word.\n");
    printf("\n");
    printf("Built-in commands:\n\n");
    printf("cd [dir]\n");
    printf("exit\n");
    printf("help\n");
}
