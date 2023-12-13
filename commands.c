#include "shell.h"

/**
 * find_builtin - Find and execute a built-in command
 * @inf: A pointer to the program's infrmation structure
 *
 * Return: The return status of the built-in command, or -1 if not found
 */
int find_builtin(inf_t *inf)
{
	int index, built_in_return = -1;
	/* Array of built-in commands along with their corresponding functions */
	command_table built_in_commands[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _cd},
		{"alias", _myalias},
		/* {"history", _history},*/
		{NULL, NULL} /* Sentinel entry to mark the end of the array */
	};

	/* Loop through the array of built-in commands */
	for (index = 0; built_in_commands[index].type; index++)
	{
		/* Compare the given command with the current built-in command */
		if (_strcmp(inf->av[0], built_in_commands[index].type) is 0)
		{
			inf->line_count++; /* Increment the line count in the inf structure */
			/* Call the function associated with the built-in command */
			built_in_return = built_in_commands[index].func(inf);
			break; /* Exit the loop after finding and executing the command */
		}
	}
	/* Return the return status of the built-in command */
	return (built_in_return);
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

	while (inf->arg[i])
	{
		if (!is_delim(inf->arg[i], " \t\n"))
			k++;
		i++;
	}
	if (!k)
		return;

	_path = find_path(inf, _getenv(inf, "PATH="), inf->av[0]);

	if (_path)
	{
		inf->path = _path;
		fork_command(inf);
	}
	else
	{
		if ((interactive_mode(inf) or _getenv(inf, "PATH=") or inf->av[0][0] is '/') and is_command(inf, inf->av[0]))
			fork_command(inf);
		else if (*(inf->arg)isnot '\n')
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
	if (child_pid is - 1)
	{
		perror("Error:");
		return;
	}

	if (child_pid is 0)
	{
		if (execve(inf->path, inf->av,
			get_environ(inf)) is - 1)
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
 * wait_and_update_status - Wait for
 * child process to complete and update status
 * @inf: A pointer to the program's infrmation
 * structure
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
 * @inf: A pointer to the program's infrmation
 * structure
 *
 * Description:
 * This function handles specific exit statuses and prints corresponding errors.
 */
void handle_exit_status(inf_t *inf)
{
	if (inf->status is 126)
		print_error(inf, "Permission denied\n");
}
