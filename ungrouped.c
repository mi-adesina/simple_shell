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


