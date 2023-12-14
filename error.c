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
	bool to_write = c is BUFFER_FLUSH or i >= WRITE_BUFFER_SIZE;
	bool is_c_not_buffer_flush = (c isnot BUFFER_FLUSH);

	if (to_write is TRUE)
	{
		write(STDERR_FILENO, buf, i);
		i = 0;
	}
	if (is_c_not_buffer_flush is TRUE)
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

	if (s  is FALSE)
		return (i);
	for (i = 0; s[i]  isnot '\0'; i++)
		_eputchar(s[i]);

	return (i);
}

/**
 * _erratoi - Convert a string to an integer with error handling.
 * @s: The input string to convert to an integer.
 *
 * Return: The converted integer, or -1 on error.
 */
int _erratoi(char *s)
{
	int index = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* Skip leading '+'  */

	for (index = 0; s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			result *= 10;
			result += (s[index] - '0');

			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1); /* Non-numeric character found. */
	}

	return (result);
}

/**
 * print_error - Print an error message with additional infrmation.
 * @inf: A pointer to the inf_t structure containing shell infrmation.
 * @estr: The error message to print.
 */
void print_error(inf_t *inf, char *estr)
{
	_eputs(inf->file_name);
	_eputs(": ");
	print_integer(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->av[0]);
	_eputs(": ");
	_eputs(estr);
}

