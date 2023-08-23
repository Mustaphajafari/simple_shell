#include "shell.h"

/**
 * _putchar - writes an array of chars to standard error
 * @string: pointer to the array of chars
 * Return: the number of bytes written
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char *string)
{
        return write(STDERR_FILENO, string, str_len(string));
}
