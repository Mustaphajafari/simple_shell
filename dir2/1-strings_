#include "shell.h"

/**
 * str_concat - Concatenates two strings
 * @s1: The first string
 * @s2: The second string
 *
 * Return: A newly allocated concatenated string
 */
char *str_concat(char *s1, char *s2)
{
	char *concatenated;
	int len1 = 0, len2 = 0, i, j;

	if (s1 != NULL)
		len1 = str_length(s1);

	if (s2 != NULL)
		len2 = str_length(s2);

	concatenated = malloc(sizeof(char) * (len1 + len2 + 1));

	if (concatenated == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (i = 0; i < len1; i++)
		concatenated[i] = s1[i];

	for (j = 0; j < len2; j++)
		concatenated[i + j] = s2[j];

	concatenated[i + j] = '\0';

	return (concatenated);
}

/**
 * str_length - Returns the length of a string.
 * @string: The input string.
 * Return: The length of the string.
 */
size_t str_length(const char *string)
{
    size_t length = 0;

    while (string[length] != '\0')
    {
        length++;
    }

    return length;
}

/**
 * _strcmp - Compares two strings lexicographically.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
        {
            return (*s1 - *s2);
        }
        s1++;
        s2++;
    }
    
    return (*s1 - *s2);
}

