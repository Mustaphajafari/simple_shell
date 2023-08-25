#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n - 1 && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';

    return dest;
}
/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
    size_t dest_len = strlen(dest);
    size_t i;

    for (i = 0; src[i] != '\0' && i < n; i++)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';

    return dest;
}
/**
 * _strchr - locates a character in a string
 * @s: the string to search
 * @c: the character to locate
 * Return: a pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found
 */
char *_strchr(const char *s, int c)
{
    while (*s != '\0')
    {
        if (*s == c)
            return (char *)s; /* Cast away const to match function signature */
        s++;
    }

    if (*s == c)
        return (char *)s; /* Return pointer to null-terminator if character is '\0' */

    return NULL; /* Character not found */
}

