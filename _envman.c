#include "shell.h"

/**
 * env_get - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_get(char *key, data_of_program *data)
{
	int i, key_length = 0;

	if (key == NULL || data->env == NULL)
		return NULL;

	key_length = str_len(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
			data->env[i][key_length] == '=')
		{
			return data->env[i] + key_length + 1;
		}
	}
	return NULL;
}

/**
 * env_set - overwrite or create an environment variable
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 0 if success, 1 if parameters are NULL, 2 if an error occurred
 */
int env_set(char *key, char *value, data_of_program *data)
{
	int i, key_length = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return 1;

	key_length = str_len(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
			data->env[i][key_length] == '=')
		{
			is_new_key = 0;
			free(data->env[i]);
			break;
		}
	}

	data->env[i] = str_concat(str_dup(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_new_key)
	{
		data->env[i + 1] = NULL;
	}
	return 0;
}

/**
 * env_rm - remove a key from the environment
 * @key: the key to remove
 * @data: the structure of the program's data
 * Return: 0 if the key does not exist, 1 if the key was removed
 */
int env_rm(char *key, data_of_program *data)
{
	int i, key_length = 0;

	if (key == NULL || data->env == NULL)
		return 0;

	key_length = str_len(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
			data->env[i][key_length] == '=')
		{
			free(data->env[i]);

			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}

			data->env[i - 1] = NULL;
			return 1;
		}
	}
	return 0;
}

/**
 * put_env - prints the current environment
 * @data: struct for the program's data
 * Return: nothing
 */
void put_env(data_of_program *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_put(data->env[j]);
		_put("\n");
	}
}

