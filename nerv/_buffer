#include "shell.h"

/**
 * buffer_add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: updated length of the buffer.
 */
int buffer_add(char *buffer, char *str_to_add)
{
int length = str_len(buffer);
int i;

for (i = 0; str_to_add[i]; i++)
{
buffer[length + i] = str_to_add[i];
}
buffer[length + i] = '\0';

return (length + i);
}
