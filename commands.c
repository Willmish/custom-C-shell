#include "commands.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
            default:
                perror("Error changing directory (other)");
        }
    }
    return return_val;
}
