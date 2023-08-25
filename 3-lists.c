#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints the str element of a list_t linked list
 * @head: pointer to the first node of the list
 *
 * Return: the number of nodes in the list
 */
size_t print_list_str(const list_t *head)
{
    size_t node_count = 0;
    const list_t *current_node = head;

    while (current_node)
    {
        if (current_node->str != NULL) {
            _puts(current_node->str);
        } else {
            _puts("(nil)");
        }
        _puts("\n");
        current_node = current_node->next;
        node_count++;
    }

    return node_count;
}

/**
 * delete_node_at_index - deletes a node at a given index
 * @head: pointer to the pointer of the first node
 * @index: index of the node to be deleted (0-based)
 *
 * Return: 1 if successful, 0 if index is out of bounds
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
    list_t *current_node, *prev_node;
    unsigned int count = 0;

    if (head == NULL || *head == NULL)
        return 0;

    current_node = *head;
    prev_node = NULL;

    while (current_node != NULL)
    {
        if (count == index)
        {
            if (prev_node == NULL)
            {
                *head = current_node->next;
            }
            else
            {
                prev_node->next = current_node->next;
            }
            free(current_node->str); /* Free allocated memory for the string */
            free(current_node); /* Free the node itself */
            return 1;
        }
        prev_node = current_node;
        current_node = current_node->next;
        count++;
    }

    return 0; /* Index is out of bounds */
}

/**
 * free_list - frees all nodes of a linked list
 * @head: pointer to the head node
 *
 * Return: void
 */
void free_list(list_t *head)
{
    list_t *current_node;

    while (head != NULL)
    {
        current_node = head;
        head = head->next;

        free(current_node->str); /* Free allocated memory for the string */
        free(current_node); /* Free the node itself */
    }
}

