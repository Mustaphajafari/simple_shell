#include "shell.h"

/**
 * _myhistory - displays the history list
 * @info: the parameter struct
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_alias - removes an alias from the alias list
 * @info: the parameter struct
 * @alias: the alias to unset
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *alias)
{
    return delete_node_at_index(&(info->alias),
                                get_node_index(info->alias, node_starts_with(info->alias, alias, -1)));
}

/**
 * set_alias - adds or updates an alias in the alias list
 * @info: the parameter struct
 * @alias: the alias to set
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias)
{
    char *p = _strchr(alias, '=');
    if (p)
    {
        *p = '\0'; // Temporarily remove the '=' to get the alias name
        unset_alias(info, alias);
        *p = '='; // Restore the '='
        return (add_node_end(&(info->alias), alias, 0) == NULL);
    }
    return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: the parameter struct
 * Return: Always 0
 */
int _myalias(info_t *info)
{
    int i = 0;

    if (info->argc == 1)
    {
        list_t *node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }

    for (i = 1; info->argv[i]; i++)
    {
        char *p = _strchr(info->argv[i], '=');
        if (p)
        {
            if (set_alias(info, info->argv[i]) == 1)
            {
                _eputs("alias: error setting alias: ");
                _eputs(info->argv[i]);
                _eputs("\n");
            }
        }
        else
        {
            list_t *node = node_starts_with(info->alias, info->argv[i], '=');
            if (node)
                print_alias(node);
            else
            {
                _eputs("alias: ");
                _eputs(info->argv[i]);
                _eputs(" not found\n");
            }
        }
    }

    return (0);
}

