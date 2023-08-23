#include "shell.h"

/**
 * built_exit - exit the program with the status
 * @data: struct for the program's data
 * Return: 0 if success, or other number if it's declared in the arguments
 */
int built_exit(data_of_program *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (!isdigit(data->tokens[1][i]) && data->tokens[1][i] != '+')
			{
				errno = EINVAL;
				return EINVAL;
			}
		}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * built_cd - change the current directory
 * @data: struct for the program's data
 * Return: 0 if success, or other number if it's declared in the arguments
 */
int built_cd(data_of_program *data)
{
	char *dir_home = env_get("HOME", data);
	char *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			_put(env_get("PWD", data));
			_put("\n");
			return error_code;
		}
		else
		{
			return set_work_directory(data, data->tokens[1]);
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, sizeof(old_dir));
		return set_work_directory(data, dir_home);
	}
}

/**
 * set_work_directory - set the working directory
 * @data: struct for the program's data
 * @new_dir: path to be set as the working directory
 * Return: 0 if success, or other number if it's declared in the arguments
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, sizeof(old_dir));

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = ENOENT;
			return ENOENT;
		}
		env_set("PWD", new_dir, data);
	}
	env_set("OLDPWD", old_dir, data);
	return 0;
}

/**
 * built_help - shows help messages for built-in commands
 * @data: struct for the program's data
 * Return: 0 if success, or other number if it's declared in the arguments
 */
int built_help(data_of_program *data)
{
	int i, length = 0;
	char *help_messages[] = {
		NULL, HELP_EXIT_MSG, HELP_ENV_MSG, HELP_SETENV_MSG,
		HELP_UNSETENV_MSG, HELP_CD_MSG
	};

	if (data->tokens[1] == NULL)
	{
		_put(help_messages[0] + 6);
		return 1;
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return 5;
	}

	for (i = 1; i < sizeof(help_messages) / sizeof(help_messages[0]); i++)
	{
		length = str_len(data->tokens[1]);
		if (str_compare(data->tokens[1], help_messages[i], length))
		{
			_put(help_messages[i] + length + 1);
			return 1;
		}
	}

	errno = EINVAL;
	perror(data->command_name);
	return 0;
}

/**
 * built_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: 0 if success, or other number if it's declared in the arguments
 */
int built_alias(data_of_program *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return print_alias(data, NULL);

	while (data->tokens[++i])
	{
		if (count_characters(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			print_alias(data, data->tokens[i]);
	}

	return 0;
}

