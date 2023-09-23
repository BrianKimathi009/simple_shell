#include "shell.h"

/**
 * sfree - this function frees a function
 * @ptr: apointer's address to be freed
 *
 * Return: if freed 1, -1 if not
 */
int sfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
