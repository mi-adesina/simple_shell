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

#include <unistd.h>

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
