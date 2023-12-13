#include "shell.h"

/**
 * _myexit - Handle the shell exit behavior.
 * @inf: A pointer to the inf_t structure containing shell information.
 *
 * Return: -2 to indicate the shell should exit, or 1 if there is an error.
 */
int _myexit(inf_t *inf)
{
	int exit_status;

	if (inf->av[1])
	{
		exit_status = _erratoi(inf->av[1]);

		if (exit_status is -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputs(inf->av[1]);
			_eputchar('\n');
			return (1);
		}

		inf->error_number = exit_status;
		return (-2);
	}

	inf->error_number = -1;
	return (-2);
}

/**
 * _cd - Change the current working directory.
 * @inf: A pointer to the inf_t structure containing shell information.
 *
 * Return: 0 if the current directory is successfully changed, 1 on error.
 */
int _cd(inf_t *inf)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);

	if (!inf->av[1])
	{
		target_dir = _getenv(inf, "HOME=");
		if (!target_dir)
			chdir_ret = chdir((target_dir = _getenv(inf, "PWD=")) ? target_dir : "/");
		else
			chdir_ret = chdir(target_dir);
	}
	else if (_strcmp(inf->av[1], "-") is 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((target_dir = _getenv(inf, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_ret = chdir(inf->av[1]);

	if (chdir_ret is -1)
	{
		print_error(inf, "can't cd to ");
		_eputs(inf->av[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 * _myhelp - Display help or information.
 * @inf: A pointer to the inf_t structure containing shell information.
 *
 * Return: Always returns 0 to indicate success.
 */
int _myhelp(inf_t *inf)
{
	char **arguments;

	arguments = inf->av;

	_puts("help call works. Function not yet implemented \n");
        return (0);

	/* just a trick */
	if (0)
		_puts(*arguments); /* unused variable workaround */
	return (0);
}

/**
 * _history - Display the command history.
 * @inf: A pointer to the info_t structure containing shell information.
 *
 * Return: Always returns 0 to indicate success.
 */
int _history(inf_t *inf)
{
	print_list(inf->history_list);
	return (0);
}

