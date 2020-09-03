/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parse_exit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:42:36 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 17:24:13 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../cub3d.h"
#include "../get_next_line/get_next_line.h"

void	freemaps(t_parse *cub)
{
	while (cub->max_y >= 0 && (cub->map || cub->mapcopy))
	{
		free(cub->map[cub->max_y]);
		free(cub->mapcopy[cub->max_y]);
		cub->max_y--;
	}
	free(cub->map);
	free(cub->mapcopy);
}

void	freevars(t_parse *cub)
{
	if (cub->line)
		free((cub->line));
	if (cub->num_temp)
		free((cub->num_temp));
	if (cub->no)
		free(cub->no);
	if (cub->so)
		free(cub->so);
	if (cub->we)
		free(cub->we);
	if (cub->ea)
		free(cub->ea);
	if (cub->s)
		free(cub->s);
	if (cub->temp)
		free(cub->temp);
	if (cub->vars.z_buff)
		free(cub->vars.z_buff);
	if (cub->sprite_order)
		free(cub->sprite_order);
}

void	ft_exit_c3d(t_parse *cub, char *s, int len)
{
	write(1, "ERROR\n", 6);
	write(1, s, len);
	write(1, "\n", 1);
	// freevars(cub);
	// if (cub->beginmap != 0)
	// 	freemaps(cub);
	close(cub->fd);
	exit(1);
}
