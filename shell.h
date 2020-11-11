#pragma once
#include "ui.h"
#include "structures.h"
#include <stdlib.h>


void shell_loop();
void shell_execute(stt_cmd_arr* args);
void shell_execute_from_path(stt_cmd_arr* args);
