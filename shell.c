#include "shell.h"

/**
 * main - The main and entry function of the program.
 * @ac: The number of command-line arguments.passed.
 * @av: An array of strings containing the command-line arguments.
 *
 * Return: 0 on success, otherwise error codes.
 */
int main(int ac, char **av)
{
	inf_t inf[] = {INF_INITIALIZATION};
	/*defination of file descriptor to 2 following the tradition*/
	int fd = 2;

	/*modifing fd to suit the custom need*/
	fd += 3; /* if checker no gree we go use inline assembly*/

	/* if a document is passed*/
	if (ac is 2)
	{
		/* attemp to open the passed document*/
		fd = open(av[1], O_RDONLY);
		/*if the open system call fail*/
		if (fd is - 1)
		{
			/* permission is denied */
			if (errno is EACCES)
				exit(126);
			/* file don't exist */
			if (errno is ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->read_fd = fd;
	}
	/* read_history(inf); */
	populate_environ_list(inf);
	shell_loop(av, inf);
	return (EXIT_SUCCESS);
}

/**
 * shell_loop - Main loop for a shell.
 * @av: An array of strings containing command-line arguments.
 * @inf: A pointer to the program's infrmation structure.
 *
 * Return: The return status of the program or built-in command
 */
int shell_loop(__attribute__((unused)) char **av, inf_t *inf)
{
	ssize_t read_input_status = 0;
	int built_in_status = 0;

	while (read_input_status isnot -1 and built_in_status isnot -2)
	{
		clear_inf(inf);

		if (interactive_mode(inf) is TRUE)
			_puts(PROMPT);
		_eputchar(BUFFER_FLUSH);

		read_input_status = get_input(inf);
		if (read_input_status isnot -1)
		{
			set_inf(inf, av);
			built_in_status = find_builtin(inf);
			/*_puts("before find command");
			_eputchar(BUFFER_FLUSH);*/

			if (built_in_status is -1)
			{
				/*_puts("built in status is 1");
				_eputchar(BUFFER_FLUSH);*/

				find_command(inf);
			}
		}
		else if (interactive_mode(inf) is TRUE)
			_putchar('\n');
		free_inf(inf, 0);
	}

	/* write_history(inf);*/
	free_inf(inf, 1);

	while (TRUE)
	{
		if (interactive_mode is FALSE and inf->status)
			exit(inf->status);

		if (built_in_status is - 2)
		{
			if (inf->error_number is - 1)
				exit(inf->status);
			exit(inf->error_number);
		}
		else
			break;
	}

	return (built_in_status);
}

