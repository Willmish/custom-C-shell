#include "ui.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>


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

            for (int i = 0; i < args.no_rows; ++i)
                printf("%d: %s\n", i, args.array[i]);
            // execute commands
            free(input_line);
            ui_free_array2D(args);
        } while(1);
}
