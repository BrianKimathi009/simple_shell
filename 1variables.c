#include "shell.h"

/**
 * s_grp - test if current char in buffer is a chain delimeter
 * @info: structure parameter
 * @buf: pointer to buf
 * @p: pointer p
 *
 * Return: 1 on success, 0 on failure
 */
int s_grp(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}

/**
 * chck_grp - checks if we should continue chaining
 * @info: structure parameter
 * @buf: pointer to char buffer
 * @p: pointer to the current position
 * @i: the starting position
 * @len: buf length
 *
 * Return: nothng
 */
void chck_grp(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*p = k;
}

/**
 * restore_aka - this function replaces aliases
 * @info: structure parameter
 *
 * Return: 1 on success, -1 on failure
 */
int restore_aka(info_t *info)
{
	int j;
	list_t *snode;
	char *q;

	for (j = 0; j < 10; j++)
	{
		snode = snode_begn_wth(info->alias, info->argv[0], '=');
		if (!snode)
			return (0);
		free(info->argv[0]);
		q = s_strchr(snode->str, '=');
		if (!q)
			return (0);
		q = s_strdup(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * restore_vrs - this function replaces variables in  str
 * @info: structure parameter
 *
 * Return: 1 on success, -1 on error
 */
int restore_vrs(info_t *info)
{
	int j = 0;
	list_t *snode;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!s_strcmp(info->argv[j], "$?"))
		{
			restore_strng(&(info->argv[j]),
				s_strdup(change_num(info->status, 10, 0)));
			continue;
		}
		if (!s_strcmp(info->argv[j], "$$"))
		{
			restore_strng(&(info->argv[j]),
				s_strdup(change_num(getpid(), 10, 0)));
			continue;
		}
		snode = snode_begn_wth(info->env, &info->argv[j][1], '=');
		if (snode)
		{
			restore_strng(&(info->argv[j]),
				s_strdup(s_strchr(snode->str, '=') + 1));
			continue;
		}
		restore_strng(&info->argv[j], s_strdup(""));

	}
	return (0);
}

/**
 * restore_strng - this function replaces a string
 * @old: pointer to old's pointer
 * @new: pointer to a new string
 *\
 * Return: 1 on success,0 on failure
 */
int restore_strng(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
