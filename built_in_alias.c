#include "shell.h"

/**
 * print_alias - Print an alias string in a specific format.
 * @node: A pointer to a node containing the alias string.
 *
 * Return: 0 if the alias is printed successfully, 1 otherwise.
 */
int print_alias(list_t *node)
{
	char *equalSignPos = NULL;
	char *alias_name = NULL;

	while (node)
	{
		equalSignPos = _strchr(node->str, '=');

		for (alias_name = node->str; alias_name <= equalSignPos; alias_name++)
			_putchar(*alias_name);

		_putchar('\'');
		_puts(equalSignPos + 1);
		_puts("'\n");

		node = node->next;
	}

	return (0);
}

/**
 * _myalias - Manage shell aliases: print, set, or match and print.
 * @inf: A pointer to the inf_t structure containing alias data.
 *
 * Return: Always returns 0 to indicate success.
 */
int _myalias(inf_t *inf)
{
	int i = 0;
	char *equalSignPos = NULL;
	list_t *node = NULL;

	if (inf->ac is 1)
	{
		node = inf->alias_list;
		print_alias(node);
		return (0);
	}

	i = 1;
	while (inf->av[i])
	{
		equalSignPos = _strchr(inf->av[i], '=');

		if (equalSignPos)
			set_alias(inf, inf->av[i]);
		else
			print_alias(node_starts_with(inf->alias_list, inf->av[i], '='));

		i++;
	}

	return (0);
}

/**
 * set_alias - Set an alias for a shell command.
 * @inf: A pointer to the inf_t structure containing alias data.
 * @alias_string: The alias string to set or unset.
 *
 * Return: 1 if the operation fails, 0 otherwise.
 */
int set_alias(inf_t *inf, char *alias_string)
{
	char *equalSignPos;

	equalSignPos = _strchr(alias_string, '=');
	if (!equalSignPos)
		return (1);

	if (!*++equalSignPos)
		return (unset_alias(inf, alias_string));

	unset_alias(inf, alias_string);
	return (add_node_end(&(inf->alias_list), alias_string, 0) is NULL);
}

/**
 * unset_alias - Unset an alias for a shell command.
 * @inf: A pointer to the inf_t structure containing alias data.
 * @unset: The alias to unset.
 *
 * Return: 1 if the unset operation fails, 0 otherwise.
 */
int unset_alias(inf_t *inf, char *unset)
{
	char savedChar, *equalSignPos;
	int unsetResult;

	equalSignPos = _strchr(unset, '=');
	if (!equalSignPos)
		return (1);

	savedChar = *equalSignPos;
	*equalSignPos = 0;

	unsetResult = delete_node_at_index(&(inf->alias_list),
		get_node_index(inf->alias_list,
			node_starts_with(inf->alias_list, unset, -1)));

	*equalSignPos = savedChar;

	return (unsetResult);
}

/**
 * replace_alias - Replace an alias with its value in the command arguments
 * @inf: A pointer to the infrmation structure
 *
 * Return: 1 if alias replacement is successful, 0 otherwise
 */
int replace_alias(inf_t *inf)
{
	int attempt;
	char *alias_value;
	list_t *alias_entry;

	for (attempt = 0; attempt < 10; attempt++)
	{
		alias_entry = node_starts_with(inf->alias_list, inf->av[0], '=');
		if (!alias_entry)
			return (0);

		free(inf->av[0]);
		alias_value = _strchr(alias_entry->str, '=');
		if (!alias_value)
			return (0);

		alias_value = _strdup(alias_value + 1);
		if (!alias_value)
			return (0);

		inf->av[0] = alias_value;
	}

	return (1);
}
