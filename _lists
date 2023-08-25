#include "shell.h"

/**
 * built_list - search for a match and execute the associated builtin
 * @data: struct for the program's data
 * Return: Returns the return value of the executed function if
 * otherwise returns -1.
 **/
int built_list(data_of_program *data)
{
int iterator;
builtins options[] = {
{"exit", built_exit},
{"help", built_help},
{"cd", built_cd},
{"alias", built_alias},
{"env", built_env},
{"setenv", set_env},
{"unsetenv", unset_env},
{NULL, NULL}
};

/* Walk through the structure */
for (iterator = 0; options[iterator].builtin != NULL; iterator++)
{
/* Check for a match between the given command and a builtin */
if (str_compare(options[iterator].builtin, data->command_name, 0))
{
/* Execute the function and return its return value */
return (options[iterator].function(data));
}
}

/* If there is no match, return -1 */
return (-1);
}

