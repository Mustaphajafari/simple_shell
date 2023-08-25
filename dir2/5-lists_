#include "shell.h"



/**
 * get_node_index - gets the index of a node in a linked list
 * @head: pointer to the head node of the linked list
 * @target: pointer to the node whose index is to be found
 *
 * Return: index of the node, or -1 if not found
 */
int get_node_index(const list_t *head, const list_t *target)
{
    int index = 0;

    while (head != NULL)
    {
        if (head == target)
            return index;
        index++;
        head = head->next;
    }

    /* Node not found in the list */
    return -1;
}

/* this is for the memory */

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
