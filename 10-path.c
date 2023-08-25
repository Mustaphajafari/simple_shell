#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(const char *pathstr, int start, int stop)
{
    char *buf = malloc(stop - start + 1);
    if (buf == NULL)
        return NULL;

    int i, k = 0;
    for (i = start; i < stop; i++)
    {
        if (pathstr[i] != ':')
        {
            buf[k] = pathstr[i];
            k++;
        }
    }
    buf[k] = '\0';
    return buf;
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, const char *pathstr, const char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path = NULL;

    if (!pathstr)
        return NULL;

    if (_strlen(cmd) > 2 && starts_with(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return _strdup(cmd);
    }

    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            if (!*path)
                path = _strdup(cmd);
            else
                path = _strcat(_strcat(_strcat(path, "/"), cmd));
            
            if (is_cmd(info, path))
                return path;
            free(path);

            if (!pathstr[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return NULL;
}

