#include "shell.h"

/**
 * clear_inf - reset a selected few fields within inf structure.
 * @inf: a pointer to the inf_t structure to reset.
 */
void clear_inf(inf_t *inf)
{
	inf->ac = 0;
	inf->av = NULL;
	inf->arg = NULL;
	inf->path = NULL;
}

/**
 * set_inf - Set infrmation in the inf_t structure based on command-line arguments.
 * @inf: Pointer to the inf_t structure.
 * @av: Array of strings representing command-line arguments.
 */
void set_inf(inf_t *inf, char **av)
{
    int i = 0;

    inf->file_name = av[0];

    if (inf->arg)
    {
	inf->av = strtow(inf->arg, " \t");

	if (!inf->av)
	{
	    inf->av = malloc(sizeof(char *) * 2);

	    if (inf->av)
	    {
		inf->av[0] = _strdup(inf->arg);
		inf->av[1] = NULL;
	    }
	}

	i = 0;
	while (inf->av and inf->av[i])
	    i++;

	inf->ac = i;

	replace_alias(inf);
	replace_vars(inf);
    }
}

/**
 * free_inf - Free memory allocated for elements in the inf_t structure.
 * @inf: Pointer to the inf_t structure.
 * @all: Flag to indicate whether to free all elements.
 */
void free_inf(inf_t *inf, int all)
{
    ffree(inf->av);

    inf->av = NULL;
    inf->path = NULL;

    if (all)
    {

	if (!inf->command_buffer)
	    free(inf->arg);

	/* if (inf->alias)
	    free_list(&(inf->alias));
	if (inf->env)
		free_list(&(inf->env));

	if (inf->history)
	    free_list(&(inf->history)); */

	ffree(inf->environ);
	inf->environ = NULL;

	bfree((void **)inf->command_buffer);

	if (inf->read_fd > 2)
	    close(inf->read_fd);

	_putchar(BUFFER_FLUSH);
    }
}
