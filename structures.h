#pragma once
#include <stdlib.h>


typedef struct command_arr {
    char** content;
    u_long length;
    u_long last_index;
    int* command_size;
} stt_cmd_arr;


// basic operations
stt_cmd_arr* stt_initialise_command_arr(u_long length);
void stt_add_command(stt_cmd_arr* arr, int cmd_size, char* command);
char* stt_get_command(stt_cmd_arr* arr, u_long index);

// clean up operations
void stt_free_command_arr(stt_cmd_arr* arr);

// testing
int stt_test_arr();
void stt_print_arr(stt_cmd_arr* arr);

