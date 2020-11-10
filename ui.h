#pragma once
#include "structures.h"


void ui_display_prompt();
char* ui_get_input();
stt_cmd_arr ui_seperate_args(char* input_line);
void ui_display_text(char* text);

