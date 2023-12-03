#include "shell.h"

/**
 * _eputchar - Write a character to the standard error stream with buffering.
 * @c: The character to write to stderr.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];
	bool to_write = (c == BUFFER_FLUSH) || (i >= WRITE_BUFFER_SIZE);
	bool is_c_not_buffer_flush = (c != BUFFER_FLUSH);

	if (to_write == TRUE)
	{
		write(STDERR_FILENO, buf, i);
		i = 0;
	}
	if (is_c_not_buffer_flush == TRUE)
	{
		buf[i] = c;
		i++;
	}
	return (1);
}

/**
 *_eputs - Print a string character by character to the standard error stream.
 * @s: The string to be printed to the standard error stream.
 */
int _eputs(char *s)
{
	int i = 0;

	if (s == FALSE)
		return (i);
	for (i = 0; s[i] != '\0'; i++)
		_eputchar(s[i]);
	
	return (i);
}
