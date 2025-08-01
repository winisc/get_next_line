/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:51:15 by wsilveir          #+#    #+#             */
/*   Updated: 2025/07/31 21:16:43 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static size_t	get_new_line(char *tmp_buffer)
{
	int	i;

	i = 0;
	while(tmp_buffer[i])
	{
		if(tmp_buffer[i] == '\n')
			return (i); 
		i++;
	}
	return (-1);
}

static char	*read_buffer_nl(int fd, char *tmp_buffer)
{
	char 	*rd_buffer;
	char	*tmp_storage;
	size_t 	nl_pos;
	int		rd_bytes;

	rd_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!rd_buffer)
		return (NULL);
	nl_pos = get_new_line(tmp_buffer);
	while (nl_pos == -1)
	{
		rd_bytes = read(fd, rd_buffer, BUFFER_SIZE);
		if (rd_bytes == 0)
			return (tmp_buffer);
		if (rd_bytes < 0)
		{
			free(rd_buffer);
			free(tmp_buffer);
			return (NULL);
		}
		rd_buffer[rd_bytes] = 0;
		tmp_storage = ft_strjoin(tmp_buffer, rd_buffer);
		free(tmp_buffer);
		tmp_buffer = tmp_storage;
		nl_pos = get_new_line(tmp_buffer);
	}
	return (tmp_buffer);
}

static char	*get_line(char *tmp_buffer, size_t nl_index)
{
	char	*nl_buffer;

	if (nl_index != -1)
	{
		nl_buffer = (char *)malloc ((nl_index + 2) * sizeof(char));
		ft_strlcpy(nl_buffer, tmp_buffer, nl_index + 2);
		return (nl_buffer);
	}
	return (NULL);

}

static char	*save_remainder_buffer(char *tmp_buffer, size_t nl_index)
{
	char *str_remainder;
	if (nl_index != -1)
	{
		str_remainder = (char *)malloc((ft_strlen(tmp_buffer) - nl_index + 1) * sizeof(char));
		ft_strlcpy(str_remainder, tmp_buffer + nl_index + 1, ft_strlen(tmp_buffer) - nl_index + 1);
		return (str_remainder);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char *tmp_buffer;
	size_t		nl_pos;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (tmp_buffer == NULL)
		tmp_buffer = ft_strdup("");
	tmp_buffer = read_buffer_nl(fd, tmp_buffer);
	if (!tmp_buffer || !tmp_buffer[0])
	{
		free(tmp_buffer);
		return (NULL);
	}
	nl_pos = get_new_line(tmp_buffer);
	line = get_line(tmp_buffer, nl_pos);
	tmp_buffer = save_remainder_buffer(tmp_buffer, nl_pos);
	return (line);
}
