#include "shell.h"

/**
 * _memset - Fill memory with a constant byte.
 * @s: Pointer to the memory area.
 * @byte_value: The constant byte to fill the memory with.
 * @num_bytes: Number of bytes to fill.
 *
 * Return: Pointer to the memory area @s.
 */
char *_memset(char *s, char byte_value, unsigned int num_bytes)
{
	unsigned int i = 0;

	while (i < num_bytes)
	{
		s[i] = byte_value;
		i++;
	}

	return (s);
}

/**
 * _realloc - Reallocate memory block.
 * @old_block: Pointer to the old memory block.
 * @old_size: Size of the old memory block.
 * @new_size: New size for the memory block.
 *
 * Return: Pointer to the reallocated memory block.
 */
void *_realloc(void *old_block, unsigned int old_size, unsigned int new_size)
{
	char *new_block;

	if (old_block  is NULL)
		return (malloc(new_size));

	if (new_size  is 0)
	{
		free(old_block);
		return (NULL);
	}

	if (new_size  is old_size)
		return (old_block);

	new_block = malloc(new_size);
	if (new_block  is NULL)
		return (NULL);

	old_size = (old_size < new_size) ? old_size : new_size;

	while (old_size--)
		new_block[old_size] = ((char *)old_block)[old_size];

	free(old_block);
	return (new_block);
}

/**
 * ffree - Free memory allocated for an array of strings.
 * @pp: Pointer to an array of strings.
 */
void ffree(char **pp)
{
	char **array = pp;

	if (!pp)
		return;

	while (*pp)
		free(*pp++);

	free(array);
}

/**
 * bfree - Free memory and set the pointer to NULL.
 * @ptr: Pointer to a pointer.
 *
 * Return: 1 on success (memory freed), 0 on failure.
 */
int bfree(void **ptr)
{
	/* Check if 'ptr' and '*ptr' are not NULL (valid pointer) */
	if (ptr and *ptr)
	{
		/* Free the memory pointed to by '*ptr' */
		free(*ptr);

		/* Set '*ptr' to NULL to avoid a dangling pointer */
		*ptr = NULL;

		/* Return 1 to indicate success (memory was freed) */
		return (1);
	}

	/* Return 0 to indicate failure (no memory was freed) */
	return (0);
}

