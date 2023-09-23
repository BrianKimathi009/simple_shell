#include "shell.h"

/**
 * **s_strtok - this function tokenizes a string
 * @str: input string
 * @d: delim string
 * Return: a pointer to tring array
 */

char **s_strtok(char *str, char *d)
{
	int w, x, y, z, wrdsnum = 0;
	char **t;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (w = 0; str[w] != '\0'; w++)
		if (!s_delimtr(str[w], d) && (s_delimtr(str[w + 1], d) || !str[w + 1]))
			wrdsnum++;

	if (wrdsnum == 0)
		return (NULL);
	t = malloc((1 + wrdsnum) * sizeof(char *));
	if (!t)
		return (NULL);
	for (w = 0, x = 0; x < wrdsnum; x++)
	{
		while (s_delimtr(str[w], d))
			w++;
		y = 0;
		while (!s_delimtr(str[w + y], d) && str[w + y])
			y++;
		t[x] = malloc((y + 1) * sizeof(char));
		if (!t[x])
		{
			for (y = 0; y < x; y++)
				free(t[y]);
			free(t);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			t[x][z] = str[w++];
		t[x][z] = 0;
	}
	t[x] = NULL;
	return (t);
}

/**
 * **s_strtokr - this function splits strings
 * @str: string to input
 * @d: the delim
 * Return: array of strings pointer
 */
char **s_strtokr(char *str, char d)
{
	int w, x, y, z, wrdsnum = 0;
	char **t;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (w = 0; str[w] != '\0'; w++)
		if ((str[w] != d && str[w + 1] == d) ||
		    (str[w] != d && !str[w + 1]) || str[w + 1] == d)
			wrdsnum++;
	if (wrdsnum == 0)
		return (NULL);
	t = malloc((1 + wrdsnum) * sizeof(char *));
	if (!t)
		return (NULL);
	for (w = 0, x = 0; x < wrdsnum; x++)
	{
		while (str[w] == d && str[w] != d)
			w++;
		y = 0;
		while (str[w + y] != d && str[w + y] && str[w + y] != d)
			y++;
		t[x] = malloc((y + 1) * sizeof(char));
		if (!t[x])
		{
			for (y = 0; y < x; y++)
				free(t[y]);
			free(t);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			t[x][z] = str[w++];
		t[x][z] = 0;
	}
	t[x] = NULL;
	return (t);
}
