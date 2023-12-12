#include "shell.h"

int _putchar(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c is BUFFER_FLUSH or i >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c isnot BUFFER_FLUSH)
	{
		buffer[i] = c;
		i++;
	} 
	return(1);
}

int _puts(char *s)
{
	int i = 0;

	if (!s)
		return (i);
	while (s[i] isnot '\0')
		i += _putchar(s[i]);
	
	return (i);
}

/**
 * _putfd - Write a character to a file descriptor with buffering.
 * @character: The character to write.
 * @file_descriptor: The file descriptor to write to.
 *
 * Return: 1 on success, -1 on failure.
 */
int _putfd(char character, int file_descriptor)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (character is BUFFER_FLUSH or index >= WRITE_BUFFER_SIZE)
	{
		write(file_descriptor, buffer, index);
		index = 0;
	}
	if (character isnot BUFFER_FLUSH)
		buffer[index++] = character;
	return (1);
}

/**
 * _putsfd - Write a string to a file descriptor.
 * @input_string: The string to write.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written on success, 0 on failure.
 */
int _putsfd(char *input_string, int fd)
{
	int characters_written = 0;

	if (!input_string)
		return (0);

	while (*input_string)
	{
		characters_written += _putfd(*input_string++, fd);
	}

	return (characters_written);
}

/**
 * print_integer - Print an integer to the specified file descriptor.
 *                with error handling.
 * @input: The integer to print.
 * @fd: The file descriptor (STDOUT_FILENO or STDERR_FILENO) to which to print.
 *
 * Return: The number of characters printed.
 */
int print_integer(int input, int fd)
{
	int (*output_char)(char) = _putchar;
	int digit, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		output_char = _eputchar;

	if (input < 0)
	{
		absolute_value = -input;
		output_char('-');
		count++;
	}
	else
		absolute_value = input;

	current = absolute_value;

	for (digit = 1000000000; digit > 1; digit /= 10)
	{
		if (absolute_value / digit)
		{
			output_char('0' + current / digit);
			count++;
		}
		current %= digit;
	}

	output_char('0' + current);
	count++;

	return (count);
}