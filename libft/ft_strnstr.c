/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 10:51:13 by akramp         #+#    #+#                */
/*   Updated: 2019/11/17 14:35:20 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hay;
	char	*ned;
	size_t	hay_i;
	size_t	ned_i;

	hay = (char *)haystack;
	ned = (char *)needle;
	if (ned[0] == '\0')
		return (hay);
	hay_i = 0;
	while (hay_i < len)
	{
		ned_i = 0;
		while ((hay[hay_i + ned_i] == ned[ned_i]) && (hay_i + ned_i < len))
		{
			ned_i++;
			if (ned[ned_i] == '\0')
				return (hay + hay_i);
		}
		if (hay[hay_i] == '\0')
			break ;
		hay_i++;
	}
	return (0);
}
