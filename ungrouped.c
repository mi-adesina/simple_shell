#include "shell.h"


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
 * is_chain - Check for command chaining symbols and update command buffer type
 * @inf: A pointer to the infrmation structure
 * @input: The input string to be checked for chaining symbols
 * @position: A pointer to the current position in the input string
 *
 * Return: 1 if a command chaining symbol is found, 0 otherwise
 */
int is_chain(inf_t *inf, char *input, size_t *position)
{
	size_t currentPosistion = *position;

	while (input[currentPosistion] == '|' && input[currentPosistion + 1] == '|')
	{
		input[currentPosistion] = '\0';
		currentPosistion++;
		inf->command_buffer_type = COMMAND_OR;
	}
	if (input[currentPosistion] == '&' && input[currentPosistion + 1] == '&')
	{
		input[currentPosistion] = '\0';
		currentPosistion++;
		inf->command_buffer_type = COMMAND_AND;
	}
	else if (input[currentPosistion] == ';') /* Found end of this command */
	{
		input[currentPosistion] = '\0'; /* Replace semicolon with null */
		inf->command_buffer_type = COMMAND_CHAIN;
	}
	else
	{
		return 0;
	}

	*position = currentPosistion;
	return 1;
}

/**
 * check_chain - Check command chaining conditions and update
 *               buffer and position.
 * @inf: A pointer to the infrmation structure.
 * @buffer: The input buffer to be checked.
 * @position: A pointer to the current position in the buffer.
 * @i: The current position in the buffer.
 * @buffer_length: The length of the buffer.
 */
void check_chain(inf_t *inf, char *buffer, size_t *position, size_t i, size_t buffer_length)
{
	size_t currentPosistion = *position;

	if (inf->command_buffer_type == COMMAND_AND)
	{
		if (inf->status)
		{
			buffer[i] = '\0';
			currentPosistion = buffer_length;
		}
	}
	if (inf->command_buffer_type == COMMAND_OR)
	{
		if (!inf->status)
		{
			buffer[i] = '\0';
			currentPosistion = buffer_length;
		}
	}

	*position = currentPosistion;
}







