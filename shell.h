#ifndef SHELL_H
#define SHELL_H


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#include <stddef.h>
#include <stdlib.h>




#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\0'




/* read and write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;




/* 1 */
char *str_concat(char *s1, char *s2);
size_t str_length(const char *string);
int _strcmp(const char *s1, const char *s2);
/* 2 */
void _flush_buffer(char *buf, int *index);
int _putchar(char c);
void _puts(char *str);
char *str_dup(char *string);
void str_copy(char *destination, const char *source);
char *starts_with(const char *string, const char *substring);
/* 3 */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t *head);
/* 4 */
size_t list_length(const list_t *head);
char **list_to_array(const list_t *head);
size_t print_list(const list_t *h);
list_t *find_node_with_prefix(const list_t *head, const char *prefix);
int _starts_with(const char *str, const char *prefix);
/* 5 */
int get_node_index(const list_t *head, const list_t *target);
int bfree(void **ptr);
/* 6 */
char **strtow(char *str, char *d);
char **split_string(char *str, char *delimiter, int *num_words);
/* 7 */
char *_memset(char *s, char b, unsigned int n);
void ffree(char **str_array);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
/* 8 */
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);
/* 9 */
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);
/* 10 */
int is_cmd(info_t *info, char *path);
char *dup_chars(const char *pathstr, int start, int stop);
char *find_path(info_t *info, const char *pathstr, const char *cmd);
/* 11 */
int main(int ac, char **av);
/* 12 */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int parse_history(info_t *info, char *buf);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
/* 13 */
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);
/* 14 */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);
/* 15 */
char *_strncpy(char *dest, const char *src, size_t n);
char *_strncat(char *dest, const char *src, size_t n);
char *_strchr(const char *s, int c)
/* 16 */
void _eputs(const char *str);
int _eputchar(char c);
int _putsfd(char *str, int fd);
/* 17 */
int safe_atoi(char *s);
void print_error(info_t *info, char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);
/* 18 */
int _myenv(info_t *info);
char *_getenv(info_t *info, const char *name);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);
/* 19 */
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);
/* 20 */
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *alias);
int set_alias(info_t *info, char *alias);
int _myalias(info_t *info);
/* 21 */
int interactive(info_t *info);
int is_delim(char c, const char *delim);
int _atoi(char *s);


#endif
