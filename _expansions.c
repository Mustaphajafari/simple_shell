#include "shell.h"

/**
 * expand_var - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_var(data_of_program *data)
{
char *temp_line;
    char *expanded_pid_line;
    char *expanded_var_line;
  char line[BUFFER_SIZE];  

	if (data->input_line == NULL)
        return;

line[BUFFER_SIZE] = {0};
    buffer_add(line, data->input_line);

    temp_line = expand_exit_status(line);
    expanded_pid_line = expand_process_id(temp_line);
    expanded_var_line = expand_variables_in_line(expanded_pid_line, data);

    if (!str_compare(data->input_line, expanded_var_line, 0)) {
        free(data->input_line);
        data->input_line = str_dup(expanded_var_line);
    }

    free(temp_line);
    free(expanded_pid_line);
    free(expanded_var_line);
}

char *expand_exit_status(char *line)
{
    char expansion[BUFFER_SIZE] = {'\0'};
    char *temp_line = str_dup(line);

    char *result = temp_line;
    char *placeholder = strstr(temp_line, "$?");
    while (placeholder) {
        placeholder[0] = '\0';
        long_to_string(errno, expansion, 10);
        buffer_add(result, expansion);
        buffer_add(result, placeholder + 2);
        placeholder = strstr(result, "$?");
    }

    return result;
}

char *expand_process_id(char *line)
{
    char expansion[BUFFER_SIZE] = {'\0'};
    char *temp_line = str_dup(line);

    char *result = temp_line;
    char *placeholder = strstr(temp_line, "$$");
    while (placeholder) {
        placeholder[0] = '\0';
        long_to_string(getpid(), expansion, 10);
        buffer_add(result, expansion);
        buffer_add(result, placeholder + 2);
        placeholder = strstr(result, "$$");
    }

    return result;
}

char *expand_variables_in_line(char *line, data_of_program *data)
{
    int i, j;
    char expansion[BUFFER_SIZE] = {'\0'}, *temp;

    char *result = str_dup(line);
    for (i = 0; result[i]; i++) {
        if (result[i] == '$' && (result[i + 1] == ' ' || result[i + 1] == '\0')) {
            continue;
        } else if (result[i] == '$') {
            for (j = 1; result[i + j] && result[i + j] != ' '; j++)
                expansion[j - 1] = result[i + j];
            temp = env_get(expansion, data);
            result[i] = '\0', expansion[0] = '\0';
            buffer_add(expansion, result + i + j);
            if (temp)
                buffer_add(result, temp);
            buffer_add(result, expansion);
        }
    }

    return result;
}



/**
 * expand_alias - expand aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_alias(data_of_program *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			line[i] = '\0';
			buffer_add(line, temp);
			line[str_len(line)] = '\0';
			buffer_add(line, expansion);
		}
		break; /* Stop after first alias expansion*/
	}

	free(data->input_line);
	data->input_line = str_dup(line);
}

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

	return length + i;
}

