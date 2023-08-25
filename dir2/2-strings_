#include "shell.h"


#include <unistd.h>  /* Include necessary header */

void _flush_buffer(char *buf, int *index)
{
    if (*index > 0)
    {
        ssize_t bytes_written = write(1, buf, *index);
        if (bytes_written == -1)
        {
            /* Handle error appropriately, e.g., print an error message */
        }
        *index = 0; /* Reset the buffer index */
    }
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        _flush_buffer(buf, &i); /* Call the helper function to flush the buffer */
    }
    if (c != BUF_FLUSH)
        buf[i++] = c; /* Add the character to the buffer */
    return (1); /* Return 1 to indicate successful printing */
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _putchar(str[i]); /* Call _putchar to print each character */
        i++;
    }
}



/**
 * str_duplicate - duplicates an string
 * @string: String to be copied
 * Return: pointer to the array
 */
char *str_dup(char *string)
{
	char *result;
	int length, i;

	if (string == NULL)
		return (NULL);

	length = str_length(string) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length ; i++)
	{
		result[i] = string[i];
	}

	return (result);
}


/**
 * str_copy - Copies a source string to a destination buffer
 * @destination: The buffer where the string will be copied
 * @source: The string to be copied
 *
 * Description: This function copies characters from the source string to the
 * destination buffer until the null-terminator of the source is reached.
 */
void str_copy(char *destination, const char *source)
{
	size_t i = 0;

	/* Copy characters until null-terminator is reached */
	while (source[i] != '\0')
	{
		destination[i] = source[i];
		i++;
	}

	/* Null-terminate the destination string */
	destination[i] = '\0';
}


/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *string, const char *substring)
{
    while (*needle)
    {
        /* If the characters don't match, return NULL immediately. */
        if (*needle != *haystack)
        {
            return NULL;
        }
        needle++;
        haystack++;
    }

    /* Return the address of the next character after the matched substring. */
    return (char *)haystack;
}

