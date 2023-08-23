#include "shell.h"

int main(int argc, char *argv[], char *env[])
{
data_of_program data_struct = {0}; /* Initialize to zero */
data_of_program *data = &data_struct;
char *prompt = NULL; /* Initialize to NULL */

inicialize_data(data, argc, argv, env);

signal(SIGINT, handle_ctrl_c);

if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
{
errno = 2;
prompt = PROMPT_MSG;
}

errno = 0;
sisifo(prompt, data);
return (0);
}

void handle_ctrl_c(int opr UNUSED)
{
_put("\n");
_put(PROMPT_MSG);
}

void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
int i;

data->program_name = argv[0];
data->input_line = NULL;
data->command_name = NULL;
data->exec_counter = 0;
data->file_descriptor = (argc == 1) ? STDIN_FILENO : open(argv[1], O_RDONLY);

if (data->file_descriptor == -1)
{
_putchar(data->program_name);
_putchar(": 0: Can't open ");
_putchar(argv[1]);
_putchar("\n");
exit(127);
}

data->tokens = NULL;
data->env = malloc(sizeof(char *) * 50);
for (i = 0; env[i]; i++)
data->env[i] = str_dup(env[i]);
data->env[i] = NULL;

data->alias_list = malloc(sizeof(char *) * 20);
for (i = 0; i < 20; i++)
data->alias_list[i] = NULL;
}

void sisifo(char *prompt, data_of_program *data)
{
int error_code = 0, string_len = 0;

while (++(data->exec_counter))
{
_put(prompt);
error_code = string_len = _getline(data);

if (error_code == EOF)
{
free_all_data(data);
exit(errno);
}
if (string_len >= 1)
{
expand_alias(data);
expand_var(data);
tokenize(data);
if (data->tokens[0])
{
error_code = execute(data);
if (error_code != 0)
_print_error(error_code, data);
}
free_recurrent_data(data);
}
}
}

