/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 21:52:19 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 17:00:35 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <math.h>

static void	calc_value(t_parse *cub)
{
	cub->vars.colorwall = 13086203;
	cub->vars.cam_x = 2 * cub->vars.x / (double)cub->vars.w - 1;
	cub->vars.ray_x = cub->vars.dir_x + cub->vars.plane_x * cub->vars.cam_x;
	cub->vars.ray_y = cub->vars.dir_y + cub->vars.plane_y * cub->vars.cam_x;
	cub->vars.map_x = (int)cub->vars.pos_x;
	cub->vars.map_y = (int)cub->vars.pos_y;
	if (cub->vars.ray_y == 0)
		cub->vars.delta_d_x = 0;
	else if (cub->vars.ray_x == 0)
		cub->vars.delta_d_x = 1;
	else
		cub->vars.delta_d_x = fabs(1 / cub->vars.ray_x);
	if (cub->vars.ray_x == 0)
		cub->vars.delta_d_y = 0;
	else if (cub->vars.ray_y == 0)
		cub->vars.delta_d_y = 1;
	else
		cub->vars.delta_d_y = fabs(1 / cub->vars.ray_y);
}

static void	calc_sidedist(t_parse *cub)
{
	if (cub->vars.ray_x < 0)
	{
		cub->vars.step_x = -1;
		cub->vars.side_d_x =
			(cub->vars.pos_x - cub->vars.map_x) * cub->vars.delta_d_x;
	}
	else
	{
		cub->vars.step_x = 1;
		cub->vars.side_d_x =
			(cub->vars.map_x + 1.0 - cub->vars.pos_x) * cub->vars.delta_d_x;
	}
	if (cub->vars.ray_y < 0)
	{
		cub->vars.step_y = -1;
		cub->vars.side_d_y =
			(cub->vars.pos_y - cub->vars.map_y) * cub->vars.delta_d_y;
	}
	else
	{
		cub->vars.step_y = 1;
		cub->vars.side_d_y =
			(cub->vars.map_y + 1.0 - cub->vars.pos_y) * cub->vars.delta_d_y;
	}
}

static void	calc_hit(t_parse *cub)
{
	cub->vars.hit = 0;
	while (cub->vars.hit == 0)
	{
		if (cub->vars.side_d_x < cub->vars.side_d_y)
		{
			cub->vars.side_d_x += cub->vars.delta_d_x;
			cub->vars.map_x += cub->vars.step_x;
			cub->vars.side = 0;
		}
		else
		{
			cub->vars.side_d_y += cub->vars.delta_d_y;
			cub->vars.map_y += cub->vars.step_y;
			cub->vars.side = 1;
		}
		if (cub->map[cub->vars.map_y][cub->vars.map_x] == '1')
			cub->vars.hit = 1;
	}
}

void		mlx_calc(t_parse *cub)
{
	cub->vars.x = 0;
	while (cub->vars.x < cub->vars.w)
	{
		calc_value(cub);
		calc_sidedist(cub);
		calc_hit(cub);
		if (cub->vars.side == 0)
			cub->vars.perp_w_d = (cub->vars.map_x - cub->vars.pos_x +
			(1 - cub->vars.step_x) / 2) / cub->vars.ray_x;
		else
			cub->vars.perp_w_d = (cub->vars.map_y - cub->vars.pos_y +
				(1 - cub->vars.step_y) / 2) / cub->vars.ray_y;
		cub->vars.line_h = (int)(cub->vars.h / cub->vars.perp_w_d);
		cub->vars.draw_start = (-cub->vars.line_h / 2) + (cub->vars.h / 2);
		if (cub->vars.draw_start < 0)
			cub->vars.draw_start = 0;
		cub->vars.draw_end = (cub->vars.line_h / 2) + (cub->vars.h / 2);
		if (cub->vars.draw_end >= cub->vars.h)
			cub->vars.draw_end = cub->vars.h - 1;
		if (cub->vars.side == 1)
			cub->vars.colorwall = cub->vars.colorwall / 2;
		ft_verline(cub->vars.draw_start, cub->vars.draw_end, cub);
		cub->vars.z_buff[cub->vars.x] = cub->vars.perp_w_d;
		cub->vars.x++;
	}
}
