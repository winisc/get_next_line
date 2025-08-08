/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:52:08 by wsilveir          #+#    #+#             */
/*   Updated: 2025/08/08 10:27:25 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_error(char *buf, char *tmp_buf)
{
	free(buf);
	free(tmp_buf);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;

	str = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	i = 0;
	if (!str)
		return (NULL);
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	size_src;

	i = 0;
	size_src = ft_strlen(src);
	if (!size)
		return (size_src);
	i = 0;
	while (i < (size - 1) && src[i])
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = 0;
	return (size_src);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_1;
	size_t	len_2;
	size_t	max_len;
	char	*str;

	if (!s1 && !s2)
		return (ft_strdup(""));
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	max_len = len_1 + len_2;
	str = (char *)malloc((max_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len_1 + 1);
	ft_strlcpy(str + len_1, s2, max_len - len_1 + 1);
	return (str);
}
