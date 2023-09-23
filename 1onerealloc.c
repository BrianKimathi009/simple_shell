#include "shell.h"

/**
 **s_memset - this function fills memory with const byte
 *@s: memory area pointer
 *@b: byte to fill
 *@n: num of bytes to be filled
 *Return: s
 */
char *s_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * ffree - this function frees string
 * @pp: pointer to address of pp
 */
void gfree(char **pp)
{
	char **b = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(b);
}

/**
 * s_realloc - this function moves a block of memory
 * @ptr: previous block pointer
 * @old_size: previous block size
 * @new_size: new block's size
 *
 * Return: old block's pointer
 */
void *s_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *q;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	q = malloc(new_size);
	if (!q)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		q[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (q);
}
