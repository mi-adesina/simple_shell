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
	inf_t inf[] = { INF_INITIALIZATION };
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
		if (fd is -1)
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
	shell_loop(av, inf);
	return (EXIT_SUCCESS);
}

/**
 * shell_loop - Main loop for a shell.
 * @av: An array of strings containing command-line arguments.
 * @inf: A pointer to the program's information structure.
 *
 * Return: The return status of the program or built-in command
 */
int shell_loop(char **av, inf_t *inf)
{
	ssize_t read_input_status = 0;
	int built_in_status = 0;

	/* to be removed*/
	int i;
	for (i = 0; av[i]; i++)
	{
		printf("%s", av[i]);
	}


	while (read_input_status isnot -1 and built_in_status isnot -2)
	{
		clear_inf(inf);
		if (interactive_mode(inf) is TRUE)
			_puts(PROMPT);
		_eputchar(BUFFER_FLUSH);
		read_input_status = get_input(inf); 


	}

	return (0);

}
