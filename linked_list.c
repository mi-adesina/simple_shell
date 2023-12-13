#include "shell.h"

/**
 * add_node - Add a new node at the beginning of a linked list
 * @head: A pointer to a pointer to the head of the linked list
 * @str: The string to be stored in the new node
 * @number: An integer to be stored in the new node
 *
 * Return: A pointer to the new node if successful, or NULL on failure
 */
list_t *add_node(list_t **head, const char *str, int number)
{
	list_t *new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->number = number;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *head;
	*head = new;
	return (new);
}

/**
 * add_node_end - Add a new node at the end of a linked list
 * @head: A pointer to a pointer to the head of the linked list
 * @str: The string to be stored in the new node
 * @number: An integer to be stored in the new node
 *
 * Return: A pointer to the new node if successful, or NULL on failure
 */
list_t *add_node_end(list_t **head, const char *str, int number)
{
	list_t *new, *current_node;

	if (!head)
		return (NULL);
	current_node = *head;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->number = number;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new;
	}
	else
		*head = new;

	return (new);
}

/**
 * delete_node_at_index - Delete a node at a specific index in a linked list.
 * @head: A pointer to a pointer to the head of the linked list.
 * @index: The index of the node to be deleted.
 *
 * Return: 1 if successful, 0 if the node was not found or an error occurred.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head or !*head)
		return 0;

	if (!index)
	{
		list_t *node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return 1;
	}

	return delete_node_at_index(&((*head)->next), index - 1);
}

/**
 * free_list - Free the memory of a linked list.
 * @head_ptr: A pointer to a pointer to the head of the linked list.
 */
void free_list(list_t **head_ptr)
{
	list_t *node;

	if (!head_ptr or !*head_ptr)
		return;

	node = *head_ptr;
	*head_ptr = node->next;

	free(node->str);
	free(node);

	free_list(head_ptr);
}

/**
 * list_len- Count the number of nodes in a linked list recursively.
 * @head: A pointer to the head of the linked list.
 *
 * Return: The number of nodes in the linked list.
 */
size_t list_len(const list_t *head)
{
	if (!head)
	{
		return (0);
	}
	else
	{
		return (1 + list_len(head->next));
	}
}



