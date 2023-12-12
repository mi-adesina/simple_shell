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
	list_t *alias_list



} inf_t;

/* infromation structure initialization*/
#define INF_INITIALIZATION {0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}

/* shell.c */
int shell_loop(char **av, inf_t *inf);

/* error.c */
int _eputs(char *s);
int _eputchar(char c);

/* strings.c */
size_t _strlen(const char *s);
int _strcmp(const char *str1, const char *str2);
char *_strcat(char *destination, const char *source);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);


/* more strings*/
char *_strncpy(char *destination, const char *source, size_t n);
char *_strchr(char *string, char character);
char *_strncat(char *destination, const char *source, int n);
char *starts_with(const char *haystack, const char *needle);

/* IO functions*/
int _putchar(char c);
int _puts(char *s);

/* ungrouped */
int interactive_mode(inf_t *inf);
void clear_inf(inf_t *inf);
void interrupt_signal_handler(__attribute__((unused))int signal_number);

/* getline*/
int _getline(inf_t *inf, char **ptr, size_t *length);
ssize_t read_buffer(char *buf, size_t *buf_pos, inf_t *inf);
ssize_t get_input(inf_t *inf);
ssize_t input_buf(inf_t *inf, char **buf, size_t *len);

/* dynamic memory */
char *_memset(char *s, char byte_value, unsigned int num_bytes);
void *_realloc(void *old_block, unsigned int old_size, unsigned int new_size);
void ffree(char **pp);
int bfree(void **ptr);

/* environ.c */
int populate_env_list(inf_t *inf);
int _myenv(inf_t *inf);
char *_getenv(inf_t *inf, const char *name);
int _mysetenv(inf_t *inf);
int _myunsetenv(inf_t *inf);

/* environ_helper_functions.c */
size_t print_and_count_environment_variables(const list_t *head);
char **get_environ(inf_t *inf);
int _unsetenv(inf_t *inf, char *var);
int _setenv(inf_t *inf, char *var, char *value)


/* linked_list.c */
list_t *add_node(list_t **head, const char *str, int number);
list_t *add_node_end(list_t **head, const char *str, int number);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);


#endif