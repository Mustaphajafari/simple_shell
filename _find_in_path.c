#include "shell.h"
/*
int find_path(data_of_program *data);
char **tokenize_path(data_of_program *data);
int check_file(char *full_path);
*/
/**
 * find_path - find a program in the PATH
 * @data: a pointer to the program's data
 * Return: 0 if success, errcode otherwise
 */
int find_path(data_of_program *data)
{
	int i = 0, ret_code = 0;
	char **directories = NULL;

	if (!data->command_name)
		return (2);

	/* Check if it's a full_path or an executable in the same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	/* Build full path with / and command name */
	free(data->tokens[0]);
	data->tokens[0] = str_concat("/", data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data); /* Search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}

	for (i = 0; directories[i]; i++)
	{
		/* Append the command_name to path */
		char *full_path = str_concat(directories[i], data->tokens[0]);
		if (!full_path)
			continue;

		ret_code = check_file(full_path);

		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = full_path;
			free_array_of_pointers(directories);
			return (ret_code);
		}
		free(full_path);
	}

	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - tokenize the PATH into directories
 * @data: a pointer to the program's data
 * Return: array of path directories
 */
char **tokenize_path(data_of_program *data)
{
	int i = 0, counter_directories = 2;
	char **tokens = NULL;
	char *PATH = NULL;

	PATH = env_get("PATH", data);

	if (PATH == NULL || PATH[0] == '\0')
		return (NULL);

	PATH = str_dup(PATH);

	/* Count the number of directories in the PATH */
	for (i = 0; PATH[i]; i++)
		if (PATH[i] == ':')
			counter_directories++;

	tokens = malloc(sizeof(char *) * counter_directories);

	/* Tokenize and duplicate each token of PATH */
	i = 0;
	tokens[i] = str_dup(_strtok(PATH, ":"));

	while (tokens[i])
		tokens[++i] = str_dup(_strtok(NULL, ":"));

	free(PATH);
	return (tokens);
}

