#pragma once
#include "structures.h"
// Commands available:
//
// user related
char* cmd_get_login();

// directory related
char* cmd_getcwd();

//builtins
int cmd_cd(const char* dir_path);
void cmd_help(stt_cmd_arr* args);
int cmd_history(stt_cmd_arr* args, stt_cmd_arr* history);
