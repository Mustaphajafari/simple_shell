#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r;
	int builtin_ret;

	do {
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);

		r = get_input(info);
		if (r == -1) {
			if (interactive(info))
				_putchar('\n');
		} else {
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}

		free_info(info, r == -1 ? 0 : 1);

		if (!interactive(info) && info->status)
			exit(info->status);

		if (builtin_ret == -2) {
			if (info->err_num == -1)
				exit(info->status);
			exit(info->err_num);
		}
	} while (r != -1 && builtin_ret != -2);

	write_history(info);
	return builtin_ret;
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH and executes it
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int num_args = 0;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	// Count the number of non-delimiter arguments
	for (int i = 0; info->arg[i]; i++)
	{
		if (!is_delim(info->arg[i], " \t\n"))
		{
			num_args++;
		}
	}

	// If no non-delimiter arguments, return
	if (num_args == 0)
	{
		return;
	}

	// Find the command in the PATH
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		// Check if command is an absolute path or a built-in command
		if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
		{
			fork_cmd(info);
		}
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

#include <sys/wait.h>

/**
 * fork_cmd - forks a child process to run the command
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;
	int exec_status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error");
		return;
	}

	if (child_pid == 0) // Child process
	{
		exec_status = execve(info->path, info->argv, get_environ(info));

		free_info(info, 1); // Clean up allocated resources

		if (exec_status == -1)
		{
			if (errno == EACCES)
				exit(126); // Permission denied
			exit(1); // Other error
		}
	}
	else // Parent process
	{
		waitpid(child_pid, &(info->status), 0); // Wait for the child process to finish

		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

