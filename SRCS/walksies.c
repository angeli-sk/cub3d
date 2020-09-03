/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   walksies.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 21:34:38 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 17:00:35 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

static void	walksies_up_down(t_parse *cub, t_move *move)
{
	if (cub->vars.walksies[up] == 1)
	{
		if (cub->map[(int)(cub->vars.pos_y)][move->x_up] != '1' &&
				ft_checkposition(cub, move->x_up, move->y_up) == 1)
			cub->vars.pos_x += cub->vars.dir_x * cub->vars.spd;
		if (cub->map[move->y_up][(int)(cub->vars.pos_x)] != '1' &&
				ft_checkposition(cub, move->x_up, move->y_up) == 1)
			cub->vars.pos_y += cub->vars.dir_y * cub->vars.spd;
	}
	if (cub->vars.walksies[down] == 1)
	{
		if (cub->map[(int)(cub->vars.pos_y)][move->x_down] != '1' &&
				ft_checkposition(cub, move->x_down, move->y_down) == 1)
			cub->vars.pos_x -= cub->vars.dir_x * cub->vars.spd;
		if (cub->map[move->y_down][(int)(cub->vars.pos_x)] != '1' &&
				ft_checkposition(cub, move->x_down, move->y_down) == 1)
			cub->vars.pos_y -= cub->vars.dir_y * cub->vars.spd;
	}
}

static void	walksies_left_right(t_parse *cub, t_move *move)
{
	if (cub->vars.walksies[left] == 1)
	{
		if (cub->map[(int)(cub->vars.pos_y)][move->x_right] != '1' &&
				ft_checkposition(cub, move->x_right, move->y_right) == 1)
			cub->vars.pos_x += cub->vars.dir_y * cub->vars.spd;
		if (cub->map[move->y_right][(int)(cub->vars.pos_x)] != '1' &&
				ft_checkposition(cub, move->x_right, move->y_right) == 1)
			cub->vars.pos_y -= cub->vars.dir_x * cub->vars.spd;
	}
	if (cub->vars.walksies[right] == 1)
	{
		if (cub->map[(int)(cub->vars.pos_y)][move->x_left] != '1' &&
				ft_checkposition(cub, move->x_left, move->y_left) == 1)
			cub->vars.pos_x -= cub->vars.dir_y * cub->vars.spd;
		if (cub->map[move->y_left][(int)(cub->vars.pos_x)] != '1' &&
				ft_checkposition(cub, move->x_left, move->y_left) == 1)
			cub->vars.pos_y += cub->vars.dir_x * cub->vars.spd;
	}
}

static void	walksies_turn_left(t_parse *cub)
{
	if (cub->vars.walksies[turn_l] == 1)
	{
		cub->vars.olddir_x = cub->vars.dir_x;
		cub->vars.dir_x = cub->vars.dir_x * cos(-cub->vars.rot_speed) -
						cub->vars.dir_y * sin(-cub->vars.rot_speed);
		cub->vars.dir_y = cub->vars.olddir_x * sin(-cub->vars.rot_speed) +
						cub->vars.dir_y * cos(-cub->vars.rot_speed);
		cub->vars.oldplane_x = cub->vars.plane_x;
		cub->vars.plane_x = cub->vars.plane_x * cos(-cub->vars.rot_speed) -
						cub->vars.plane_y * sin(-cub->vars.rot_speed);
		cub->vars.plane_y = cub->vars.oldplane_x * sin(-cub->vars.rot_speed) +
						cub->vars.plane_y * cos(-cub->vars.rot_speed);
	}
}

static void	walksies_turn_right(t_parse *cub)
{
	if (cub->vars.walksies[turn_r] == 1)
	{
		cub->vars.olddir_x = cub->vars.dir_x;
		cub->vars.dir_x = cub->vars.dir_x * cos(cub->vars.rot_speed) -
						cub->vars.dir_y * sin(cub->vars.rot_speed);
		cub->vars.dir_y = cub->vars.olddir_x * sin(cub->vars.rot_speed) +
						cub->vars.dir_y * cos(cub->vars.rot_speed);
		cub->vars.oldplane_x = cub->vars.plane_x;
		cub->vars.plane_x = cub->vars.plane_x * cos(cub->vars.rot_speed) -
						cub->vars.plane_y * sin(cub->vars.rot_speed);
		cub->vars.plane_y = cub->vars.oldplane_x * sin(cub->vars.rot_speed) +
						cub->vars.plane_y * cos(cub->vars.rot_speed);
	}
}

void		walksies(t_parse *cub, t_move *move)
{
	walksies_up_down(cub, move);
	walksies_left_right(cub, move);
	walksies_turn_left(cub);
	walksies_turn_right(cub);
}
