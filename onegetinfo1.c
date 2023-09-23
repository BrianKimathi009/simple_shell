#include "shell.h"

/**
 * del_data - this function initializes info_t
 * @info: an address of type struct
 */
void del_data(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * enable_data - this function initializes info_t
 * @info: address of type struct
 * @av: arg vector
 */
void enable_data(info_t *info, char **av)
{
	int j = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = s_strtok(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = s_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}

		for (j = 0; info->argv && info->argv[j]; j++)
			;
		info->argc = j;

		restore_aka(info);
		restore_vrs(info);
	}
}

/**
 * rel_data - frees info_t struct fields
 * @info: theaddress
 * @all: freeing all
 */
void rel_data(info_t *info, int all)
{
	gfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			rel_slist(&(info->env));
		if (info->history)
			rel_slist(&(info->history));
		if (info->alias)
			rel_slist(&(info->alias));
		gfree(info->environ);
			info->environ = NULL;
		sfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
