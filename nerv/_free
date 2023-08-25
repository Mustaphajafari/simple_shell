#include "shell.h"

/**
 * free_recurrent_data - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_recurrent_data(data_of_program *data)
{
free_array_of_pointers(data->tokens);
free(data->input_line);
free(data->command_name);

data->input_line = NULL;
data->command_name = NULL;
data->tokens = NULL;
}

/**
 * free_all_data - free all fields of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_all_data(data_of_program *data)
{
if (data->file_descriptor != 0 && close(data->file_descriptor) != 0)
perror(data->program_name);

free_recurrent_data(data);
free_array_of_pointers(data->env);
free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - frees an array of pointers and each pointer within
 * @array: array of pointers
 * Return: Nothing
 */
void free_array_of_pointers(char **array)
{
int i = 0;

if (array != NULL)
{
for (i = 0; array[i]; i++)
free(array[i]);

free(array);
}
}

