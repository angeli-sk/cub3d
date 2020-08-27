/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 19:32:37 by akramp         #+#    #+#                */
/*   Updated: 2019/11/17 19:16:13 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_pre(int n, char const *s1, char const *set)
{
	int i;

	i = 0;
	while (s1[n] != '\0')
	{
		while (set[i] != '\0')
		{
			if (set[i] == s1[n])
			{
				n++;
				i = 0;
			}
			else
				i++;
		}
		return (n);
	}
	return (0);
}

static int		ft_post(int len, char const *s1, char const *set)
{
	int i;
	int l;

	i = 0;
	l = len - 1;
	while (set[i] != '\0' && l > 0)
	{
		if (set[i] == s1[l])
		{
			l--;
			i = 0;
		}
		else
			i++;
	}
	if (l <= 0)
		return (0);
	return (len - l - 1);
}

static char		*ft_trim(int pre, int len, char const *s1, char *str)
{
	int n;

	n = 0;
	while (n < len)
	{
		str[n] = s1[pre];
		n++;
		pre++;
	}
	str[n] = '\0';
	return (str);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		pre;
	int		post;
	int		len;
	int		n;

	pre = 0;
	post = 0;
	len = 0;
	n = 0;
	if (s1 == 0)
		return (0);
	len = ft_strlen(s1);
	pre = ft_pre(n, s1, set);
	if (pre == len)
		return (ft_strdup(""));
	post = ft_post(len, s1, set);
	len = len - (pre + post);
	if (len < 0)
		len = 0;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == 0)
		return (0);
	str = ft_trim(pre, len, s1, str);
	return ((char *)str);
}
