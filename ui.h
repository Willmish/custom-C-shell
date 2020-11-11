#pragma once
#include "structures.h"


void ui_display_prompt();
char* ui_get_input(int* input_length);
stt_cmd_arr* ui_seperate_args(char* input_line, stt_cmd_arr* arr);

