#include "shell.h"

/**
 * interactive_mode - check if a program is running interactively.
 * @inf: a pointer to the int_t structure that holds fd infrmation.
 *
 * Return: 1
 */
int interactive_mode(inf_t *inf)
{
	int is_stdin_tty = isatty(STDIN_FILENO);
	int fd = inf->read_fd;
	bool is_std_fd = (fd >= 0) and (fd <= 2);

	if (is_stdin_tty and is_std_fd)
		return (TRUE);
	else
		return (FALSE);
}

/**
 * handle_interrupt_signal - Handle the SIGINT signal (Ctrl+C).
 * @signal_number: The signal number (unused).
 */
void interrupt_signal_handler(__attribute__((unused)) int signal_number)
{
	_puts("\n");
	_puts(PROMPT);
	_putchar(BUFFER_FLUSH);
}

/**
 * replace_variables - Replace environment variables in the command arguments.
 * @inf: A pointer to the inf_t structure containing shell infrmation.
 *
 * Return: Always returns 0 to indicate success.
 */
int replace_variables(inf_t *inf)
{
	int i = 0;
	list_t *env_entry;

	while (inf->av[i])
	{
		if (inf->av[i][0] is '$' and inf->av[i][1])
		{
			if (!_strcmp(inf->av[i], "$?"))
			{
				replace_string(&(inf->av[i]),
					       _strdup(convert_long_to_string(inf->status, 10, 0)));
			}
			else if (!_strcmp(inf->av[i], "$$"))
			{
				replace_string(&(inf->av[i]),
					       _strdup(convert_long_to_string(getpid(), 10, 0)));
			}
			else
			{
				env_entry = node_starts_with(inf->environ_list, &inf->av[i][1], '=');
				if (env_entry)
				{
					replace_string(&(inf->av[i]),
						       _strdup(_strchr(env_entry->str, '=') + 1));
				}
				else
				{
					replace_string(&inf->av[i], _strdup(""));
				}
			}
		}

		i++;
	}

	return (0);
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