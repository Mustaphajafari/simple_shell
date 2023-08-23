#include "shell.h"

/**
 * built_env - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: 0 if success, or other number if it's declared in the arguments
 */
int built_env(data_of_program *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	if (data->tokens[1] == NULL)
	{
		put_env(data);
	}
	else
	{
		for (i = 0; data->tokens[1][i] && data->tokens[1][i] != '='; i++)
		{
			cpname[i] = data->tokens[1][i];
		}

		if (data->tokens[1][i] == '=')
		{
			var_copy = env_get(cpname, data);
			if (var_copy != NULL)
			{
				env_set(cpname, data->tokens[1] + i + 1, data);
				put_env(data);
				env_set(cpname, var_copy, data);
				free(var_copy);
			}
			else
			{
				_put(data->tokens[1]);
				_put("\n");
			}
		}
		else
		{
			errno = 2;
			perror(data->command_name);
			errno = 127;
		}
	}

	return (0);
}

/**
 * set_env - ..
 * @data: struct for the program's data
 * Return: 0 if success, or other number if it's declared in the arguments
 */
int set_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL || data->tokens[3] != NULL)
	{
		errno = data->tokens[1] ? E2BIG : EINVAL;
		perror(data->command_name);
		return (5);
	}

	env_set(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * unset_env - ..
 * @data: struct for the program's data
 * Return: 0 if success, or other number if it's declared in the arguments
 */
int unset_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] != NULL)
	{
		errno = data->tokens[1] ? E2BIG : EINVAL;
		perror(data->command_name);
		return (5);
	}

	env_rm(data->tokens[1], data);

	return (0);
}

