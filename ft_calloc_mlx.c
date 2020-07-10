/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 15:48:24 by akramp         #+#    #+#                */
/*   Updated: 2019/11/17 19:27:47 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	*ft_calloc_mlx(size_t count, size_t size)
{
	void	*s;

	s = malloc(size * count);
	if (s == 0)
		return (0);
	ft_bzero_mlx(s, count);
	return (s);
}
