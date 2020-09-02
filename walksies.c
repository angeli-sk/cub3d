/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   walksies.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 21:34:38 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/02 21:52:07 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	walksies_up_down(t_parse *cub, t_boris *move)
{
	if (cub->vars.walksies[up] == 1)
	{
		if (cub->map[(int)(cub->vars.posY)][move->x_up] != '1' &&
				ft_checkposition(cub, move->x_up, move->y_up) == 1)
			cub->vars.posX += cub->vars.dirX * cub->vars.speedy;
		if (cub->map[move->y_up][(int)(cub->vars.posX)] != '1' &&
				ft_checkposition(cub, move->x_up, move->y_up) == 1)
			cub->vars.posY += cub->vars.dirY * cub->vars.speedy;
	}
	if (cub->vars.walksies[down] == 1)
	{
		if (cub->map[(int)(cub->vars.posY)][move->x_down] != '1' &&
				ft_checkposition(cub, move->x_down, move->y_down) == 1)
			cub->vars.posX -= cub->vars.dirX * cub->vars.speedy;
		if (cub->map[move->y_down][(int)(cub->vars.posX)] != '1' &&
				ft_checkposition(cub, move->x_down, move->y_down) == 1)
			cub->vars.posY -= cub->vars.dirY * cub->vars.speedy;
	}
}

static void	walksies_left_right(t_parse *cub, t_boris *move)
{
	if (cub->vars.walksies[left] == 1)
	{
		if (cub->map[(int)(cub->vars.posY)][move->x_right] != '1' &&
				ft_checkposition(cub, move->x_right, move->y_right) == 1)
			cub->vars.posX += cub->vars.dirY * cub->vars.speedy;
		if (cub->map[move->y_right][(int)(cub->vars.posX)] != '1' &&
				ft_checkposition(cub, move->x_right, move->y_right) == 1)
			cub->vars.posY -= cub->vars.dirX * cub->vars.speedy;
	}
	if (cub->vars.walksies[right] == 1)
	{
		if (cub->map[(int)(cub->vars.posY)][move->x_left] != '1' &&
				ft_checkposition(cub, move->x_left, move->y_left) == 1)
			cub->vars.posX -= cub->vars.dirY * cub->vars.speedy;
		if (cub->map[move->y_left][(int)(cub->vars.posX)] != '1' &&
				ft_checkposition(cub, move->x_left, move->y_left) == 1)
			cub->vars.posY += cub->vars.dirX * cub->vars.speedy;
	}
}

static void	walksies_turn_left(t_parse *cub)
{
	if (cub->vars.walksies[turn_l] == 1)
	{
		cub->vars.oldDirX = cub->vars.dirX;
		cub->vars.dirX = cub->vars.dirX * cos(-cub->vars.rotSpeed) -
						cub->vars.dirY * sin(-cub->vars.rotSpeed);
		cub->vars.dirY = cub->vars.oldDirX * sin(-cub->vars.rotSpeed) +
						cub->vars.dirY * cos(-cub->vars.rotSpeed);
		cub->vars.oldPlaneX = cub->vars.planeX;
		cub->vars.planeX = cub->vars.planeX * cos(-cub->vars.rotSpeed) -
						cub->vars.planeY * sin(-cub->vars.rotSpeed);
		cub->vars.planeY = cub->vars.oldPlaneX * sin(-cub->vars.rotSpeed) +
						cub->vars.planeY * cos(-cub->vars.rotSpeed);
	}
}

static void	walksies_turn_right(t_parse *cub)
{
	if (cub->vars.walksies[turn_r] == 1)
	{
		cub->vars.oldDirX = cub->vars.dirX;
		cub->vars.dirX = cub->vars.dirX * cos(cub->vars.rotSpeed) -
						cub->vars.dirY * sin(cub->vars.rotSpeed);
		cub->vars.dirY = cub->vars.oldDirX * sin(cub->vars.rotSpeed) +
						cub->vars.dirY * cos(cub->vars.rotSpeed);
		cub->vars.oldPlaneX = cub->vars.planeX;
		cub->vars.planeX = cub->vars.planeX * cos(cub->vars.rotSpeed) -
						cub->vars.planeY * sin(cub->vars.rotSpeed);
		cub->vars.planeY = cub->vars.oldPlaneX * sin(cub->vars.rotSpeed) +
						cub->vars.planeY * cos(cub->vars.rotSpeed);
	}
}

void		walksies(t_parse *cub, t_boris *move)
{
	walksies_up_down(cub, move);
	walksies_left_right(cub, move);
	walksies_turn_left(cub);
	walksies_turn_right(cub);
}
