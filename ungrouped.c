#include "shell.h"

/**
 * interactive_mode - check if a program is running interactively. 
 * @inf: a pointer to the int_t structure that holds fd information.
 * 
 * Return: 1
 */
int interactive_mode(inf_t *inf)
{
	int is_stdin_tty = isatty(STDIN_FILENO);
	int fd = inf->read_fd;
	bool is_std_fd = (fd >= 0) && (fd <= 2);

	if (is_stdin_tty && is_std_fd)
		return (TRUE);
	else
		return (FALSE);
}

/**
 * clear_inf - reset a selected few fields within inf structure.
 * @inf: a pointer to the inf_t structure to reset.
 */
void clear_inf(inf_t *inf)
{
	inf->ac = 0;
	inf->av = NULL;
	inf->arg = NULL;
	inf->path = NULL;
}