#include "shell.h"

/**
 * _put - writes an array of chars to standard output
 * @string: pointer to the array of chars
 * Return: the number of bytes written
 * On error, -1 is returned, and errno is set appropriately.
 */
int _put(char *string)
{
        return write(STDOUT_FILENO, string, str_len(string));
}
