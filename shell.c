#include "ui.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>


void shell_loop()
{
    char* input_line;
    char** args;
    do
        {
            ui_display_prompt();
            // read user input
            input_line = ui_get_input();
            printf("%s\n", input_line);
            // separate command flags
            args = ui_seperate_args(input_line);
            // execute commands
            free(input_line);
            free(args);
        } while(1);
}
