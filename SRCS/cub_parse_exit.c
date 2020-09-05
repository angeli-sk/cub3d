/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parse_exit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:42:36 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/05 14:29:20 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../cub3d.h"
#include "../get_next_line/get_next_line.h"

void	ft_exit_c3d(t_parse *cub, char *s, int len)
{
	write(2, "ERROR\n", 6);
	write(2, s, len);
	write(2, "\n", 1);
	if (cub->fd)
		close(cub->fd);
	exit(1);
}
