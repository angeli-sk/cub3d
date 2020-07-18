/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_c3d.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 13:29:41 by akramp        #+#    #+#                 */
/*   Updated: 2020/07/18 20:20:49 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

static char	**ft_free_split(char **split, int x)
{
	while (x >= 0)
	{
		free(split[x]);
		x--;
	}
	free(split);
	return (0);
}

static char	**ft_write_string(char *s, t_splitty *spty, char **split, int max_y)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	while (s[i] != '\0' && y < max_y)
	{
		while (s[i] == (spty->c) && s[i] != '\0')
			i++;
		while (s[i] != (spty->c) && s[i] != '\0')
		{
			split[y][x] = s[i];
			x++;
			i++;
		}
		split[y][(spty->maxlen)] = '\0';
		y++;
		x = 0;
	}
	return (split);
}

static char	**ft_c_count(char *s, char **split, t_splitty *spty, t_cub3d *cub)
{
	int count;
	int x;

	count = 0;
	x = 0;
	while (*s != '\0')
	{
		while (*s == (spty->c) && *s != '\0')
			s++;
		while (*s != (spty->c) && *s != '\0')
		{
			count++;
			s++;
		}
		if (x < (spty->y))
		{
			split[x] = ft_calloc_mlx((cub->maxstrlen + 1), (sizeof(char)));
			if (split[x] == 0)
				return (ft_free_split(split, x));
			x++;
		}
		count = 0;
	}
	return (split);
}

static int	ft_string_count(char *s, char c, int y)
{
	int i;
	int m;

	i = 0;
	m = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && m == 0)
		{
			y++;
			m = 1;
		}
		if (s[i] == c && m == 1)
			m = 0;
		i++;
	}
	return (y);
}

char		**ft_split_c3d(t_cub3d *cub, char const *s, char c)
{
	t_splitty	spty;
	char		*copy_s;
	char		**split;

	spty.y = 0;
	spty.len = 0;
	spty.c = c;
	spty.maxlen = cub->maxstrlen;
	copy_s = (char *)s;
	if (s == 0)
		return (0);
	spty.y = ft_string_count(copy_s, c, spty.y);
	split = (char **)ft_calloc(sizeof(char *), ((spty.y) + 1));
	if (split == 0)
		return (0);
	split = ft_c_count(copy_s, split, &spty, cub);
	if (split == 0)
		return (0);
	split = ft_write_string(copy_s, &spty, split, spty.y);
	split[spty.y] = 0;
	return (split);
}
