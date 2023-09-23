#include "shell.h"

/**
 * slst_lenth - this determines hte linked list's length
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t slst_lenth(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * slst_t_strn - this function returns an array of str
 * @head: 1st node's pointer
 *
 * Return: array of strings
 */
char **slst_t_strn(list_t *head)
{
	list_t *snode = head;
	size_t k = slst_lenth(head), l;
	char **string;
	char *str;

	if (!head || !k)
		return (NULL);
	string = malloc(sizeof(char *) * (k + 1));
	if (!string)
		return (NULL);
	for (k = 0; snode; snode = snode->next, k++)
	{
		str = malloc(s_strlen(snode->str) + 1);
		if (!str)
		{
			for (l = 0; l < k; l++)
				free(string[l]);
			free(string);
			return (NULL);
		}

		str = s_strcpy(str, snode->str);
		string[k] = str;
	}
	string[k] = NULL;
	return (string);
}


/**
 * output_slst - this function linked list elements
 * @h: 1st node's pointer
 *
 * Return: list size
 */
size_t output_slst(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(change_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * snode_begn_wth - returns node whose string starts with prefix
 * @node: 1st node pointer
 * @prefix: string to be matched
 * @c: next char to match
 *
 * Return: node's match or NULL
 */
list_t *snode_begn_wth(list_t *node, char *prefix, char c)
{
	char *q = NULL;

	while (node)
	{
		q = s_strstr(node->str, prefix);
		if (q && ((c == -1) || (*q == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * acq_snode_indx - acquires node's index
 * @head: head's pointer
 * @node: node's pointer
 *
 * Return: node's index
 */
ssize_t acq_snode_indx(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
