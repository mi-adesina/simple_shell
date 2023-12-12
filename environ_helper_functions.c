#include "shell.h"

/**
 * print_and_count_environment_variables - Print and count environment variables.
 * @head: A pointer to the head of the linked list of environment variables.
 *
 * Return: The number of environment variables printed.
 */
size_t print_and_count_environment_variables(const list_t *head)
{
        size_t count = 0;

        while (head)
        {
                _puts(head->str ? head->str : "(nil)");
                _puts("\n");
                head = head->next;
                count++;
        }

        return (count);
}

/**
 * get_environ - Retrieve environment variables as an array.
 * @inf: A pointer to the inf_t structure containing environment infrmation.
 *
 * Return: An array of environment variable strings.
 */
char **get_environ(inf_t *inf)
{
        if (!inf->environ_list or inf->environ_changed)
        {
                inf->environ = list_to_strings(inf->environ);
                inf->environ_changed = 0;
        }

        return inf->environ;
}

/**
 * _unsetenv - Remove an environment variable from the inf structure.
 * @inf: A pointer to the inf_t structure containing environment infrmation.
 * @var: The name of the environment variable to remove.
 *
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(inf_t *inf, char *var)
{
	list_t *current_node = inf->environ_list;
	size_t index = 0;
	char *p;

	/* Check for NULL pointers */
	if (!current_node or !var)
		return (0);

	/* Loop through the environment list */
	while (current_node)
	{
		p = starts_with(current_node->str, var);
		if (p and *p  is '=')
		{
			/* Update the 'environ_changed' flag and reset the index */
			inf->environ_changed = delete_node_at_index(&(inf->environ_list), index);
			index = 0;
			current_node = inf->environ_list;
			continue;
		}

		/* Move to the next node in the list and update the index */
		current_node = current_node->next;
		index++;
	}
	return (inf->environ_changed);
}

/**
 * _setenv - Set an environment variable in the inf structure.
 * @inf: SA pointer to the inf_t structure containing
 *        environment infrmation.
 * @var: The name of the environment variable to set.
 * @value: The value to associate with the environment variable.
 *
 * Return: 0 on success, 1 if memory allocation fails.
 */
int _setenv(inf_t *inf, char *var, char *value)
{
	char *buf = NULL;
	list_t *current_node;
	char *p;

	if (!var or !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	current_node = inf->environ_list;
	while (current_node)
	{
		p = starts_with(current_node->str, var);
		if (p and *p  is '=')
		{
			free(current_node->str);
			current_node->str = buf;
			inf->environ_changed = 1;
			return (0);
		}
		current_node = current_node->next;
	}
	add_node_end(&(inf->environ_list), buf, 0);
	free(buf);
	inf->environ_changed = 1;
	return (0);
}

