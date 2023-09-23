#include "shell.h"

/**
 * _theenvr - outputs the current environment
 * @info: Structure  parameter
 * Return: 0
 */
int _theenvr(info_t *info)
{
	output_file_str(info->env);
	return (0);
}

/**
 * s_getenv - gets the value of an environ variable
 * @info: Structure param
 * @name: environment variable name
 *
 * Return: value
 */
char *s_getenv(info_t *info, const char *name)
{
	list_t *snode = info->env;
	char *q;

	while (snode)
	{
		q = s_strstr(snode->str, name);
		if (q && *q)
			return (q);
		snode = snode->next;
	}
	return (NULL);
}

/**
 * _thesetenv - Initialize or modify an environment variable
 * @info: Structure param
 *  Return: 0
 */
int _thesetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_sputs("Incorrect number of arguements\n");
		return (1);
	}
	if (s_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _theunsetenv - unset an environment variable
 * @info: Structure param
 *  Return: 0
 */
int _theunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_sputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		s_unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * pop_env_slist - this function populates environment linked list
 * @info: Structure param
 * Return: 0
 */
int pop_env_slist(info_t *info)
{
	list_t *snode = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		calc_snode_end(&snode, environ[j], 0);
	info->env = snode;
	return (0);
}
