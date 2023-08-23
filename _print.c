#include "shell.h"



/**
 * _print_error - writes an array of chars to standard error for specific error codes
 * @errorcode: error code to print
 * @data: a pointer to the program's data
 * Return: 0
 */
int _print_error(int errorcode, data_of_program *data)
{
	char n_as_string[10] = {'\0'};
	long_to_string((long)data->exec_counter, n_as_string, 10);

	_putchar(data->program_name);
	_putchar(": ");
	_putchar(n_as_string);
	_putchar(": ");

	if (errorcode == 2 || errorcode == 3)
	{
		_putchar(data->tokens[0]);
		_putchar(": ");
		if (errorcode == 2)
			_putchar("Illegal number: ");
		else
			_putchar("can't cd to ");
		_putchar(data->tokens[1]);
	}
	else if (errorcode == 127)
	{
		_putchar(data->command_name);
		_putchar(": not found");
	}
	else if (errorcode == 126)
	{
		_putchar(data->command_name);
		_putchar(": Permission denied");
	}

	_putchar("\n");
	return 0;
}

