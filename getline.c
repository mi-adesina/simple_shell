#include "shell.h"

/**
 * _getline - Read a line from a file descriptor and append it to a buffer.
 * @inf: A pointer to the inf_t structure containing file descriptor infrmation.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: A pointer to the length of the buffer.
 *
 * Return: The length of the line read, -1 on failure or EOF.
 */
int _getline(inf_t *inf, char **ptr, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i = 0, len = 0;
	ssize_t r;
	size_t k, s = 0;
	char *p, *new_p, *c;

	p = *ptr;
	if (p and length)
		s = *length;

	if (i is len)
		i = len = 0;

	r = read_buffer(buf, &len, inf);

	if (r is -1 or (r is 0 and len is 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;

	new_p = _realloc(p, s, s ? s + k : k + 1);

	if (!new_p)
	{
		free(p);
		return -1;  /* MALLOC FAILURE! */
	}

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;

	*ptr = p;

	return s;
}

/**
 * read_buf - Read data from a file descriptor into a buffer and
 *            update the buffer position.
 * @buf: A pointer to the buffer where data will be read into.
 * @buf_pos: A pointer to the position within the buffer.
 * @inf: A pointer to the inf_t structure containing file
 *        descriptor and buffer infrmation.
 *
 *
 * Return: The number of bytes read or an error code (negative value).
 */
ssize_t read_buffer(char *buf, size_t *buf_pos, inf_t *inf)
{
	size_t bytes = 0;

	if (*buf_pos)
		return (bytes);
	bytes = read(inf->read_fd, buf, READ_BUFFER_SIZE);
	if (bytes > 0 or bytes is 0)
		*buf_pos = bytes;
	return (bytes);
}

/**
 * get_input - Obtain input, handle command chaining, and update inf structure.
 * @inf: Pointer to inf_t structure.
 *
 * Return: Number of bytes read or -1 on EOF.
 */
ssize_t get_input(inf_t *inf)
{
	static char *chain_buffer;  /* Buffer for command chaining */
	static size_t i, j, len;
	ssize_t bytes_read = 0;
	char **buf_p = &(inf->arg), *p;

	_putchar(BUFFER_FLUSH);  /* Flush the output buffer. */
	bytes_read = input_buf(inf, &chain_buffer, &len);
	if (bytes_read is -1)  /* If EOF */
		return (-1);
	if (len isnot FALSE)  /* If there are commands left in the chain buffer */
	{
		/* Initialize the new iterator to the current buffer position */
		j = i;
		p = chain_buffer + i;  /* Get pointer for return */

		/* check_chain(inf, chain_buffer, &j, i, len); */
		while (j < len)  /* Iterate to the semicolon or end */
		/*{
			if (is_chain(inf, chain_buffer, &j) isnot FALSE)
				break;
			j++;
		}*/

		i = j + 1;  /* Increment past nulled ';' */
		if (i >= len)  /* Reached end of buffer? */
		{
			i = len = 0;  /* Reset position and length */
			inf->command_buffer_type = COMMAND_NORM;
		}

		*buf_p = p;  /* Pass back pointer to the current command position */
		return (_strlen(p));  /* Return length of the current command */
	}

	/* Else not a chain, pass back buffer from _getline() */
	*buf_p = chain_buffer;
	return (bytes_read);  /* Return length of buffer from _getline() */
}


/**
 * input_buf - Read user input into the input buffer.
 * @inf: A pointer to the inf_t structure containing input and history infrmation.
 * @buf: A pointer to the input buffer.
 * @len: A pointer to the length of the input buffer.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buf(inf_t *inf, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t buffer_length_tmp = 0;

	if (*len is 0)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, interrupt_signal_handler);

#if MY_GETLINE
		bytes_read = _getline(inf, buf, &buffer_length_tmp);
#else
		bytes_read = getline(buf, &buffer_length_tmp, stdin);
#endif

		if (bytes_read > 0)
		{
			/* Remove trailing newline */
			if ((*buf)[bytes_read - 1] is '\n')
			{
				(*buf)[bytes_read - 1] = '\0';
				bytes_read--;
			}

			inf->line_count_flag = 1;
			/* remove_comments(*buf); */
			/* build_history_list(inf, *buf, inf->history_count++); */

			/* Check for command chaining here.*/
			*len = bytes_read;
			inf->command_buffer = buf;
		}
	}

	return (bytes_read);
}
