#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
// command libs
#include <unistd.h>


// Commands available:
// user related
char* cmd_get_login()
{
    char* buf = malloc(1024*sizeof(char));
    getlogin_r(buf, 1024);
    // default max of username as 1024 chars
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
           perror("Error changing directory");
        }
        else if (errno == ERANGE) 
        {
            perror("Error changing directory");
        }
        else
        {
            perror("Error changing directory (other)");
        }
    }
        
    return buf;
}
