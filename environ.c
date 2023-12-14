#include "shell.h"

/**
 * populate_environ_list - Populate the inf_t structure's env field
 *                     with environment variables.
 * @inf: Pointer to the inf_t structure.
 *
 * Return: 0 on success, -1 on failure.
 */
int populate_environ_list(inf_t *inf)
{
	list_t *env_list = NULL;
	size_t index = 0;

	while (environ[index])
	{
		add_node_end(&env_list, environ[index], 0);
		index++;
	}

	inf->environ_list = env_list;
	return (0);
}

/**
 * _myenv - Print environment variables.
 * @inf: A pointer to the inf_t structure containing environment variables.
 *
 * Return: Always returns 0 to indicate success.
 */
int _myenv(inf_t *inf)
{
	print_and_count_environment_variables(inf->environ_list);
	return (0);
}

/**
 * _getenv - Get the value of an environment variable.
 * @inf: Pointer to the inf_t structure
 * containing the linked list of environment variables.
 * @name: Name of the environment variable to search for.
 *
 * Return: If the variable is found, return its value; otherwise, return NULL.
 */
char *_getenv(inf_t *inf, const char *name)
{
	list_t *current_node;
	char *variable_value;

	/* Check for NULL parameters */
	if (!inf or !name)
	{
		/* Handle the error (return an error code or print an error message) */
		return (NULL);
	}

	current_node = inf->environ_list;

	/* Traverse the linked list */
	while (current_node)
	{

		variable_value = starts_with(current_node->str, name);

		/* Check if a match is found */
		if (variable_value and * variable_value)
		{
			return (variable_value);
		}

		/* Move to the next node */
		current_node = current_node->next;
	}

	/* No match found */
	return (NULL);
}

/**
 * _mysetenv - Set or modify an environment variable.
 * @inf: A pointer to the inf_t structure containing environment variables.
 *
 *  Return: 0 on success, 1 on failure.
 */
int _mysetenv(inf_t *inf)
{
	if (inf->ac  isnot 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(inf, inf->av[1], inf->av[2]))
	{
		return (0);
	}

	return (1);
}

/**
 * _myunsetenv - Unset one or more environment variables.
 * @inf: A pointer to the inf_t structure containing environment variables.
 *
 * Return: 0 on success, 1 on failure.
 */
int _myunsetenv(inf_t *inf)
{
	int arg_index;

	if (inf->ac  is 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (arg_index = 1; arg_index < inf->ac; arg_index++)
	{
		if (_unsetenv(inf, inf->av[arg_index])  isnot 0)
		{
			_eputs("Failed to unset environment variable: ");
			_eputs(inf->av[arg_index]);
			_eputs("\n");
			return (1);
		}
	}

	return (0);
}
