#include "shell.h"

/**
 * _strtok - separates strings with delimiters
 * @line: Pointer to the input string
 * @delim: Delimiter characters used to split the string
 * Return: A pointer to the created token
 */
char *_strtok(char *line, char *delim)
{
	static char *str;
	char *token_start = NULL;

	if (line != NULL)
		str = line;

	/* Skip leading delimiters */
	while (*str != '\0' && strchr(delim, *str) != NULL)
		str++;

	if (*str == '\0')
		return (NULL);

	token_start = str;

	/* Find the end of the token */
	while (*str != '\0' && strchr(delim, *str) == NULL)
		str++;

	if (*str != '\0') {
		*str = '\0';
		str++;
	}

	return token_start;
}

