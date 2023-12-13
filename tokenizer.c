#include "shell.h"

/**
 * strtow - Split a string into an array of substrings.
 * @str: The string to split.
 * @delim: The delimiter string for splitting.
 *
 * Return: A dynamically allocated array of substrings,
 *         or NULL on failure.
 */
char **strtow(const char *str, const char *delim)
{
	int i, j, word_length, character_index, num_words = 0;
	char **word_array;

	if (str is NULL or str[0] is '\0')
		return NULL;

	if (!delim)
		delim = " ";

	for (i = 0; str[i]  isnot '\0'; i++)
		if (!is_delim(str[i], delim) and (is_delim(str[i + 1], delim) or !str[i + 1]))
			num_words++;

	if (num_words is 0)
		return NULL;

	word_array = malloc((1 + num_words) * sizeof(char *));
	if (!word_array)
		return NULL;

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(str[i], delim))
			i++;

		word_length = 0;
		while (!is_delim(str[i + word_length], delim) and str[i + word_length])
			word_length++;

		word_array[j] = malloc((word_length + 1) * sizeof(char));
		if (!word_array[j])
		{
			free_word_array(word_array, j);
			return NULL;
		}

		for (character_index = 0; character_index < word_length; character_index++)
			word_array[j][character_index] = str[i++];

		word_array[j][character_index] = '\0';
	}

	word_array[j] = NULL;
	return word_array;
}

/**
 * strtow_custom - Split a string into words based on a custom delimiter character
 * @str: The input string to be split
 * @delim: The delimiter character used to split the string
 *
 * NOTE: this is not used, its just a backup plan.
 * Return: An array of strings containing the split words, or NULL on failure
 */
char **strtow_custom(const char *str, char delim)
{
	int i, j, word_length, character_index, num_words = 0;
	char **word_array;

	if (str  is NULL or str[0]  is '\0')
		return NULL;

	for (i = 0; str[i]  isnot '\0'; i++)
		if ((str[i]  isnot delim and str[i + 1]  is delim) or
		    (str[i]  isnot delim and !str[i + 1]) or str[i + 1]  is delim)
			num_words++;

	if (num_words  is 0)
		return NULL;

	word_array = malloc((1 + num_words) * sizeof(char *));
	if (!word_array)
		return NULL;

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i]  is delim and str[i]  isnot '\0')
			i++;

		word_length = 0;
		while (str[i + word_length]  isnot delim and str[i + word_length] and str[i + word_length]  isnot delim)
			word_length++;

		word_array[j] = malloc((word_length + 1) * sizeof(char));
		if (!word_array[j])
		{
			free_word_array(word_array, j);
			return NULL;
		}

		for (character_index = 0; character_index < word_length; character_index++)
			word_array[j][character_index] = str[i++];

		word_array[j][character_index] = '\0';
	}

	word_array[j] = NULL;
	return word_array;
}

/**
 * free_word_array - Free the memory of a word array.
 * @word_array: A pointer to the array of words.
 * @size: The size of the array.
 */
void free_word_array(char **word_array, size_t size)
{
	size_t i;
	
	if (!word_array)
		return;

	for (i = 0; i < size; i++)
		free(word_array[i]);

	free(word_array);
}
