#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees an array of strings
 * @str_array: pointer to the array of strings
 *
 * Return: void
 */
void ffree(char **str_array)
{
    if (str_array == NULL)
        return;

    for (int i = 0; str_array[i] != NULL; i++)
    {
        free(str_array[i]);
    }

    free(str_array);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to the previous block of memory
 * @old_size: size of the previous block of memory
 * @new_size: size of the new block of memory
 *
 * Return: pointer to the reallocated memory block
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr;

    if (new_size == old_size)
        return ptr;

    if (ptr == NULL)
        return malloc(new_size);

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }

    new_ptr = malloc(new_size);

    if (new_ptr == NULL)
        return NULL;

    if (new_size > old_size)
        _memcpy(new_ptr, ptr, old_size);
    else
        _memcpy(new_ptr, ptr, new_size);

    free(ptr);
    return new_ptr;
}

