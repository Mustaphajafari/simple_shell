#include "shell.h"

/**
 * tokenize - this function separates the string using a designated delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(data_of_program *data)
{
    char *delimiter = " \t";
    int i, counter = 0;
    char *token;

    int length = str_len(data->input_line);
    if (length && data->input_line[length - 1] == '\n')
        data->input_line[length - 1] = '\0';

    for (i = 0; data->input_line[i]; i++)
    {
        if (strchr(delimiter, data->input_line[i]))
            counter++;
    }
    counter++; /* Account for the last token*/

    data->tokens = malloc(counter * sizeof(char *));
    if (data->tokens == NULL)
    {
        perror(data->program_name);
        exit(errno);
    }

    i = 0;
    token = _strtok(data->input_line, delimiter);
    while (token)
    {
        data->tokens[i++] = str_dup(token);
        token = _strtok(NULL, delimiter);
    }
    data->tokens[i] = NULL;

    if (i > 0)
    {
        data->command_name = str_dup(data->tokens[0]);
    }
}

