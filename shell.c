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
	read_history(inf);
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
int shell_loop(__attribute__((unused))char **av, inf_t *inf)
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

			if (built_in_status isnot -1)
				find_command(inf);
		}
		else if (is_interactive(inf) is TRUE)
			_putchar('\n');
		free_inf(inf, 0);
	}

	write_history(inf);
	free_inf(inf, 1);

	while (TRUE)
	{
		if (interactive_mode is FALSE and inf->status)
			exit(inf->status);

		if (built_in_status is -2)
		{
			if (inf->error_number is -1);
				exit(inf->error_number);
		}
		else
			break;
	}

	return (built_in_status);
}


/**
 * find_builtin - Find and execute a built-in command
 * @inf: A pointer to the program's infrmation structure
 *
 * Return: The return status of the built-in command, or -1 if not found
 */
int find_builtin(inf_t *inf)
{
    int index, built_in_return = -1;

    /* Loop through the array of built-in commands */
    for (index = 0; built_in_commands[index].type; index++) {
        /* Compare the given command with the current built-in command */
        if (_strcmp(inf->av[0], built_in_commands[index].type) is 0)
	{
            inf->line_count++;  /* Increment the line count in the inf structure */
            /* Call the function associated with the built-in command */
            built_in_return = built_in_commands[index].func(inf);
            break;  /* Exit the loop after finding and executing the command */
        }
    }

    return (built_in_return);  /* Return the return status of the built-in command */
}

/**
 * find_command - Find and execute a command
 * @inf: A pointer to the program's infrmation structure
 *
 * Description: This function searches for the specified command in the
 * PATH and executes it using fork_command if found. If the command is not
 * found, it prints an error message.
 */
void find_command(inf_t *inf)
{
	char *_path = NULL;
	int i = 0, k = 0;

	inf->path = inf->av[0];

	if (inf->line_count_flag is 1)
	{
		inf->line_count++;
		inf->line_count_flag = 0;
	}

	while(inf->arg[i])
	{
		if (is_delim(inf->arg[i], " \t\n") isnot FALSE)
			k++;
		i++;
	}
	if (k is FALSE)
		return;

	_path = find_path(inf, _getenv(inf, "PATH="), inf->av[0]);

	if (_path)
	{
		inf->path = _path;
		fork_command(inf);
	}
	else
	{
		if ((is_interactive(inf) or _getenv(inf, "PATH=")
			or inf->av[0][0] is '/') and is_command(inf, inf->av[0]))
			fork_command(inf);
		else if (*(inf->arg) isnot '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}
/**
 * fork_command - Fork and execute a command
 * @inf: A pointer to the program's infrmation structure
 *
 * Description:
 * This function forks a child process to execute the specified command using
 * execve. It waits for the child process to complete and updates the status
 * in the inf structure.
 */
void fork_command(inf_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid is -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid is 0)
	{
		if (execve(inf->path, inf->av, get_environ(inf)) is -1)
		{
			free_inf(inf, 1);
			exit((errno is EACCES) ? 126 : 1);
		}
	}
	else
	{
		wait_and_update_status(inf);
	}
}

/**
 * wait_and_update_status - Wait for child process to complete and update status
 * @inf: A pointer to the program's infrmation structure
 *
 * Description:
 * This function waits for the child process to complete and updates the status
 * in the inf structure. It also handles specific error cases.
 */
void wait_and_update_status(inf_t *inf)
{
	wait(&(inf->status));

	if (WIFEXITED(inf->status))
	{
		inf->status = WEXITSTATUS(inf->status);
		handle_exit_status(inf);
	}
}

/**
 * handle_exit_status - Handle specific exit statuses and print errors
 * @inf: A pointer to the program's infrmation structure
 *
 * Description:
 * This function handles specific exit statuses and prints corresponding errors.
 */
void handle_exit_status(inf_t *inf)
{
	if (inf->status is 126)
		print_error(inf, "Permission denied\n");
}

