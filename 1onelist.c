#include "shell.h"

/**
 * calc_snode - this functionadds a node at the beginning of the list
 * @head: head node's pointers address
 * @str: point to str
 * @num: indexx to node used by hist
 *
 * Return: list size
 */
list_t *calc_snode(list_t **head, const char *str, int num)
{
	list_t *other_head;

	if (!head)
		return (NULL);
	other_head = malloc(sizeof(list_t));
	if (!other_head)
		return (NULL);
	s_memset((void *)other_head, 0, sizeof(list_t));
	other_head->num = num;
	if (str)
	{
		other_head->str = s_strdup(str);
		if (!other_head->str)
		{
			free(other_head);
			return (NULL);
		}
	}
	other_head->next = *head;
	*head = other_head;
	return (other_head);
}

/**
 * calc_snode_end - this function adds a node to the list's end
 * @head: pointers address to head node
 * @str: pointer to string
 * @num: index node used by hist
 *
 * Return: list size
 */
list_t *calc_snode_end(list_t **head, const char *str, int num)
{
	list_t *other_snode, *snode;

	if (!head)
		return (NULL);

	snode = *head;
	other_snode = malloc(sizeof(list_t));
	if (!other_snode)
		return (NULL);
	s_memset((void *)other_snode, 0, sizeof(list_t));
	other_snode->num = num;
	if (str)
	{
		other_snode->str = s_strdup(str);
		if (!other_snode->str)
		{
			free(other_snode);
			return (NULL);
		}
	}
	if (snode)
	{
		while (snode->next)
			snode = snode->next;
		snode->next = other_snode;
	}
	else
		*head = other_snode;
	return (other_snode);
}

/**
 * output_file_str - this function prints the str element 
 * @h: 1st node's pointer
 *
 * Return: list size
 */
size_t output_file_str(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * erase_snode_t_indx - this functiom deletes node at specific index
 * @head: 1st node's address pointer
 * @index: node's index to be deleted
 *
 * Return: on success 1, 0 on error
 */
int erase_snode_t_indx(list_t **head, unsigned int index)
{
	list_t *snode, *former_snode;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		snode = *head;
		*head = (*head)->next;
		free(snode->str);
		free(snode);
		return (1);
	}
	snode = *head;
	while (snode)
	{
		if (j == index)
		{
			former_snode->next = snode->next;
			free(snode->str);
			free(snode);
			return (1);
		}
		j++;
		former_snode = snode;
		snode = snode->next;
	}
	return (0);
}

/**
 * rel_slist - this function frees list nodes
 * @head_ptr: head's node pointer's address
 *
 * Return: nothing
 */
void rel_slist(list_t **head_ptr)
{
	list_t *snode, *aftr_snode, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	snode = head;
	while (snode)
	{
		aftr_snode = snode->next;
		free(snode->str);
		free(snode);
		snode = aftr_snode;
	}
	*head_ptr = NULL;
}
