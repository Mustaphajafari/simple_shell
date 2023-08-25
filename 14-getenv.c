#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Environ string array copy
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		ffree(info->environ);
		info->environ = list_to_array(info->env);
		info->env_changed = 0;
	}
	return info->environ;
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	if (!var)
		return 0;

	info->env_changed = delete_nodes_by_prefix(&(info->env), var);
	return info->env_changed;
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: 0 on success, 1 on failure
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return 1;

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return 1;

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = node_starts_with(info->env, var, '=');
	if (node)
	{
		free(node->str);
		node->str = buf;
		info->env_changed = 1;
	}
	else
	{
		add_node_end(&(info->env), buf, 0);
		info->env_changed = 1;
	}

	return 0;
}

