#include "shell.h"

/**
 * acq_hist_sfile - retrieves the history file
 * @info: Structure parameter
 *
 * Return: string with history file
 */

char *acq_hist_sfile(info_t *info)
{
	char *buf, *drct;

	drct = s_getenv(info, "HOME=");
	if (!drct)
		return (NULL);
	buf = malloc(sizeof(char) * (s_strlen(drct) + s_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	s_strcpy(buf, drct);
	s_strcat(buf, "/");
	s_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * inpt_hist - this function creates or appends file s
 * @info: structure parameter
 *
 * Return: 1 on success and -1 on error
 */
int inpt_hist(info_t *info)
{
	ssize_t fildes;
	char *fldr_tag = acq_hist_sfile(info);
	list_t *snode = NULL;

	if (!fldr_tag)
		return (-1);

	fildes = open(fldr_tag, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fldr_tag);
	if (fildes == -1)
		return (-1);
	for (snode = info->history; snode; snode = snode->next)
	{
		_putsfides(snode->str, fildes);
		_putfildes('\n', fildes);
	}
	_putfildes(BUF_FLUSH, fildes);
	close(fildes);
	return (1);
}

/**
 * rd_hist - this function reads history from a file
 * @info: struct prameter
 *
 * Return: on success history count, 0 on error
 */
int rd_hist(info_t *info)
{
	int j, finl = 0, num_line = 0;
	ssize_t fildes, srdlen, f_size = 0;
	struct stat st;
	char *buf = NULL, *fldr_tag = acq_hist_sfile(info);

	if (!fldr_tag)
		return (0);

	fildes = open(fldr_tag, O_RDONLY);
	free(fldr_tag);
	if (fildes == -1)
		return (0);
	if (!fstat(fildes, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (f_size + 1));
	if (!buf)
		return (0);
	srdlen = read(fildes, buf, f_size);
	buf[f_size] = 0;
	if (srdlen <= 0)
		return (free(buf), 0);
	close(fildes);
	for (j = 0; j < f_size; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			creat_hist_slist(info, buf + finl, num_line++);
			finl = j + 1;
		}
	if (finl != j)
		creat_hist_slist(info, buf + finl, num_line++);
	free(buf);
	info->histcount = num_line;
	while (info->histcount-- >= HIST_MAX)
		erase_snode_t_indx(&(info->history), 0);
	rnum_hist(info);
	return (info->histcount);
}

/**
 * creat_hist_slist - this function adds history on linked list
 * @info: Structure parameter
 * @buf: pointer to buffer
 * @linecount: linecount's history, histcount
 *
 * Return: 0
 */
int creat_hist_slist(info_t *info, char *buf, int linecount)
{
	list_t *snode = NULL;

	if (info->history)
		snode = info->history;
	calc_snode_end(&snode, buf, linecount);

	if (!info->history)
		info->history = snode;
	return (0);
}

/**
 * rnum_hist - this function renums the linked list containing history
 * @info: Structure parameter
 *
 * Return: histcount
 */
int rnum_hist(info_t *info)
{
	list_t *snode = info->history;
	int j = 0;

	while (snode)
	{
		snode->num = j++;
		snode = snode->next;
	}
	return (info->histcount = j);
}
