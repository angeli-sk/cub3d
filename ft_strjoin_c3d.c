/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_c3d.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 18:51:57 by akramp        #+#    #+#                 */
/*   Updated: 2020/07/09 16:12:24 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
# include "./libft/libft.h"

static char	*ft_fil(char *str, char const *s1, char const *s2)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[n] != '\0')
	{
		str[i] = s2[n];
		n++;
		i++;
	}
	str[i] = '\n';
	str[i + 1] = '\0';
	return (str);
}

static char	*ft_check(char const *s1, char const *s2)
{
	if (s1 == 0 && s2 == 0)
		return (0);
	if (s1 == 0)
		return (ft_strdup(s2));
	if (s2 == 0)
		return (ft_strdup(s1));
	return (0);
}

char	*ft_strjoin_c3d(t_parse *cub, char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str;

	if ((s1 == 0 && s2 == 0) || s1 == 0 || s2 == 0)
		return (ft_check(s1, s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s2_len > cub->maxstrlen)
		cub->maxstrlen = s2_len;
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len) + 2);
	if (str == 0)
	{
		free(str);
		return (0);
	}
	str = ft_fil(str, s1, s2);
	free((void *)s1);
	return (str);
}
