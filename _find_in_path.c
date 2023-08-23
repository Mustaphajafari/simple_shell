#include "shell.h"
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
if (data->command_name[0] == '/' || data->command_name[0] == '.')
return (check_file(data->command_name));
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
if (NULL == PATH
|| PATH[0] == '\0')
return (NULL);
PATH = str_dup(PATH);
for (i = 0; PATH[i]; i++)
if (PATH[i] == ':')
counter_directories++;
tokens = malloc(sizeof(char *) * counter_directories);
i = 0;
tokens[i] = str_dup(_strtok(PATH, ":"));
while (tokens[i])
tokens[++i] = str_dup(_strtok(NULL, ":"));
free(PATH);
return (tokens);
}
/**
 * check_file - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
 * @full_path: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */
int check_file(char *full_path)
{
struct stat sb;
if (stat(full_path, &sb) != -1)
{
if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
{
errno = 126;
return (126);
}
return (0);
}
/*if not exist the file*/
errno = 127;
return (127);
}
