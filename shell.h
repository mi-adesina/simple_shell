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

/* useful constant macros */
#define PROMPT "#ghengis_khan$ "
#define BUFFER_FLUSH -1
#define WRITE_BUFFER_SIZE 4096

#define bool int
#define FALSE 0 
#define TRUE 1
#define or ||
#define and &&
#define is ==
#define isnot !=

/*inf structure*/
typedef struct pass_information
{
	int ac;
	int read_fd;
	char **av;
	char *arg;
	char *path;
} inf_t;

/* infromation structure initialization*/
#define INF_INITIALIZATION {0, 0, NULL, NULL, NULL}

/* shell.c */
int shell_loop(char **av, inf_t *inf);

/* error.c */
int _eputs(char *s);
int _eputchar(char c);

/* strings.c */
size_t _strlen(const char *s);
int _strcmp(const char *str1, const char *str2);
char *_strcat(char *destination, const char *source);
char *starts_with(const char *haystack, const char *needle);

/* IO functions*/
int _putchar(char c);
int _puts(char *s);

/* ungrouped */
int interactive_mode(inf_t *inf);
void clear_inf(inf_t *inf);

/* getline*/
ssize_t get_input(inf_t *inf)
#endif