/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   verline.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:18:31 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 17:00:35 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

static int	calc_tex(t_parse *cub)
{
	int tex;

	tex = 0;
	if (cub->vars.side == 1 && cub->vars.ray_y > 0)
		tex = 0;
	if (cub->vars.side == 1 && cub->vars.ray_y < 0)
		tex = 1;
	if (cub->vars.side == 0 && cub->vars.ray_x > 0)
		tex = 2;
	if (cub->vars.side == 0 && cub->vars.ray_x < 0)
		tex = 3;
	return (tex);
}

static void	calc_draw_start(t_parse *cub, int draw_start, int tex)
{
	while (cub->vars.y < draw_start)
	{
		my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, cub->c_color);
		cub->vars.y++;
	}
	if (cub->vars.side == 0)
		cub->vars.wall_x = cub->vars.pos_y + cub->vars.perp_w_d
		* cub->vars.ray_y;
	else
		cub->vars.wall_x = cub->vars.pos_x + cub->vars.perp_w_d
		* cub->vars.ray_x;
	cub->vars.wall_x -= floor((cub->vars.wall_x));
	cub->vars.tex_x = (int)(cub->vars.wall_x * (double)(cub->tex[tex].x));
	if (cub->vars.side == 0 && cub->vars.ray_x > 0)
		cub->vars.tex_x = cub->tex[tex].x - cub->vars.tex_x - 1;
	if (cub->vars.side == 1 && cub->vars.ray_y < 0)
		cub->vars.tex_x = cub->tex[tex].x - cub->vars.tex_x - 1;
	cub->vars.step = 1.0 * cub->tex[tex].y / cub->vars.line_h;
	cub->vars.tex_pos = (cub->vars.draw_start - cub->vars.h / 2 +
		cub->vars.line_h / 2) * cub->vars.step;
	cub->vars.y = draw_start;
	cub->vars.tex_x = cub->tex[tex].x - cub->vars.tex_x - 1;
}

static void	calc_end(t_parse *cub)
{
	while (cub->vars.y < cub->ry)
	{
		my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, cub->f_color);
		cub->vars.y++;
	}
}

void		ft_verline(int draw_start, int draw_end, t_parse *cub)
{
	int				tex;
	char			*test;
	unsigned int	color;

	cub->vars.y = 0;
	tex = calc_tex(cub);
	calc_draw_start(cub, draw_start, tex);
	while (cub->vars.y <= draw_end)
	{
		cub->vars.tex_y = (int)cub->vars.tex_pos & (cub->tex[tex].y - 1);
		cub->vars.tex_pos += cub->vars.step;
		if (cub->vars.tex_y >= 0 && cub->vars.tex_x >= 0)
			color = *(unsigned int *)(cub->tex[tex].addr +
			((cub->tex[tex].line_length * (int)cub->vars.tex_y) +
			(int)cub->vars.tex_x * (cub->tex[tex].bits_per_pixel / 8)));
		else
			color = 0;
		if (color < 0)
			color = 0;
		my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, color);
		cub->vars.y++;
	}
	calc_end(cub);
}
