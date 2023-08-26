#include "shell.h"

/**
 * _stringlen - returns the length of a string
 * @str: the string that we want to check his string
 *
 * Return: the length of the string
 */
int _stringlen(char *str)
{
int length = 0;

if (!str)
return (0);

while (*str != '\0')
{
length++;
str++;
}

return (length);
}



/**
 * frfr - Frees a pointer and sets it to NULL
 * @ptr: Address of the pointer to free
 *
 * Return: 1 if freed, 0 if ptr or *ptr is NULL.
 */
int frfr(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}

/**
 * get_node_index - gets the index of a node in a linked list
 * @head: pointer to the head of the linked list
 * @node: pointer to the node whose index is to be found
 *
 * Return: index of the node if found, -1 otherwise
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
size_t index = 0;

while (head)
{
if (head == node)
return (index);

head = head->next;
index++;
}

return (-1);
}
/**
 * delimiter - checks if character is a delimiter
 * @c: the char to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int delimiter(char c, const char *delim)
{
while (*delim != '\0')
{
if (*delim == c)
return (1);
delim++;
}
return (0);
}

