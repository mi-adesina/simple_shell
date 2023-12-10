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
	list_t *new_head;

	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->number = number;

	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *head;
	*head = new_head;
	return (new_head);
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
	if (!head)
		return NULL;

	list_t *new_node = malloc(sizeof(list_t));
	if (!new_node)
		return NULL;

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->number = number;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return NULL;
		}
	}

	if (*head)
		(*head)->next = add_node_end(&((*head)->next), str, number);
	else
		*head = new_node;

	return new_node;
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
	if (!head_ptr or !*head_ptr)
		return;

	list_t *node = *head_ptr;
	*head_ptr = node->next;

	free(node->str);
	free(node);

	free_list(head_ptr);
}
