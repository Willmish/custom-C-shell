#include "structures.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
 

stt_cmd_arr* stt_intialise_command_arr(stt_cmd_arr* arr, long length)
{
    if (length == 0)
    {
        printf("Cannot allocate stt_cmd_arr with length NULL!");
        exit(EXIT_FAILURE);
    }
    if((arr->content = malloc(length*sizeof(char*))) == NULL)
    {
        perror("stt_cmd_arr allocation");
        exit(EXIT_FAILURE);
    }
    if((arr->command_size = malloc(length*sizeof(int))) == NULL)
    {
        perror("stt_cmd_arr allocation");
        exit(EXIT_FAILURE);
    }

    arr->length = length;
    arr->last_index = -1; // this is so that add_command will add 0th element;
    return arr;
}

void stt_add_command(stt_cmd_arr* arr, int cmd_size, char* command)
{
    int size = cmd_size;
    int command_len = strlen(command) + 1;
    if (size == 0)
    {
        printf("Cannot allocate stt_cmd_arr->command with length NULL!");
        exit(EXIT_FAILURE);
    }
    // Make sure the string will fit in the to-be allocated memory
    while (command_len > size)
        size += cmd_size;

    ++arr->last_index;
    // Make sure the content array is big enough for the pointer to the string
    if (arr->last_index >= arr->length)
    {
        arr->length += arr->length; // double the size of the arr->content
        if((arr->content = realloc(arr->content, arr->length*sizeof(char*))) == NULL)
        {
            perror("stt_cmd_arr allocation");
            exit(EXIT_FAILURE);
        }
    }

    if((arr->content[arr->last_index] = malloc(size*sizeof(char))) == NULL)
    {
        perror("stt_cmd_arr allocation");
        exit(EXIT_FAILURE);
    }

    arr->command_size[arr->last_index] = size;
    strcpy(arr->content[arr->last_index], command);
}

void stt_add_NULL_terminator(stt_cmd_arr* arr)
{
    ++arr->last_index;

    if (arr->last_index >= arr->length)
    {
        arr->length += arr->length; // double the size of the arr->content
        if((arr->content = realloc(arr->content, arr->length*sizeof(char*))) == NULL)
        {
            perror("stt_cmd_arr allocation");
            exit(EXIT_FAILURE);
        }
    }

    if((arr->content[arr->last_index] = malloc(sizeof(NULL))) == NULL)
    {
        perror("stt_cmd_arr allocation");
        exit(EXIT_FAILURE);
    }

    arr->command_size[arr->last_index] = sizeof(NULL);
    arr->content[arr->last_index] = NULL;
}

char* stt_get_command(stt_cmd_arr* arr, long index)
{
    return (arr->content[index]);
}

void stt_free_command_arr(stt_cmd_arr* arr)
{
    if(arr->last_index >= 0)
        for (int i = 0; i <= arr->last_index; ++i)
        {
            free(arr->content[i]);
        }
    else
        free(arr->content);
}

void stt_print_arr(stt_cmd_arr* arr)
{
    printf("Array at: %p\nLength: %ld; Last index: %ld", arr, arr->length, arr->last_index);
    for (int i = 0; i < arr->last_index; ++i)
    {
        printf("\n%d: size: %d; command: %s", i, arr->command_size[i], stt_get_command(arr, i));
    }
}

int stt_test_arr()
{
    char my_strings[][30] = {"hey there", "Ahoy", "thats a lot of greetings", "Hello there", "General Kenobi!"};
    int len_my_strings = (int) (sizeof(my_strings)/30);
    for(int i = 0; i < 5; ++i)
        printf("%s\n", my_strings[i]);

    stt_cmd_arr arr;
    stt_intialise_command_arr(&arr, 4);
    for (int i = 0; i < len_my_strings; ++i)
        stt_add_command(&arr, 10, my_strings[i]);

    stt_print_arr(&arr);
    stt_free_command_arr(&arr);
    return 0;
}
