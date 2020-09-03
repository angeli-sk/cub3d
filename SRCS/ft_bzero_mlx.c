/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero_mlx.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/03 19:23:23 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 17:00:35 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

void	ft_bzero_mlx(void *s, size_t n)
{
	ft_memset(s, '0', n);
}