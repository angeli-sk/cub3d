/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 18:20:49 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/05 18:20:52 by akramp        ########   odam.nl         */
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
