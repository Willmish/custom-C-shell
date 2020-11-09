#pragma once

typedef struct array2D
{
    char** array;
    int no_rows;

} arr2D;

void ui_display_prompt();
char* ui_get_input();
arr2D ui_seperate_args(char* input_line);
void ui_free_array2D(arr2D arr);
void ui_display_text(char* text);

