#ifndef SHELL_H
#define SHELL_H

/* useful standard libraries */
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define bool int
#define FALSE 0 
#define TRUE 1
#define or ||
#define and &&
#define is ==
#define isnot !=


/* useful constant macros */
#define PROMPT "#ghengis_khan$ "
#define BUFFER_FLUSH -1
#define WRITE_BUFFER_SIZE 4096
#define READ_BUFFER_SIZE 4096
#define MY_GETLINE TRUE
#define MY_STRTOK TRUE
#define COMMAND_NORM 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3
#define CONVERT_LOWER_CASE	1
#define CONVERT_UNSIGNED	2

extern char **environ;

/**
 * struct liststr - Structure for a linked list of integer-string pairs
 * @num: An integer value
 * @str: A string value
 * @next: Pointer to the next element in the list
 */
typedef struct list_str
{
	int number;
	char *str;
	struct list_str *next;
} list_t;


/*inf structure*/
typedef struct pass_information
{
	int ac;
	int read_fd;
	int line_count_flag;
	int error_number;
	int command_buffer_type;
	int history_count;
	int status;
	int environ_changed;

	unsigned int line_count;

	char *file_name;
	char *arg;
	char *path;
	char **command_buffer;
	char **av;
	char **environ;

	list_t *history_list;
	list_t *environ_list;
	list_t *alias_list;
} inf_t;

/* infromation structure initialization*/
#define INF_INITIALIZATION {0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}

/**
 *struct BuiltInCommand - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct BuiltInCommand {
    char *type;
    int (*func)(inf_t *);
}command_table;



/* built_in_alias.c */
int print_alias(list_t *node);
int _myalias(inf_t *inf);
int set_alias(inf_t *inf, char *alias_string);
int unset_alias(inf_t *inf, char *unset);
int replace_alias(inf_t *inf);

/* built_in.c */
int _myexit(inf_t *inf);
int _cd(inf_t *inf);
int _myhelp(inf_t *inf);
int _history(inf_t *inf);

/* commands.c */
int find_builtin(inf_t *inf);
void find_command(inf_t *inf);
void fork_command(inf_t *inf);
void wait_and_update_status(inf_t *inf);
void handle_exit_status(inf_t *inf);

/* dynamic memory */
char *_memset(char *s, char byte_value, unsigned int num_bytes);
void *_realloc(void *old_block, unsigned int old_size, unsigned int new_size);
void ffree(char **pp);
int bfree(void **ptr);

/* environ_helper_functions.c */
size_t print_and_count_environment_variables(const list_t *head);
char **get_environ(inf_t *inf);
int _unsetenv(inf_t *inf, char *var);
int _setenv(inf_t *inf, char *var, char *value);

/* environ.c */
int populate_environ_list(inf_t *inf);
int _myenv(inf_t *inf);
char *_getenv(inf_t *inf, const char *name);
int _mysetenv(inf_t *inf);
int _myunsetenv(inf_t *inf);

/* error.c */
int _eputchar(char c);
int _eputs(char *s);
int _erratoi(char *s);
void print_error(inf_t *inf, char *estr);

/* even_more_strings.c */
char *dup_characters(char *pathstr, int start_idx, int end_idx);
int is_delim(char character, const char *delimiters);
char *convert_long_to_string(long int num, int base, int cFlag);

/* getline*/
int _getline(inf_t *inf, char **ptr, size_t *length);
ssize_t read_buffer(char *buf, size_t *buf_pos, inf_t *inf);
ssize_t get_input(inf_t *inf);
ssize_t input_buf(inf_t *inf, char **buf, size_t *len);

/* inf_structure.c */
void clear_inf(inf_t *inf);
void set_inf(inf_t *inf, char **av);
void free_inf(inf_t *inf, int all);

/* io_functions.c */
int _putchar(char c);
int _puts(char *s);
int _putfd(char character, int file_descriptor);
int _putsfd(char *input_string, int fd);
int print_integer(int input, int fd);

/* linked_list.c */
list_t *add_node(list_t **head, const char *str, int number);
list_t *add_node_end(list_t **head, const char *str, int number);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);
size_t list_len(const list_t *head);

/* more_linked_list.c */
ssize_t get_node_index(list_t *head, list_t *node);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *head);
list_t *node_starts_with(list_t *node, char *prefix, char c);

/* more strings*/
char *_strncpy(char *destination, const char *source, size_t n);
char *_strchr(char *string, char character);
char *_strncat(char *destination, const char *source, int n);
char *starts_with(const char *haystack, const char *needle);
int replace_string(char **original_string, char *new_string);

/* parse.c */
int is_command(inf_t *inf, char *path);
char *find_path(inf_t *inf, char *pathstr, char *command);

/* shell_helper.c */
void remove_comments(char *input_string);
int interactive_mode(inf_t *inf);
void interrupt_signal_handler(int signal_number);
int is_chain(inf_t *inf, char *input, size_t *position);
void check_chain(inf_t *inf, char *buffer, size_t *position, size_t i, size_t buffer_length);

/* shell.c */
int shell_loop(char **av, inf_t *inf);

/* strings.c */
size_t _strlen(const char *s);
int _strcmp(const char *str1, const char *str2);
char *_strcat(char *destination, const char *source);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);

/* tokenizer.c */
char **strtow(const char *str, const char *delim);
char **strtow_custom(const char *str, char delim);
void free_word_array(char **word_array, size_t size);

/*ungrouped.c*/
int replace_variables(inf_t *inf);

#endif