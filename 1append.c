#include "shell.h"

/**
 * s_command - this function decides if a file is executable
 * @info: structure parameter
 * @path: pointr to path
 *
 * Return: 1 if true, 0 if false
 */
int s_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dplc_schar - this function duplicates chars
 * @pathstr: pointer to path string
 * @start: beggining index
 * @stop: ending index
 *
 * Return: new buffer's pointer
 */
char *dplc_schar(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int j = 0, l = 0;

	for (l = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[l++] = pathstr[j];
	buf[l] = 0;
	return (buf);
}

/**
 * loct_spth - looks for command in path string
 * @info: structure parameter
 * @pathstr: path string
 * @cmd: command to look for
 *
 * Return: commands path
 */
char *loct_spth(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, rec_psn = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((s_strlen(cmd) > 2) && s_strstr(cmd, "./"))
	{
		if (s_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dplc_schar(pathstr, rec_psn, j);
			if (!*path)
				s_strcat(path, cmd);
			else
			{
				s_strcat(path, "/");
				s_strcat(path, cmd);
			}
			if (s_command(info, path))
				return (path);
			if (!pathstr[j])
				break;
			rec_psn = j;
		}
		j++;
	}
	return (NULL);
}
