#include "shell.h"

/**
 * list_length - determines the length of a linked list
 * @head: pointer to the head node
 *
 * Return: length of the linked list
 */
size_t list_length(const list_t *head)
{
    size_t count = 0;

    while (head != NULL)
    {
        count++;
        head = head->next;
    }

    return count;
}

/**
 * list_to_array - converts a linked list of strings to an array of strings
 * @head: pointer to the head node of the linked list
 *
 * Return: array of strings (char **)
 */
char **list_to_array(const list_t *head)
{
    size_t len = list_length(head);
    char **array = malloc((len + 1) * sizeof(char *));
    size_t i = 0;

    if (array == NULL)
        return NULL;

    while (head != NULL)
    {
        array[i] = _strdup(head->str);
        if (array[i] == NULL)
        {
            while (i > 0)
                free(array[--i]);
            free(array);
            return NULL;
        }
        i++;
        head = head->next;
    }

    array[i] = NULL; // Null-terminate the array
    return array;
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

#include "shell.h"

/**
 * find_node_with_prefix - finds a node whose string starts with a prefix
 * @head: pointer to the head node of the linked list
 * @prefix: prefix to search for
 *
 * Return: pointer to the node or NULL if not found
 */
list_t *find_node_with_prefix(const list_t *head, const char *prefix) /*main function*/
{
    while (head != NULL)
    {
        if (_starts_with(head->str, prefix))
            return (list_t *)head; // Cast const away
        head = head->next;
    }
    return NULL;
}

/**
 * _starts_with - checks if a string starts with a prefix
 * @str: string to check
 * @prefix: prefix to compare with
 *
 * Return: 1 if starts with prefix, 0 otherwise
 */
int _starts_with(const char *str, const char *prefix)
{
    while (*prefix)
    {
        if (*prefix != *str)
            return 0;
        prefix++;
        str++;
    }
    return 1;
}

