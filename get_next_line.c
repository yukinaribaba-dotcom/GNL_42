/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybaba <ybaba@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:27:22 by ybaba             #+#    #+#             */
/*   Updated: 2026/01/14 12:59:15 by ybaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_until_newline(int fd, char *backup)
{
	char	*buf;
	ssize_t	bytes_read;
	char	*temp;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(backup, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			free(backup);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		temp = ft_strjoin(backup, buf);
		free(backup);
		backup = temp;
	}
	free(buf);
	return (backup);
}

static char	*extract_line(char **backup)
{
	char	*line;
	char	*newline_pos;
	char	*temp;

	newline_pos = ft_strchr(*backup, '\n');
	if (newline_pos)
	{
		line = ft_substr(*backup, 0, newline_pos - *backup + 1);
		temp = ft_substr(*backup, newline_pos - *backup + 1,
				ft_strlen(newline_pos + 1));
		free(*backup);
		*backup = temp;
	}
	else
	{
		line = ft_substr(*backup, 0, ft_strlen(*backup));
		free(*backup);
		*backup = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = read_until_newline(fd, backup);
	if (!backup || backup[0] == '\0')
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	return (extract_line(&backup));
}
