#include "shell.h"

/**
 * dup_characters - Duplicate characters from a source string within
 *             a specified range.
 * @pathstr: The source string to duplicate characters from.
 * @start_idx: The starting index (inclusive) for character duplication.
 * @end_idx: The ending index (exclusive) for character duplication.
 *
 * Return: pointer to new buffer
 */
char *dup_characters(char *pathstr, int start_idx, int end_idx)
{
        static char duplicated_buffer[1024];
        int source_idx = start_idx, duplicated_idx = 0;

        while (source_idx < end_idx)
        {
                if (pathstr[source_idx] != ':')
                {
                        duplicated_buffer[duplicated_idx++] = pathstr[source_idx];
                }
                source_idx++;
        }
        duplicated_buffer[duplicated_idx] = '\0';
        return duplicated_buffer;
}

/**
 * is_delim - Checks if a character is a delimiter.
 * @character: The character to check.
 * @delimiters: A string of delimiter characters.
 *
 * Return: 1 if 'character' is a delimiter, 0 otherwise.
 */
int is_delim(char character, char *delimiters)
{
        /* Iterate through the 'delimiters' string. */
        while (*delimiters)
        {
                /* Check if the current character matches 'character'. */
                if (*delimiters == character)
                {
                        return 1; /* 'character' is a delimiter. */
                }

                delimiters++; /* Move to the next character in 'delimiters'. */
        }

        return 0; /* 'character' is not a delimiter. */
}

/**
 * convert_long_to_string - Convert a long integer to a string representation with options.
 * @num: The long integer to convert.
 * @base: The base for the conversion (e.g., 2 for binary, 10 for decimal, 16 for hexadecimal).
 * @cFlag: Argument flags.
 *
 * Return: A pointer to the resulting string.
 */
char *convert_long_to_string(long int num, int base, int cFlag)
{
	unsigned long absolute_value = num;
	static char *cChar;
	static char buffer[50];
	char sign_character = 0;
	char *result_ptr;
	

	if (!(cFlag & CONVERT_UNSIGNED) && num < 0)
	{
		absolute_value = -num;
		sign_character = '-';
	}

	cChar = cFlag & CONVERT_LOWER_CASE ? "0123456789abcdef" : "0123456789ABCDEF";
	result_ptr = &buffer[49];
	*result_ptr = '\0';

	do {
		*--result_ptr = cChar[absolute_value % base];
		absolute_value /= base;
	} while (absolute_value != 0);

	if (sign_character)
		*--result_ptr = sign_character;

	return (result_ptr);
}

