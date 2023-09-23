#include "shell.h"

/**
 * acq_environ - this funtion returns the environment string array
 * @info: Structure param
 * Return:  0
 */
char **acq_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = slst_t_strng(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * s_unsetenv - this function removes env variable
 * @info: Structure parameter
 * @var: string
 *
 *  Return: 1 if it deletes, 0 if not
 */
int s_unsetenv(info_t *info, char *var)
{
	list_t *snode = info->env;
	size_t j = 0;
	char *q;

	if (!snode || !var)
		return (0);

	while (snode)
	{
		q = s_strstr(snode->str, var);
		if (q && *q == '=')
		{
			info->env_changed = erase_snode_t_indx(&(info->env), j);
			j = 0;
			snode = info->env;
			continue;
		}
		snode = snode->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * s_setenv - this function initializes an enc variable
 * @info: Structure parameters
 * @var: the string
 * @value: the environment variable value
 * Return:  0
 */
int s_setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *snode;
	char *q;

	if (!var || !value)
		return (0);

	buf = malloc(s_strlen(var) + s_strlen(value) + 2);
	if (!buf)
		return (1);
	s_strcpy(buf, var);
	s_strcat(buf, "=");
	s_strcat(buf, value);
	snode = info->env;
	while (snode)
	{
		q = s_strstr(snode->str, var);
		if (q && *q == '=')
		{
			free(snode->str);
			snode->str = buf;
			info->env_changed = 1;
			return (0);
		}
		snode = snode->next;
	}
	calc_snode_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
