#include "shell.h"

/**
 * _getline - read one line from the prompt.
 * @data: struct for the program's data
 *
 * Return: reading counting bytes.
 */
int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read;
	/*int i = 0;*/

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
	    (array_operators[0] == '|' && errno == 0))
	{
		clear_array_commands(array_commands, array_operators);

		bytes_read = read(data->file_descriptor, buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return -1;

		split_commands_and_operators(buff, array_commands, array_operators);
	}

	data->input_line = array_commands[0];
	shift_arrays_left(array_commands, array_operators);

	return str_len(data->input_line);
}

/**
 * clear_array_commands - free the memory allocated in the array_commands.
 * @array_commands: array of commands
 * @array_operators: array of operators
 */
void clear_array_commands(char *array_commands[], char array_operators[])
{
	int i;

	for (i = 0; array_commands[i]; i++)
	{
		free(array_commands[i]);
		array_commands[i] = NULL;
	}
}

/**
 * split_commands_and_operators - split lines for \n or ;
 * @buff: input buffer
 * @array_commands: array of commands
 * @array_operators: array of operators
 */
void split_commands_and_operators(char *buff, char *array_commands[], char array_operators[])
{
	int i = 0;

	do {
		array_commands[i] = str_dup(_strtok(i ? NULL : buff, "\n;"));
		i = check_logic_ops(array_commands, i, array_operators);
	} while (array_commands[i++]);
}

/**
 * shift_arrays_left - shifts elements in arrays to the left.
 * @array_commands: array of commands
 * @array_operators: array of operators
 */
void shift_arrays_left(char *array_commands[], char array_operators[])
{
	int i;

	for (i = 0; array_commands[i]; i++)
	{
		array_commands[i] = array_commands[i + 1];
		array_operators[i] = array_operators[i + 1];
	}
}

