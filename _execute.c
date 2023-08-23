#include "shell.h"

/**
 * execute - execute a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If success returns zero, otherwise, return -1.
 */
int execute(data_of_program *data)
{
int retval = 0, status;
pid_t child_pid;

	/* Check if the program is a built-in command */
retval = built_list(data);
if (retval != -1)
return (retval);

	/* Check if the program exists in the file system */
retval = find_path(data);
if (retval)
return (retval);

	/* If the program was found, fork and execute it */
child_pid = fork();
if (child_pid == -1)
{
perror(data->command_name);
exit(EXIT_FAILURE);
}
if (child_pid == 0)
{
		/* Child process: execute the program */
retval = execve(data->tokens[0], data->tokens, data->env);
if (retval == -1)
{
perror(data->command_name);
exit(EXIT_FAILURE);
}
}
else
{
		/* Parent process: wait for child to finish and check status */
wait(&status);
if (WIFEXITED(status))
errno = WEXITSTATUS(status);
else if (WIFSIGNALED(status))
errno = 128 + WTERMSIG(status);
}

return (0);
}

