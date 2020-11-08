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

void ui_display_text(char* text)
{
    printf("%s\n", text);
}
