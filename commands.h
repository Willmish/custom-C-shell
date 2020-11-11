#pragma once
// Commands available:
//
// user related
char* cmd_get_login();

// directory related
char* cmd_getcwd();

//builtins
int cmd_cd(const char* dir_path);
void cmd_help();
void cmd_history();



