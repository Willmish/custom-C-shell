#include <stdio.h>
#include <stdlib.h>
#include "commands.h"

void ui_display_prompt()
{
    char* buf;
    buf = cmd_get_login();
    printf("%s:", buf);
    buf = cmd_getcwd();
    printf("%s ??", buf);
    free(buf);
}

char* ui_get_input()
{
    char* lineptr = malloc(1);
    int len = (int) getline(&lineptr, 0, stdin);
    return lineptr;
}

void ui_display_text(char* text)
{
    printf("%s\n", text);
}

