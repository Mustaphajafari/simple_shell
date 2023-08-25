#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	int i;

	info->fname = av[0];
	info->argc = 0;  // Initialize argc to 0

	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *));
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argc = 1;  // Set argc to 1
			}
		}
		else
		{
			for (i = 0; info->argv[i]; i++)
				;  // Count the number of arguments
			info->argc = i;  // Set argc to the number of arguments
			replace_alias(info);
			replace_vars(info);
		}
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	if (info->argv) {
		ffree(info->argv);
		info->argv = NULL;
		info->path = NULL;
	}

	if (all) {
		if (!info->cmd_buf) {
			free(info->arg);
		}

		free_list(&(info->env));
		free_list(&(info->history));
		free_list(&(info->alias));

		if (info->environ) {
			ffree(info->environ);
			info->environ = NULL;
		}

		bfree((void **)info->cmd_buf);

		if (info->readfd > 2) {
			close(info->readfd);
		}

		_putchar(BUF_FLUSH);
	}
}

