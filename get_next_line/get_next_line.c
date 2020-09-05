/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 14:08:34 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/05 17:37:37 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

int			ft_strlcpy_gnl(char *dst, const char *src, int dstsize)
{
	int srclen;
	int dstlen;

	if (src == 0)
		return (0);
	srclen = ft_strlen_gnl(src);
	if (dstsize == 0)
		return (srclen);
	dstlen = dstsize - 1;
	if (srclen < dstsize)
		dstlen = srclen;
	ft_memcpy_gnl(dst, src, dstlen);
	dst[dstlen] = '\0';
	return (srclen);
}

int			g_n_l_read(char **str, char **buffer, int fd, int *i)
{
	int ret;
	int len;

	ret = 1;
	len = ft_strlen_gnl(*str);
	*buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*buffer == 0 && ft_free(str, buffer, 0) == 0)
		return (-1);
	while (ret > 0)
	{
		if ((((*i) % BUFFER_SIZE == 0) && *i > len) || *i == len)
		{
			ret = read(fd, *buffer, BUFFER_SIZE);
			if (ret == -1 && ft_free(str, buffer, 0) == 0)
				return (-1);
			(*buffer)[ret] = '\0';
			(*str) = ft_strjoin_gnl((*str), *buffer);
			if ((*str) == 0 && ft_free(str, buffer, 0) == 0)
				return (-1);
		}
		if ((*str)[*i] == '\n' || (*str)[*i] == '\0')
			return (ret);
		(*i)++;
	}
	return (ret);
}

void		g_n_l_eol(int ret, char **str, int *i, char **buffer)
{
	while (ret == 0)
	{
		if ((*str)[*i] == '\n' || (*str)[*i] == '\0')
			break ;
		(*i)++;
	}
	if (*buffer)
		free(*buffer);
}

int			empty_s(char **str)
{
	if (*str == 0)
	{
		*str = (char *)malloc(1);
		if (*str == 0)
			return (0);
		*str[0] = '\0';
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	char			*buffer;
	static char		*str;
	int				ret;
	int				i;
	int				m;

	i = 0;
	m = 0;
	if (fd < 0 || line == 0 || read(fd, 0, 0) == -1 || empty_s(&str) == 0)
		return (-1);
	ret = g_n_l_read(&str, &buffer, fd, &i);
	if (ret == -1)
		return (-1);
	g_n_l_eol(ret, &str, &i, &buffer);
	*line = malloc(sizeof(char) * i + 1);
	if (*line == 0 && ft_free(&str, &buffer, 1) == 0)
		return (-1);
	ft_strlcpy_gnl(*line, str, i + 1);
	if (str[i] == '\n')
		m = 1;
	ft_strlcpy_gnl(&str[0], &str[i + 1], (ft_strlen_gnl(str)));
	if (m == 1)
		return (1);
	return (ft_free(&str, &buffer, 1));
}
