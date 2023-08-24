
#ifndef SHELL_H
#define SHELL_H

#include <ctype.h>


#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

#ifndef HELPERS_H
#define HELPERS_H

/* Prompt to be printed */
#define PROMPT_MSG "#cisfun$ " /* Needed to work with signal */

/* Resume from the unused attibute */
#define UNUSED __attribute__((unused))

/* buffer size for each read call in _getline */
#define BUFFER_SIZE 1024

/************* FORMATTED STRING FOR HELP BUILT IN **************/

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change the shell working directory.\n\n"\
"	If no argument is given to cd the command will be interpreted\n"\
"	as cd $HOME.\n"\
"	if the argumenthelp is - (cd -), the command will be interpreted\n"\
"	as cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit of the simple-shell.\n\n"\
"	Exits the shell with a status of N.  If N is omitted, the exit status\n"\
"	is that of the last command executed.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	Print environment.\n\n"\
"	The env command will be print a complete list of enviroment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Change or add an environment variable.\n\n"\
"	initialize a new environment variable, or modify an existing one\n"\
"	When there are not correct numbers of arguments print error message.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function deletes one variable from the environment.\n\n"\
"	Wen there are not correct numbers of arguments print error message.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Display information about builtin commands.\n\n"\
"	Displays brief summaries of builtin commands.  If BUILTIN_NAME is\n"\
"	specified, gives detailed help on all commands matching BUILTIN_NAME,\n"\
"	otherwise the list of help topics is printed BUILTIN_NAME list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifiying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"


#endif

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


int check_logic_ops(char *array_commands[], int i, char array_operators[]);



int print_alias(data_of_program *data, char *alias);
char *get_alias(data_of_program *data, char *name);
int set_alias(char *alias_string, data_of_program *data);
int built_exit(data_of_program *data);
int built_cd(data_of_program *data);
int set_work_directory(data_of_program *data, char *new_dir);
int built_help(data_of_program *data);
int built_alias(data_of_program *data);
int unset_env(data_of_program *data);
int set_env(data_of_program *data);
int built_env(data_of_program *data);
char *env_get(char *key, data_of_program *data);
int env_set(char *key, char *value, data_of_program *data);
int env_rm(char *key, data_of_program *data);
void put_env(data_of_program *data);
int execute(data_of_program *data);
int buffer_add(char *buffer, char *str_to_add);
void expand_alias(data_of_program *data);
void expand_var(data_of_program *data);
int find_path(data_of_program *data);
char **tokenize_path(data_of_program *data);
int check_file(char *full_path);
void free_recurrent_data(data_of_program *data);
void free_all_data(data_of_program *data);
void free_array_of_pointers(char **array);
int _getline(data_of_program *data);
/*void clear_array_commands(char *array_commands[], char array_operators[]);*/
void shift_arrays_left(char *array_commands[], char array_operators[]);
int built_list(data_of_program *data);
void long_to_string(long number, char *string, int base);
int _atoi(char *s);
int count_characters(char *string, char character);
int _print_error(int errorcode, data_of_program *data);
int _put(char *string);
int _putchar(char *string);
int main(int argc, char *argv[], char *env[]);
void handle_ctrl_c(int opr UNUSED);
void inicialize_data(data_of_program *data, int argc,
char *argv[], char **env);
void sisifo(char *prompt, data_of_program *data);
int str_len(const char *string);
char *str_dup(const char *string);
int str_compare(const char *string1, const char *string2, int number);
char *str_concat(const char *string1, const char *string2);
void str_rev(char *string);
char *_strtok(char *line, char *delim);
void tokenize(data_of_program *data);



char *expand_exit_status(char *line);
char *expand_process_id(char *line);
char *expand_variables_in_line(char *line, data_of_program *data);


/* Function prototype */

/*int check_logic_ops(char *array_commands[], int i, char array_operators[]);*/
void split_commands_and_operators(char *buff, char *array_commands[],
char array_operators[]);

int check_logic_ops(char *array_commands[], int i, char array_operators[]);
void clear_array_commands(char *array_commands[]);
#endif
