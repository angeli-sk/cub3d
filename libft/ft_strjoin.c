/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 18:51:57 by akramp         #+#    #+#                */
/*   Updated: 2019/11/17 19:15:46 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_fill(char *str, char const *s1, char const *s2)
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
	str[i] = '\0';
	return (str);
}

char	*ft_check(char const *s1, char const *s2)
{
	if (s1 == 0 && s2 == 0)
		return (0);
	if (s1 == 0)
		return (ft_strdup(s2));
	if (s2 == 0)
		return (ft_strdup(s1));
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if ((s1 == 0 && s2 == 0) || s1 == 0 || s2 == 0)
		return (ft_check(s1, s2));
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len) + 1);
	if (str == 0)
		return (0);
	str = ft_fill(str, s1, s2);
	return (str);
}
