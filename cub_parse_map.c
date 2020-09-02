/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parse_map.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 21:24:30 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/02 21:32:53 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	check_if_empty_start(t_parse *cub)
{
	if (cub->rx < 0 || cub->ry < 0)
		ft_exit_c3d(cub, "R is fricked", 12);
	if (cub->no == 0)
		ft_exit_c3d(cub, "NO is fricked", 13);
	if (cub->so == 0)
		ft_exit_c3d(cub, "SO is fricked", 13);
	if (cub->we == 0)
		ft_exit_c3d(cub, "WE is fricked", 13);
	if (cub->ea == 0)
		ft_exit_c3d(cub, "EA is fricked", 13);
	if (cub->s == 0)
		ft_exit_c3d(cub, "S is fricked", 13);
	if (((cub->fr < 0 || cub->fr > 255) || (cub->fg < 0 || cub->fg > 255)
	|| (cub->fb < 0 || cub->fb > 255)))
		ft_exit_c3d(cub, "F is fricked", 12);
	if ((cub->cr < 0 || cub->cr > 255) || (cub->cg < 0 || cub->cg > 255)
	|| (cub->cb < 0 || cub->cb > 255))
		ft_exit_c3d(cub, "C is fricked", 12);
}

static void	object_count(t_parse *cub, int x, int y)
{
	if ((cub->mapcopy[y][x] != 'N' && cub->mapcopy[y][x] != 'S' &&
		cub->mapcopy[y][x] != 'W'
		&& cub->mapcopy[y][x] != 'E') && cub->mapcopy[y][x] != '2'
		&& cub->mapcopy[y][x] != '1' && cub->mapcopy[y][x] != '0' &&
		cub->mapcopy[y][x] != ' ')
		ft_exit_c3d(cub, "Map is fricked", 14);
	if (cub->mapcopy[y][x] == 'S' || cub->mapcopy[y][x] == 'W' ||
		cub->mapcopy[y][x] == 'E' || cub->mapcopy[y][x] == 'N')
	{
		cub->players++;
		cub->ltr = cub->mapcopy[y][x];
		cub->startx = x;
		cub->starty = y;
	}
	if (cub->mapcopy[y][x] == '2')
		cub->objects++;
}

void	playerobjcheck(t_parse *cub)
{
	int x;
	int y;

	y = 0;
	while (y < cub->max_y)
	{
		x = 0;
		while (cub->mapcopy[y][x] != '\0')
		{
			object_count(cub, x, y);
			x++;
		}
		y++;
	}
}
