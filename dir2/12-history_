#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
    char *home_dir = _getenv(info, "HOME=");
    if (!home_dir)
        return NULL;
    
    char *filename = malloc(_strlen(home_dir) + _strlen(HIST_FILE) + 2);
    if (!filename)
    {
        free(home_dir);
        return NULL;
    }
    
    _strcpy(filename, home_dir);
    _strcat(filename, "/");
    _strcat(filename, HIST_FILE);
    free(home_dir);
    return filename;
}

/**
 * write_history - creates or appends to a history file
 * @info: the parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int write_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return -1;
    
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    free(filename);
    if (fd == -1)
        return -1;
    
    list_t *node = info->history;
    while (node)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
        node = node->next;
    }
    _putfd(BUF_FLUSH, fd);
    close(fd);
    return 1;
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: number of lines read from history file
 */
int read_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return 0;
    
    int fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return 0;
    
    struct stat st;
    if (fstat(fd, &st) != 0)
    {
        close(fd);
        return 0;
    }
    
    char *buf = malloc(st.st_size + 1);
    if (!buf)
    {
        close(fd);
        return 0;
    }
    
    ssize_t rdlen = read(fd, buf, st.st_size);
    close(fd);
    if (rdlen <= 0)
    {
        free(buf);
        return 0;
    }
    
    buf[st.st_size] = '\0';
    int linecount = parse_history(info, buf);
    free(buf);
    return linecount;
}

/**
 * parse_history - parses history buffer and builds history linked list
 * @info: the parameter struct
 * @buf: buffer containing history
 *
 * Return: number of lines parsed from history buffer
 */
int parse_history(info_t *info, char *buf)
{
    int last = 0;
    int linecount = 0;
    for (int i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            build_history_list(info, buf + last, linecount++);
            last = i + 1;
        }
    }
    if (last != 0)
        build_history_list(info, buf + last, linecount++);
    
    int max_history = HIST_MAX;
    while (linecount >= max_history)
    {
        delete_node_at_index(&(info->history), 0);
        linecount--;
    }
    
    renumber_history(info);
    return linecount;
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: the parameter struct
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: 1 on success, 0 on failure
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
    add_node_end(&(info->history), buf, linecount);
    return 1;
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: the parameter struct
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;
    while (node)
    {
        node->num = i++;
        node = node->next;
    }
    info->histcount = i;
    return i;
}

