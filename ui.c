#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void display_prompt()
{
    char curr_working_dir[1024]; // Limit to dir name
    getcwd(curr_working_dir, sizeof(curr_working_dir));

    printf("%s ??", curr_working_dir);
}
