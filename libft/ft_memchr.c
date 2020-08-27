/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:18:43 by akramp         #+#    #+#                */
/*   Updated: 2019/11/17 14:17:06 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_c;

	s_c = (unsigned char *)s;
	while (n > 0)
	{
		if (*s_c == (unsigned char)c)
			return ((void *)s_c);
		s_c++;
		n--;
	}
	return (0);
}
