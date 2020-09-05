/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 18:18:05 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/05 18:18:08 by akramp        ########   odam.nl         */
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
