#pragma once
// Commands available:
//
// user related
char* cmd_get_login();

// directory related
char* cmd_getcwd();
int cmd_cd(const char* dir_path);
void cmd_mkdir(char* dir_name);


void cmd_mv(char* source, char* destination);


