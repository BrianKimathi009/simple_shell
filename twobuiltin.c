#include "shell.h"

/**
 * _thehist - this function displays the history list
 * @info: parameter structure
 *  Return: 0
 */
int _thehist(info_t *info)
{
	output_slst(info->history);
	return (0);
}

/**
 * disable_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int disable_alias(info_t *info, char *str)
{
	char *q, d;
	int pat;

	q = s_strchr(str, '=');
	if (!q)
		return (1);
	d = *q;
	*q = 0;
	pat = erase_snode_t_indx(&(info->alias),
		acq_snode_indx(info->alias, snode_begn_wth(info->alias, str, -1)));
	*q = d;
	return (pat);
}

/**
 * enable_alias - this function enables alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int enable_alias(info_t *info, char *str)
{
	char *q;

	q = s_strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (disable_alias(info, str));

	disable_alias(info, str);
	return (calc_snode_end(&(info->alias), str, 0) == NULL);
}

/**
 * output_alias - outputs an alias string
 * @node: the alias node
 *
 * Return: 0 on success and 1 on error
 */
int output_alias(list_t *node)
{
	char *q = NULL, *b = NULL;

	if (node)
	{
		q = s_strchr(node->str, '=');
		for (b = node->str; b <= q; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _thealias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _thealias(info_t *info)
{
	int j = 0;
	char *q = NULL;
	list_t *snode = NULL;

	if (info->argc == 1)
	{
		snode = info->alias;
		while (snode)
		{
			output_alias(snode);
			snode = snode->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		q = s_strchr(info->argv[j], '=');
		if (q)
			enable_alias(info, info->argv[j]);
		else
			output_alias(snode_begn_wth(info->alias, info->argv[j], '='));
	}

	return (0);
}
