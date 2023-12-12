#include "shell.h"

/**
 * _strncpy - Copy at most n characters from source to destination.
 * @destination: The destination buffer.
 * @source: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *destination, const char *source, size_t n)
{
	size_t i;

	for (i = 0; (i < n - 1) and (source[i] isnot '\0'); i++)
	{
		destination[i] = source[i];
	}

	/* Explicitly null-terminate the destination string */
	destination[i] = '\0';

	return (destination);
}

/**
 * _strchr - Locate the first occurrence of a character in a string.
 * @string: The string to search.
 * @character: The character to find.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *_strchr(char *string, char character)
{
	while (*string isnot '\0')
        {
		if (*string is character)
			return (string);
		string++;
	}

	/* Include the case where the character is the null terminator */
	if (*string is character)
		return (string);

	return (NULL);
}


/**
 * _strncat - Concatenate at most n characters from source to destination.
 * @destination: The destination buffer.
 * @source: The source string.
 * @n: The maximum number of characters to concatenate.
 *
 * Return: A pointer to the destination string.
 */
char *_strncat(char *destination, const char *source, int n)
{
	int dest_len = 0, src_len = 0;
	char *original_dest = destination;

	/* Find the length of the destination string */
	while (destination[dest_len] isnot '\0')
		dest_len++;

	/* Find the length of the source string */
	while ((source[src_len] isnot '\0') and (src_len < n))
	{
		destination[dest_len] = source[src_len];
		dest_len++;
		src_len++;
	}

	/* Null-terminate the concatenated string */
	if (src_len < n)
		destination[dest_len] = '\0';

	return (original_dest);
}

/**
 * starts_with - Check if a string starts with a specified substring
 * @haystack: The string to check
 * @needle: The substring to check for
 *
 * Return:
 * - A pointer to the character following the substring if found
 * - NULL if the string does not start with the substring
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle isnot '\0')
	{
		if (*needle isnot *haystack)
			return (NULL);
		needle++;
		haystack++;
	}
	return ((char *)haystack);
}

/**
 * replace_string - Replace the content of a string with a new string
 * @original_string: A pointer to the old string
 * @new_string: The new string to replace the old content
 *
 * Return: 1 if the replacement is successful, 0 otherwise
 */
int replace_string(char **original_string, char *new_string)
{
	free(*original_string);
	*original_string = new_string;
	return (1);
}


