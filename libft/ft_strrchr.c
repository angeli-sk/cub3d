/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 12:55:52 by akramp         #+#    #+#                */
/*   Updated: 2019/11/17 14:26:06 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *end;

	end = ft_strchr(s, '\0');
	while (end > s)
	{
		if (*end == (char)c)
			break ;
		end--;
	}
	if (*end == (char)c)
		return (end);
	return (0);
}
