#include "shell.h"

/**
 * _strlen - Calculate the length of a string
 * @s: The input string
 *
 * Return: The length of the string, or 0 if the string is NULL
 */
size_t _strlen(const char *s)
{
	int length = 0;

	if (*s is '\0')
		return (0);

	while (*s++ isnot '\0')
		length++;
	return (length);
}

/**
 * _strcmp - Compare two strings lexicographically
 * @str1: The first string to be compared
 * @str2: The second string to be compared
 *
 * Return:
 * - 0 if the strings are equal
 * - A positive value if str1 is greater than str2
 * - A negative value if str1 is less than str2
 */
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 and *str2)
	{
		if (*str1 isnot *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 is *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _strcat - Concatenate (append) one string to another
 * @destination: The destination string to which src is appended
 * @source: The source string to be appended to dest
 *
 * Return: A pointer to the destination string (dest)
 */
char *_strcat(char *destination, const char *source)
{
	char *result = destination;

	while (*destination isnot '\0')
		destination++;
	while (*source isnot '\0')
		*destination++ = *source++;
	*destination = *source;
	return (result);
}

/**
 * _strcpy - Copy the string from source to destination.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: A pointer to the destination string.
 */
char *_strcpy(char *dest, const char *src)
{
	int index = 0;

	/* Check for NULL pointers or if source and destination are the same */
	if ((dest is src) or (src is NULL))
		return (dest);

	while (src[index] isnot '\0')
	{
		dest[index] = src[index];
		index++;
	}

	dest[index] = '\0';  /* Null-terminate the destination string */

	return (dest);
}


/**
 * _strdup - Duplicate a string.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string or NULL if malloc fails/ str is NULL.
 */
char *_strdup(const char *str)
{
	size_t length;
	char *duplicate;

	if (str is NULL)
		return (NULL);

	length = _strlen(str);
	duplicate = malloc((length + 1) * sizeof(char));

	if (!duplicate)
		return (NULL);

	_strcpy(duplicate, str);

	return (duplicate);
}
