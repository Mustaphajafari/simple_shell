#include "shell.h"



void _eputs(const char *str) {
    if (str) {
        ssize_t i = 0;
        while (str[i] != '\0') {
            write(1, &str[i], 1); /* Write one character at a time to standard output */
            i++;
        }
    }
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

int _putsfd(char *str, int fd)
{
	if (!str)
		return 0;

	int chars_written = 0;

	while (*str)
	{
		chars_written += _putfd(*str++, fd);
	}

	return chars_written;
}

