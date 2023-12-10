#include "shell.h"

/**
 * interactive_mode - check if a program is running interactively. 
 * @inf: a pointer to the int_t structure that holds fd infrmation.
 * 
 * Return: 1
 */
int interactive_mode(inf_t *inf)
{
	int is_stdin_tty = isatty(STDIN_FILENO);
	int fd = inf->read_fd;
	bool is_std_fd = (fd >= 0) and (fd <= 2);

	if (is_stdin_tty and is_std_fd)
		return (TRUE);
	else
		return (FALSE);
}

/**
 * handle_interrupt_signal - Handle the SIGINT signal (Ctrl+C).
 * @signal_number: The signal number (unused).
 */
void interrupt_signal_handler(__attribute__((unused))int signal_number)
{
	_puts("\n");
	_puts(PROMPT);
	_putchar(BUFFER_FLUSH);
	
}