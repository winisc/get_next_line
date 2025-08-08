/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:51:15 by wsilveir          #+#    #+#             */
/*   Updated: 2025/08/08 10:27:13 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	get_new_line(char *tmp_buffer)
{
	int	i;

	i = 0;
	while (tmp_buffer[i])
	{
		if (tmp_buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*read_buffer_nl(int fd, char *tmp_buffer)
{
	char	*rd_buffer;
	char	*tmp_storage;
	int		nl_pos;
	int		rd_bytes;

	rd_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!rd_buffer)
		return (NULL);
	nl_pos = get_new_line(tmp_buffer);
	while (nl_pos == -1)
	{
		rd_bytes = read(fd, rd_buffer, BUFFER_SIZE);
		if (rd_bytes == 0)
			break ;
		if (rd_bytes == -1)
			return (ft_read_error(rd_buffer, tmp_buffer));
		rd_buffer[rd_bytes] = 0;
		tmp_storage = ft_strjoin(tmp_buffer, rd_buffer);
		free(tmp_buffer);
		tmp_buffer = tmp_storage;
		nl_pos = get_new_line(tmp_buffer);
	}
	free(rd_buffer);
	return (tmp_buffer);
}

char	*get_line(char *tmp_buffer, int nl_index)
{
	char	*nl_buffer;

	if (nl_index < 0)
		return (ft_strdup(tmp_buffer));
	nl_buffer = (char *)malloc((nl_index + 2) * sizeof(char));
	if (!nl_buffer)
		return (NULL);
	ft_strlcpy(nl_buffer, tmp_buffer, nl_index + 2);
	return (nl_buffer);
}

char	*save_remainder_buffer(char *tmp_buffer, int nl_index)
{
	char	*str_remainder;
	int		len;

	len = ft_strlen(tmp_buffer);
	if (nl_index < 0 || nl_index == len - 1)
	{
		free(tmp_buffer);
		return (NULL);
	}
	str_remainder = ft_strdup(tmp_buffer + nl_index + 1);
	free(tmp_buffer);
	return (str_remainder);
}

char	*get_next_line(int fd)
{
	static char	*tmp_buffer[4096];
	int			nl_pos;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!tmp_buffer[fd])
		tmp_buffer[fd] = ft_strdup("");
	tmp_buffer[fd] = read_buffer_nl(fd, tmp_buffer[fd]);
	if (!tmp_buffer[fd] || !tmp_buffer[fd][0])
	{
		free(tmp_buffer[fd]);
		tmp_buffer[fd] = NULL;
		return (NULL);
	}
	nl_pos = get_new_line(tmp_buffer[fd]);
	line = get_line(tmp_buffer[fd], nl_pos);
	tmp_buffer[fd] = save_remainder_buffer(tmp_buffer[fd], nl_pos);
	return (line);
}
