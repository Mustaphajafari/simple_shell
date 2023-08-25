/**
 * is_chain - tests if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j++] = '\0'; // Replace '|' with null terminator
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j++] = '\0'; // Replace '&' with null terminator
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j++] = '\0'; // Replace ';' with null terminator
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*p = j;
	return (1);
}

/**
 * check_chain - checks if chaining should continue based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->cmd_buf_type == CMD_AND && info->status)
    {
        buf[i] = '\0'; // Terminate the current command
        j = len;       // Skip to the end of the buffer
    }
    else if (info->cmd_buf_type == CMD_OR && !info->status)
    {
        buf[i] = '\0'; // Terminate the current command
        j = len;       // Skip to the end of the buffer
    }

    *p = j;
}


/**
 * replace_alias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
    list_t *node;
    char *alias_value;

    for (int i = 0; i < 10; i++)
    {
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return 0;

        char *equal_sign = _strchr(node->str, '=');
        if (!equal_sign)
            return 0;

        alias_value = _strdup(equal_sign + 1);
        if (!alias_value)
            return 0;

        free(info->argv[0]);
        info->argv[0] = alias_value;
    }

    return 1;
}

/**
 * replace_vars - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
    list_t *node;

    for (int i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!_strcmp(info->argv[i], "$?"))
        {
            replace_string(&(info->argv[i]), _strdup(convert_number(info->status, 10, 0)));
        }
        else if (!_strcmp(info->argv[i], "$$"))
        {
            replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
        }
        else
        {
            node = node_starts_with(info->env, &info->argv[i][1], '=');
            if (node)
            {
                replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
            }
            else
            {
                replace_string(&info->argv[i], _strdup(""));
            }
        }
    }
    return 0;
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
