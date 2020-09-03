/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_sprite.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 21:13:08 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 17:00:35 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	sprite_startend(t_parse *cub)
{
	cub->sprite.draw_start_y = -cub->sprite.spr_h / 2 + cub->ry / 2;
	if (cub->sprite.draw_start_y < 0)
		cub->sprite.draw_start_y = 0;
	cub->sprite.draw_end_y = cub->sprite.spr_h / 2 + cub->ry / 2;
	if (cub->sprite.draw_end_y >= cub->ry)
		cub->sprite.draw_end_y = cub->ry;
	cub->sprite.spr_w = abs((int)(cub->ry / (cub->sprite.trans_y)));
	cub->sprite.draw_start_x = -(cub->sprite.spr_w) / 2
		+ cub->sprite.spr_screen_y;
	if (cub->sprite.draw_start_x < 0)
		cub->sprite.draw_start_x = 0;
	cub->sprite.draw_end_x = cub->sprite.spr_w / 2
		+ cub->sprite.spr_screen_y;
	if (cub->sprite.draw_end_x >= cub->rx)
		cub->sprite.draw_end_x = cub->rx;
	cub->sprite.stripe = cub->sprite.draw_start_x;
}

static void	calc_sprite(t_parse *cub, int i)
{
	cub->sprite.spr_x = cub->arr[cub->sprite_order[i]].x - cub->vars.pos_x;
	cub->sprite.spr_y = cub->arr[cub->sprite_order[i]].y - cub->vars.pos_y;
	cub->sprite.spr_x += 0.5;
	cub->sprite.spr_y += 0.5;
	cub->sprite.inv_det = 1.0 / (cub->vars.plane_x *
		cub->vars.dir_y - cub->vars.dir_x * cub->vars.plane_y);
	cub->sprite.trans_x = cub->sprite.inv_det * (cub->vars.dir_y *
		cub->sprite.spr_x - cub->vars.dir_x * cub->sprite.spr_y);
	cub->sprite.trans_y = cub->sprite.inv_det * (-cub->vars.plane_y *
		cub->sprite.spr_x + cub->vars.plane_x * cub->sprite.spr_y);
	cub->sprite.spr_screen_y = (int)((cub->rx / 2) *
		(1 + cub->sprite.trans_x / cub->sprite.trans_y));
	cub->sprite.spr_h = abs((int)(cub->ry / (cub->sprite.trans_y)));
	sprite_startend(cub);
}

static void	draw_sprite_line(t_parse *cub)
{
	unsigned int color;

	color = 0;
	cub->vars.tex_x = (int)(256 * (cub->sprite.stripe -
		(-cub->sprite.spr_w / 2 + cub->sprite.spr_screen_y))
		* cub->tex[4].x / cub->sprite.spr_w) / 256;
	cub->sprite.d = (cub->vars.y) * 256 - cub->ry * 128
		+ cub->sprite.spr_h * 128;
	cub->vars.tex_y = ((cub->sprite.d * cub->tex[4].x)
		/ cub->sprite.spr_h) / 256;
	color = *(unsigned int *)(cub->tex[4].addr
		+ (cub->tex[4].line_length * (int)cub->vars.tex_y
		+ (int)cub->vars.tex_x * (cub->tex[4].bits_per_pixel / 8)));
	if (color > 0)
		my_mlx_pixel_put(&cub->img,
			cub->sprite.stripe, cub->vars.y, color);
}

static void	draw_sprite(t_parse *cub)
{
	while (cub->sprite.stripe < cub->sprite.draw_end_x)
	{
		cub->vars.tex_x = (int)(256 * (cub->sprite.stripe -
			(-cub->sprite.spr_w / 2 + cub->sprite.spr_screen_y))
			* cub->tex[4].x / cub->sprite.spr_w) / 256;
		if (cub->sprite.trans_y > 0 && cub->sprite.stripe >= 0 &&
				cub->sprite.stripe < cub->vars.w && cub->sprite.trans_y <
				cub->vars.z_buff[cub->sprite.stripe])
			cub->vars.y = cub->sprite.draw_start_y;
		while (cub->vars.y < cub->sprite.draw_end_y && cub->sprite.stripe >= 0
			&& cub->sprite.stripe < cub->rx)
		{
			draw_sprite_line(cub);
			cub->vars.y++;
		}
		cub->sprite.stripe++;
	}
}

void		mlx_sprite(t_parse *cub)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (i < cub->objects)
	{
		cub->sprite_order[i] = i;
		cub->arr[cub->sprite_order[i]].distance = ((cub->vars.pos_x
			- cub->arr[cub->sprite_order[i]].x) * (cub->vars.pos_x
			- cub->arr[cub->sprite_order[i]].x) + (cub->vars.pos_y
			- cub->arr[cub->sprite_order[i]].y) * (cub->vars.pos_y
			- cub->arr[cub->sprite_order[i]].y));
		i++;
	}
	ft_sort(cub);
	i = 0;
	while (i < cub->objects)
	{
		calc_sprite(cub, i);
		draw_sprite(cub);
		i++;
	}
}
