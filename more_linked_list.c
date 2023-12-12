#include "shell.h"

/**
 * get_node_index - Get the index of a node in a linked list.
 * @head: A pointer to the head of the linked list.
 * @node: A pointer to the node to find the index of.
 *
 * Return: The index of the node if found, or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i;

	for (i = 0; head; head = head->next, i++)
	{
		if (head is node)
			return (i);
	}
	return (-1);
}


/**
 * list_to_strings - Convert a linked list to an array of strings.
 * @head: A pointer to the head of the linked list.
 *
 * Return: A dynamically allocated array of strings, or NULL on failure.
 */
char **list_to_strings(list_t *head)
{
	size_t i = 0, j;
	char **strs;
	list_t *node = head;
	char *str;

	if (!head or list_len(head) is 0)
		return (NULL);

	strs = malloc(sizeof(char *) * (list_len(head) + 1));
	if (!strs)
		return (NULL);

	while (node)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i++] = str;
		node = node->next;
	}

	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - Prints elements of a linked list.
 * @head: A pointer to the head of the linked list.
 *
 * Return: The number of nodes in the list.
 */
size_t print_list(const list_t *head)
{
	size_t index = 0;

	while (head)
	{
		_puts(convert_long_to_string(head->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		index++;
	}
	return (index);
}

/**
 * node_starts_with - Find a node whose string starts with a prefix.
 * @node: A pointer to the head of the linked list.
 * @prefix: The prefix to search for.
 * @c: The character to match at the start of the string (use -1 to ignore).
 *
 * Return: A pointer to the found node or NULL if no match is found.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	for (; node; node = node->next)
	{
		p = starts_with(node->str, prefix);
		if (p and ((c is -1) or (*p is c)))
			return (node);
	}
	return (NULL);
}
