#include "shell.h"

/**
 * remove_comments - Remove comments from a string by truncating it at the '#' character.
 * @input_string: Address of the string to modify.
 */
void remove_comments(char *input_string)
{
	int index;

	for (index = 0; input_string[index] != '\0'; index++)
	{
		if (input_string[index] == '#' && (!index || input_string[index - 1] == ' '))
		{
			input_string[index] = '\0';
			break;
		}
	}
}

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
