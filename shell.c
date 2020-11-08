#include "ui.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>


void shell_loop()
{
    char* input_line;
    char* args;
    do
        {
            ui_display_prompt();
            input_line = ui_get_input();
            printf("%s\n", input_line);
            // read user input
            // separate command flags
            // execute commands
            free(input_line);

        } while(1);
}
